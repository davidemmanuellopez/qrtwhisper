#include "view.h"

View::View(QWidget* parent) : QObject(parent) {
    label = new TransparentLabel();
}

void View::updateLabel(QString& str) {
    label->setText(str);
    label->adjustSize();
}
