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

    view.label->adjustSize();
    auto screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    int x = 0;
    int y = screenGeometry.height() - view.label->height() - 100;
    //view.label->move(x, y);
    view.label->setGeometry(0, 200, 300, 50);

    // Mostrar el label
    view.label->show();
    return app.exec();
}

