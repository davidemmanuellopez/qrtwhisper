#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QTimer>

class Model : public QObject {
    Q_OBJECT

public:
    Model(QObject* parent = nullptr);

    void start(); // inicia el loop
    void start_capture_loop();

    signals:
        void dataUpdated(int value); // señal que emite datos nuevos

private slots:
    void update(); // función llamada por el timer

private:
    QTimer timer;
    int counter = 0;
};

#endif // MODEL_H
