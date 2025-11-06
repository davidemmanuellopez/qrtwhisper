//
// Created by david on 27/05/25.
//

#ifndef TRAY_H
#define TRAY_H
#include <QTimer>
#include <qt6/QtWidgets/QApplication>
#include <qt6/QtWidgets/QSystemTrayIcon>

class Controller;

class Tray : public QSystemTrayIcon {
public:
    Tray();
    // Sobrescribe showMessage() para borrar notificaciones previas
    void showMessage(const QString &title, const QString &message,
                    QSystemTrayIcon::MessageIcon icon = Information,
                    int timeoutMs = 5000) {
        // Workaround para borrar notificación previa
        /*
        if (m_notificationVisible) {
            hide();  // Ocultar el icono fuerza la limpieza de notificaciones
            show();  // Mostrar nuevamente
            m_notificationVisible = false;
        }
        */
        // Llamar al showMessage() original de QSystemTrayIcon
        QSystemTrayIcon::showMessage(title, message, icon, timeoutMs);
        m_notificationVisible = true;

        // Opcional: Resetear estado después del timeout
        /*
        QTimer::singleShot(timeoutMs, [this]() {
            m_notificationVisible = false;
        });*/
    }
private:
    bool m_notificationVisible = false;
    QMenu* menu;
    friend Controller;

};


#endif //TRAY_H
