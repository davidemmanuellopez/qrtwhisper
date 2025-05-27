#include <QApplication>
#include "model.h"
#include "controller.h"
#include "TextRender.h"
#include <QGuiApplication>
#include <QScreen>

#include "MainWidget.h"
#include "TrayApp.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Model m_model;
    View view;
    Controller controller(&m_model, &view);

    // Mostrar el label

    controller.start_main();

    return app.exec();
}

