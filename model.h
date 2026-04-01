#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <list>
#include <string>

#include <QObject>
#include <QString>
#include <QThread>

class Worker;

class Model : public QObject {
    Q_OBJECT

public:
    Model();
    void start(int mic_dev);
    QString get_last_transcription() { return last_transcription; }
    std::list<std::pair<int, std::string>> get_mic_devices();
    void stop_transcription();

signals:
    void update();

private slots:
    void handleMessage(const QString &msg) {
        std::cout << msg.toStdString() << std::endl;
        last_transcription = msg;
        emit update();
    }

private:
    Worker* worker;
    QThread workerThread;
    QString last_transcription;
    std::list<std::pair<int, std::string>> mic_devices;
};

#endif // MODEL_H
