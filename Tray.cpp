//
// Created by david on 27/05/25.
//

#include "Tray.h"

#include <QFile>
#include <QApplication>
#include <QMenu>

Tray::Tray() {
    /*
    QPixmap pixmap(16, 16);
    pixmap.fill(Qt::blue); // Icono azul cuadrado
    setIcon(QIcon(pixmap));
    */

    if (QFile::exists("tray_icon.png")) {
        setIcon(QIcon("tray_icon.png"));
    }


    // 4. Crear menú contextual
    menu = new QMenu();


    setContextMenu(menu);

    /*
    // 5. Mostrar notificación
    showMessage("Aplicación Tray", "La aplicación se está ejecutando",
                        QSystemTrayIcon::Information, 3000);

    // 6. Configuración importante
    app.setQuitOnLastWindowClosed(false);
    */
}
