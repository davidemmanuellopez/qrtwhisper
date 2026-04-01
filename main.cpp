#include <QApplication>

#include "model.h"
#include "View.h"
#include "controller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Model m_model;
    View view;
    Controller controller(&m_model, &view);

    controller.start_main();

    return app.exec();
}
