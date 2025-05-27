#include "model.h"

#include "common-sdl.h"
#include "common.h"
#include "common-whisper.h"
#include "whisper.h"

#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>


Model::Model() : QObject(nullptr) {
}

void Model::start(int mic_dev) {
    worker = new Worker(mic_dev);
    worker->moveToThread(&workerThread);
    connect(worker, &Worker::conditionMessage, this, &Model::handleMessage);
    connect(&workerThread, &QThread::started, worker, &Worker::doWork);
    connect(worker, &Worker::finished, &workerThread, &QThread::quit); // Finaliza el event loop

    workerThread.start();
}

std::list<std::pair<int, std::string>> Model::get_mic_devices() {
    mic_devices.clear();
    SDL_Init(SDL_INIT_AUDIO);
    int num_devices = SDL_GetNumAudioDevices(SDL_TRUE); // SDL_TRUE = captura
    for (int i = 0; i < num_devices; i++) {
        mic_devices.push_back(std::make_pair(i,SDL_GetAudioDeviceName(i, SDL_TRUE)));
    }
    SDL_Quit();
    return mic_devices;
}

void Model::stop_transcription() {
    worker->stopWork();
    //workerThread.wait();

}


void Worker::doWork() {
    qDebug() << "Worker: Hilo iniciado en thread" << QThread::currentThreadId();

    while (is_running && !m_stop) {
        if (params.save_audio) {
            wavWriter.write(pcmf32_new.data(), pcmf32_new.size());
        }
        // handle Ctrl + C
        is_running = sdl_poll_events();

        if (!is_running) {
            break;
        }

        // process new audio

        if (!use_vad) {
            while (true) {
                // handle Ctrl + C
                is_running = sdl_poll_events();
                if (!is_running) {
                    break;
                }
                 audio->get(params.step_ms, pcmf32_new);
                if ((int) pcmf32_new.size() > 2*n_samples_step) {
                    //fprintf(stderr, "\n\n%s: WARNING: cannot process audio fast enough, dropping audio ...\n\n", __func__);
                    audio->clear();
                    continue;
                }

                if ((int) pcmf32_new.size() >= n_samples_step) {
                    audio->clear();
                    break;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }

            const int n_samples_new = pcmf32_new.size();

            // take up to params.length_ms audio from previous iteration
            const int n_samples_take = std::min((int) pcmf32_old.size(), std::max(0, n_samples_keep + n_samples_len - n_samples_new));

            //printf("processing: take = %d, new = %d, old = %d\n", n_samples_take, n_samples_new, (int) pcmf32_old.size());

            pcmf32.resize(n_samples_new + n_samples_take);

            for (int i = 0; i < n_samples_take; i++) {
                pcmf32[i] = pcmf32_old[pcmf32_old.size() - n_samples_take + i];
            }

            memcpy(pcmf32.data() + n_samples_take, pcmf32_new.data(), n_samples_new*sizeof(float));

            pcmf32_old = pcmf32;
        } else {
            const auto t_now  = std::chrono::high_resolution_clock::now();
            const auto t_diff = std::chrono::duration_cast<std::chrono::milliseconds>(t_now - t_last).count();

            if (t_diff < 2000) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

                continue;
            }

            audio->get(2000, pcmf32_new);

            if (::vad_simple(pcmf32_new, WHISPER_SAMPLE_RATE, 1000, params.vad_thold, params.freq_thold, false)) {
                audio->get(params.length_ms, pcmf32);
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

                continue;
            }

            t_last = t_now;
        }

        // run the inference
        {
            whisper_full_params wparams = whisper_full_default_params(params.beam_size > 1 ? WHISPER_SAMPLING_BEAM_SEARCH : WHISPER_SAMPLING_GREEDY);

            wparams.print_progress   = false;
            wparams.print_special    = params.print_special;
            wparams.print_realtime   = false;
            wparams.print_timestamps = !params.no_timestamps;
            wparams.translate        = params.translate;
            wparams.single_segment   = !use_vad;
            wparams.max_tokens       = params.max_tokens;
            wparams.language         = params.language.c_str();
            wparams.n_threads        = params.n_threads;
            wparams.beam_search.beam_size = params.beam_size;

            wparams.audio_ctx        = params.audio_ctx;

            wparams.tdrz_enable      = params.tinydiarize; // [TDRZ]

            // disable temperature fallback
            //wparams.temperature_inc  = -1.0f;
            wparams.temperature_inc  = params.no_fallback ? 0.0f : wparams.temperature_inc;

            wparams.prompt_tokens    = params.no_context ? nullptr : prompt_tokens.data();
            wparams.prompt_n_tokens  = params.no_context ? 0       : prompt_tokens.size();

            if (whisper_full(ctx, wparams, pcmf32.data(), pcmf32.size()) != 0) {
                //fprintf(stderr, "%s: failed to process audio\n", argv[0]);
                return;
            }

            // print result;
            {
                if (!use_vad) {
                    //printf("\33[2K\r");

                    // print long empty line to clear the previous line
                    //printf("%s", std::string(100, ' ').c_str());

                    //printf("\33[2K\r");
                } else {
                    const int64_t t1 = (t_last - t_start).count()/1000000;
                    const int64_t t0 = std::max(0.0, t1 - pcmf32.size()*1000.0/WHISPER_SAMPLE_RATE);
                    /*
                    printf("\n");
                    printf("### Transcription %d START | t0 = %d ms | t1 = %d ms\n", n_iter, (int) t0, (int) t1);
                    printf("\n");
                    */
                }

                const int n_segments = whisper_full_n_segments(ctx);
                for (int i = 0; i < n_segments; ++i) {
                    const char * text = whisper_full_get_segment_text(ctx, i);

                    if (params.no_timestamps) {
                        //printf("%s", text);
                        qDebug() << text << '\n';
                        emit conditionMessage(text);
                        //fflush(stdout);
                        /*
                        if (params.fname_out.length() > 0) {
                            fout << text;
                        }*/
                    } else {
                        const int64_t t0 = whisper_full_get_segment_t0(ctx, i);
                        const int64_t t1 = whisper_full_get_segment_t1(ctx, i);

                        QString output = text ; // "[" + to_timestamp(t0, false) + " --> " + to_timestamp(t1, false) + "]  " + text;

                        if (whisper_full_get_segment_speaker_turn_next(ctx, i)) {
                            output += " [SPEAKER_TURN]";
                        }

                        output += "\n";

                        qDebug() << output << '\n';
                        emit conditionMessage(QString(output));
                        //printf("%s", output.c_str());
                        //fflush(stdout);
                        /*
                        if (params.fname_out.length() > 0) {
                            fout << output;
                        }*/
                    }
                }



                /*
                if (use_vad) {
                    printf("\n");
                    printf("### Transcription %d END\n", n_iter);
                }*/
            }

            ++n_iter;

            if (!use_vad && (n_iter % n_new_line) == 0) {
                //printf("\n");

                // keep part of the audio for next iteration to try to mitigate word boundary issues
                pcmf32_old = std::vector<float>(pcmf32.end() - n_samples_keep, pcmf32.end());

                // Add tokens of the last full length segment as the prompt
                if (!params.no_context) {
                    prompt_tokens.clear();

                    const int n_segments = whisper_full_n_segments(ctx);
                    for (int i = 0; i < n_segments; ++i) {
                        const int token_count = whisper_full_n_tokens(ctx, i);
                        for (int j = 0; j < token_count; ++j) {
                            prompt_tokens.push_back(whisper_full_get_token_id(ctx, i, j));
                        }
                    }
                }
            }
            //fflush(stdout);
        }
    }

    audio->pause();

    whisper_print_timings(ctx);
    whisper_free(ctx);

    emit finished();
}

int Worker::setup_capture(int mic_dev)
{

    whisper_params params;

    params.capture_id = mic_dev;

    /*
    if (whisper_params_parse(argc, argv, params) == false) {
        return 1;
    }
*/

    params.keep_ms   = std::min(params.keep_ms,   params.step_ms);
    params.length_ms = std::max(params.length_ms, params.step_ms);

    n_samples_step = (1e-3*params.step_ms  )*WHISPER_SAMPLE_RATE;
    n_samples_len  = (1e-3*params.length_ms)*WHISPER_SAMPLE_RATE;
    n_samples_keep = (1e-3*params.keep_ms  )*WHISPER_SAMPLE_RATE;
    n_samples_30s  = (1e-3*30000.0         )*WHISPER_SAMPLE_RATE;

    use_vad = n_samples_step <= 0; // sliding window mode uses VAD

    n_new_line = !use_vad ? std::max(1, params.length_ms / params.step_ms - 1) : 1; // number of steps to print new line

    params.no_timestamps  = !use_vad;
    params.no_context    |= use_vad;
    params.max_tokens     = 0;

    // init audio

    audio = new audio_async(params.length_ms);
    if (!audio->init(params.capture_id, WHISPER_SAMPLE_RATE)) {
        fprintf(stderr, "%s: audio.init() failed!\n", __func__);
        return 1;
    }

    audio->resume();

    // whisper init
    if (params.language != "auto" && whisper_lang_id(params.language.c_str()) == -1){
        fprintf(stderr, "error: unknown language '%s'\n", params.language.c_str());
        //whisper_print_usage(argc, argv, params);
        exit(0);
    }

    struct whisper_context_params cparams = whisper_context_default_params();

    cparams.use_gpu    = params.use_gpu;
    cparams.flash_attn = params.flash_attn;

    ctx = whisper_init_from_file_with_params(params.model.c_str(), cparams);

    pcmf32=std::vector<float>(n_samples_30s, 0.0f);
    pcmf32_new=std::vector<float>(n_samples_30s, 0.0f);

    // print some info about the processing
    {
        fprintf(stderr, "\n");
        if (!whisper_is_multilingual(ctx)) {
            if (params.language != "en" || params.translate) {
                params.language = "en";
                params.translate = false;
                fprintf(stderr, "%s: WARNING: model is not multilingual, ignoring language and translation options\n", __func__);
            }
        }
        fprintf(stderr, "%s: processing %d samples (step = %.1f sec / len = %.1f sec / keep = %.1f sec), %d threads, lang = %s, task = %s, timestamps = %d ...\n",
                __func__,
                n_samples_step,
                float(n_samples_step)/WHISPER_SAMPLE_RATE,
                float(n_samples_len )/WHISPER_SAMPLE_RATE,
                float(n_samples_keep)/WHISPER_SAMPLE_RATE,
                params.n_threads,
                params.language.c_str(),
                params.translate ? "translate" : "transcribe",
                params.no_timestamps ? 0 : 1);

        if (!use_vad) {
            fprintf(stderr, "%s: n_new_line = %d, no_context = %d\n", __func__, n_new_line, params.no_context);
        } else {
            fprintf(stderr, "%s: using VAD, will transcribe on speech activity\n", __func__);
        }

        fprintf(stderr, "\n");
    }

    int n_iter = 0;

    is_running = true;
    if (params.fname_out.length() > 0) {
        fout.open(params.fname_out);
        if (!fout.is_open()) {
            fprintf(stderr, "%s: failed to open output file '%s'!\n", __func__, params.fname_out.c_str());
            return 1;
        }
    }

    // save wav file
    if (params.save_audio) {
        // Get current date/time for filename
        time_t now = time(0);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", localtime(&now));
        std::string filename = std::string(buffer) + ".wav";

        wavWriter.open(filename, WHISPER_SAMPLE_RATE, 16, 1);
    }

    t_last  = std::chrono::high_resolution_clock::now();
    auto t_start = t_last;

      return 0;

}