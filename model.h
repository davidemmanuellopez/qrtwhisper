#ifndef MODEL_H
#define MODEL_H

#include <common.h>
#include <iostream>
#include <QObject>
#include <QTimer>

#include <thread>
#include "common.h"
#include "common-sdl.h"
#include "whisper.h"

#include <QObject>
#include <QThread>
#include <QDebug>

#include "config.h"


class Worker;

struct whisper_params {
    int32_t n_threads  = std::min(4, (int32_t) std::thread::hardware_concurrency());
    int32_t step_ms    = 3000;
    int32_t length_ms  = 10000;
    int32_t keep_ms    = 200;
    int32_t capture_id = 1;
    int32_t max_tokens = 32;
    int32_t audio_ctx  = 0;
    int32_t beam_size  = -1;

    float vad_thold    = 0.6f;
    float freq_thold   = 100.0f;

    bool translate     = false;
    bool no_fallback   = false;
    bool print_special = false;
    bool no_context    = true;
    bool no_timestamps = false;
    bool tinydiarize   = false;
    bool save_audio    = false; // save audio to wav file
    bool use_gpu       = true;
    bool flash_attn    = false;

    std::string language  = "en";
    std::string model     = MODELS_PATH"/ggml-medium.en.bin";
    std::string fname_out;
};


class Model : public QObject {
    Q_OBJECT

public:
    Model();
    void start(int mic_dev); // inicia el loop
    QString get_last_transcription(){return last_transcription;}
    std::list<std::pair<int, std::string>> get_mic_devices();
    void stop_transcription();

private
    slots:
    void handleMessage(const QString &msg) {
    std::cout << msg.toStdString() << std::endl;
    last_transcription = msg;
    emit update();
    }

    signals:
        void update();

private:
    Worker* worker;
    QThread workerThread;
    QString last_transcription;
    std::list<std::pair<int, std::string>> mic_devices;

};


class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(int mic_dev) : QObject(nullptr), m_stop(false) {setup_capture(mic_dev);}
    int setup_capture(int mic_dev);

public slots:
    void doWork();
    void stopWork() {
        m_stop = true;
    }
    signals:
    void conditionMessage(const QString &message);
    void finished();

private:

    std::atomic<bool> m_stop;

    whisper_params params;
    wav_writer wavWriter;

    int n_samples_step;
    int n_samples_len;
    int n_samples_keep;
    int n_samples_30s;
    bool use_vad;
    int n_new_line;

    std::vector<float> pcmf32;
    std::vector<float> pcmf32_old;
    std::vector<float> pcmf32_new;

    bool is_running;
    audio_async* audio;
    std::chrono::time_point<std::chrono::system_clock> t_last, t_start;

    std::vector<whisper_token> prompt_tokens;
    int n_iter;
    std::ofstream fout;

    struct whisper_context *ctx;
};

#endif // MODEL_H
