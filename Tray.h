//
// Created by david on 27/05/25.
//

#ifndef TRAY_H
#define TRAY_H
#include <qt6/QtWidgets/QApplication>
#include <qt6/QtWidgets/QSystemTrayIcon>


class Controller;

class Tray : public QSystemTrayIcon {
public:
    Tray();
private:
    QMenu* menu;
    friend Controller;

};


#endif //TRAY_H
