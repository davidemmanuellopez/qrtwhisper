//
// Created by david on 27/05/25.
//

#ifndef TRAYAPP_H
#define TRAYAPP_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>

class TrayApp : public QObject
{
    Q_OBJECT
public:
    explicit TrayApp(QObject *parent = nullptr) : QObject(parent)
    {
        // Configurar el icono (asegúrate de tener un archivo icon.png en tus recursos)
        trayIcon = new QSystemTrayIcon(QIcon(":/icon.png"), this);

        if(!trayIcon->isSystemTrayAvailable()) {
            QMessageBox::critical(nullptr, "Error", "No hay soporte para system tray");
            QCoreApplication::exit(1);
        }

        // Crear menú contextual
        QMenu *menu = new QMenu();

        pauseAction = menu->addAction("Pausar");
        pauseAction->setCheckable(true);
        menu->addSeparator();
        menu->addAction("Salir", qApp, &QCoreApplication::quit);

        // Conectar señales
        connect(pauseAction, &QAction::toggled, this, &TrayApp::onPauseToggled);
        connect(trayIcon, &QSystemTrayIcon::activated, this, &TrayApp::onTrayIconActivated);

        // Configurar el icono
        trayIcon->setContextMenu(menu);
        trayIcon->show();

        // Mostrar notificación
        trayIcon->showMessage("Aplicación Tray", "La aplicación se está ejecutando en segundo plano",
                            QSystemTrayIcon::Information, 3000);
    }

private slots:
    void onPauseToggled(bool paused)
    {
        if(paused) {
            trayIcon->showMessage("Estado", "Aplicación pausada", QSystemTrayIcon::Warning);
            // Lógica de pausa aquí
        } else {
            trayIcon->showMessage("Estado", "Aplicación reanudada", QSystemTrayIcon::Information);
            // Lógica de reanudar aquí
        }
    }

    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
    {
        if(reason == QSystemTrayIcon::DoubleClick) {
            // Aquí puedes mostrar una ventana si lo deseas
            QMessageBox::information(nullptr, "Info", "Doble click detectado");
        }
    }

private:
    QSystemTrayIcon *trayIcon;
    QAction *pauseAction;
};

#endif //TRAYAPP_H
