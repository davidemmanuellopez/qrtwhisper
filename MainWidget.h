//
// Created by david on 25/05/25.
//

#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <qboxlayout.h>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>


class Controller;

class MainWidget : public QWidget{

public:
    MainWidget();
    void add_mic_dev(QString &dev_name);
    int get_device_selected();
private:
    QHBoxLayout layout;
    QVBoxLayout v_layout;
    QComboBox q_device_selection;
    QPushButton start_button;
    friend Controller;

};



#endif //MAINWIDGET_H
