#include "controller.h"
#include "model.h"
#include "view.h"

Controller::Controller(Model* model, View* view, QObject* parent)
    : QObject(parent), m_model(model), m_view(view) {
    connect(m_model, &Model::update, this, &Controller::handleDataUpdate);
}

void Controller::handleDataUpdate() {
    auto str = m_model->get_last_transcription();
    m_view->updateLabel(str); // Actualiza la vista
}
