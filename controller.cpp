#include "controller.h"
#include "model.h"
#include "view.h"

Controller::Controller(Model* model, View* view, QObject* parent)
    : QObject(parent), m_model(model), m_view(view) {
    connect(m_model, &Model::dataUpdated, this, &Controller::handleDataUpdate);
}

void Controller::handleDataUpdate(int value) {
    m_view->updateLabel(value); // Actualiza la vista
}
