#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class View : public QWidget {
    Q_OBJECT

public:
    View(QWidget* parent = nullptr);

    void updateLabel(int value); // interfaz para actualizar la vista

private:
    QLabel* label;
};

#endif // VIEW_H
