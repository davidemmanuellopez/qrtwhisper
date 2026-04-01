#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include <QComboBox>
#include <QPushButton>

class MainWidget : public QWidget {
    Q_OBJECT

public:
    MainWidget();
    void add_mic_dev(QString &dev_name);
    int get_device_selected();

signals:
    void startClicked();

private:
    QVBoxLayout v_layout;
    QComboBox q_device_selection;
    QPushButton start_button;
    QComboBox q_display_selection;
};

#endif // MAINWIDGET_H
