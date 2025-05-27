#ifndef TEXTRENDER_H
#define TEXTRENDER_H
#include "TransparentWindow.cpp"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "test/TransparentLabel.h"
class TextRender : public TransparentWindow {
    Q_OBJECT

public:
    TextRender(QWidget* parent = nullptr);

    void updateLabel(QString&); // interfaz para actualizar la vista

    QLabel* label;

    void bringToFront();
};

#endif // TEXTRENDER_H
