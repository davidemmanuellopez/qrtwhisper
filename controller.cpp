#include "controller.h"

#include "MainWidget.h"
#include "model.h"
#include "TextRender.h"
#include "Tray.h"
#include "View.h"

Controller::Controller(Model* model, View* view, QObject* parent)
    : QObject(parent), m_model(model), m_view(view)
{
    connect(m_model, &Model::update, this, &Controller::handleDataUpdate);

    auto main_widget = m_view->getMainWidget();
    connect(main_widget, &MainWidget::startClicked, this, &Controller::start_transcription);

    m_view->getTray()->addMenuAction("Salir", [this]() {
        m_model->stop_transcription();
        exit(0);
    });
}

void Controller::start_main() {
    auto mic_devs = m_model->get_mic_devices();
    auto main_widget = m_view->getMainWidget();
    for (auto &dev : mic_devs) {
        auto name = QString::fromStdString(dev.second);
        main_widget->add_mic_dev(name);
    }
    main_widget->show();
}

void Controller::start_transcription() {
    auto main_widget = m_view->getMainWidget();
    auto dev_id = main_widget->get_device_selected();
    m_model->start(dev_id);
    main_widget->hide();
    m_view->getTray()->show();
}

void Controller::stop_transcription() {
    m_model->stop_transcription();
}

void Controller::handleDataUpdate() {
    auto str = m_model->get_last_transcription();
    m_view->getTray()->showMessage(QString("QRTWhisper"), str);
}
