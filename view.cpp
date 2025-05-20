#include "view.h"

View::View(QWidget* parent) : QWidget(parent) {
    label = new QLabel("Valor inicial: 0", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);

    setLayout(layout);
    setWindowTitle("MVC Qt6 App");
    resize(300, 100);
}

void View::updateLabel(int value) {
    label->setText(QString("Valor: %1").arg(value));
}
