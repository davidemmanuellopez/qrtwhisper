#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "model.h"
#include "View.h"

class Model;
class TextRender;

class Controller : public QObject {
    Q_OBJECT

public:
    Controller(Model* model, View* view, QObject* parent = nullptr);
    void start_main();
    void start_transcription();
    void stop_transcription(){m_model->stop_transcription();};

private slots:
    void handleDataUpdate();

private:
    Model* m_model;
    View* m_view;
};

#endif // CONTROLLER_H
