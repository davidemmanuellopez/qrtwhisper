#include "controller.h"

#include "MainWidget.h"
#include "model.h"
#include "TextRender.h"
#include "View.h"
#include <QMenu>

Controller::Controller(Model* model, View* view, QObject* parent)
    : QObject(parent), m_model(model), m_view(view) {
    connect(m_model, &Model::update, this, &Controller::handleDataUpdate);
    auto main_widget = (MainWidget*) m_view->getWidget("Main");

    connect(&main_widget->start_button, &QPushButton::clicked, this, &Controller::start_transcription);

    auto tray_menu = m_view->get_tray()->menu;
    tray_menu->addAction("Salir", [model]() {
        model->stop_transcription();
        exit(0);

        // Obtenemos la instancia de QApplication y la convertimos al tipo correcto
/*
        auto qApp = qobject_cast<QApplication*>(QCoreApplication::instance());
       if(qApp) {
           qApp->quit(); // Cierre limpio de la aplicación
       }*/
   });
}

void Controller::start_main() {
    auto mic_devs = m_model->get_mic_devices();
    auto main_widget = (MainWidget*) m_view->getWidget("Main");
    for (auto dev : mic_devs) {
        auto name = QString::fromStdString(dev.second);
        main_widget->add_mic_dev(name);
    }

    main_widget->show();
}

void Controller::start_transcription() {
    auto main_widget = (MainWidget*) m_view->getWidget("Main");
    auto dev_id = main_widget->get_device_selected();
    m_model->start(dev_id);
    m_view->getWidget("TextRender")->show();
    main_widget->hide();
    m_view->get_tray()->show();
    qDebug() << "star transcription";
}

void Controller::handleDataUpdate() {
    auto str = m_model->get_last_transcription();
    auto text_render = (TextRender*) m_view->getWidget("TextRender");
    text_render->updateLabel(str); // Actualiza la vista
}
