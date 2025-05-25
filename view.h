#ifndef VIEW_H
#define VIEW_H
#include "TransparentWindow.cpp"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "test/TransparentLabel.h"
class View : public TransparentWindow {
    Q_OBJECT

public:
    View(QWidget* parent = nullptr);

    void updateLabel(QString&); // interfaz para actualizar la vista

    QLabel* label;

    void bringToFront();
};

#endif // VIEW_H
