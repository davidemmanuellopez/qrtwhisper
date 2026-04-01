#include "model.h"
#include "Worker.h"

#include "common-sdl.h"

#include <iostream>

Model::Model() : QObject(nullptr) {
}

void Model::start(int mic_dev) {
    worker = new Worker(mic_dev);
    worker->moveToThread(&workerThread);
    connect(worker, &Worker::conditionMessage, this, &Model::handleMessage);
    connect(&workerThread, &QThread::started, worker, &Worker::doWork);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(worker, &Worker::finished, &workerThread, &QThread::quit);

    workerThread.start();
}

std::list<std::pair<int, std::string>> Model::get_mic_devices() {
    mic_devices.clear();
    SDL_Init(SDL_INIT_AUDIO);
    int num_devices = SDL_GetNumAudioDevices(SDL_TRUE);
    for (int i = 0; i < num_devices; i++) {
        mic_devices.push_back(std::make_pair(i, SDL_GetAudioDeviceName(i, SDL_TRUE)));
    }
    SDL_Quit();
    return mic_devices;
}

void Model::stop_transcription() {
    worker->stopWork();
    workerThread.quit();
    workerThread.wait();
}