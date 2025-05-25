#include <QApplication>
#include "model.h"
#include "controller.h"
#include "view.h"
#include <QGuiApplication>
#include <QScreen>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Model model;
    View view;
    Controller controller(&model, &view);
    model.start();  // inicia el loop

    // Mostrar el label
    view.label->show();
    return app.exec();
}

