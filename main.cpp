#include <QApplication>
#include "model.h"
#include "controller.h"
#include "view.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Model model;
    View view;
    Controller controller(&model, &view);

    view.show();
    model.start();  // inicia el loop

    return app.exec();
}
//
// Created by david on 20/05/25.
//
