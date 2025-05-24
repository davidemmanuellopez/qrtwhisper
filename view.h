#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "TransparentLabel.h"
class View : public QObject {
    Q_OBJECT

public:
    View(QWidget* parent = nullptr);

    void updateLabel(QString&); // interfaz para actualizar la vista

    TransparentLabel* label;
};

#endif // VIEW_H
