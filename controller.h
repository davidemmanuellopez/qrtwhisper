#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Model;
class View;

class Controller : public QObject {
    Q_OBJECT

public:
    Controller(Model* model, View* view, QObject* parent = nullptr);

private slots:
    void handleDataUpdate(int value);

private:
    Model* m_model;
    View* m_view;
};

#endif // CONTROLLER_H
