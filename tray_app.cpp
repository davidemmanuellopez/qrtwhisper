#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
#include <QFile>

class Tray : public QSystemTrayIcon {
public:
    Tray(QApplication&);
private:

};

Tray::Tray(QApplication& app) {
    /*
    QPixmap pixmap(16, 16);
    pixmap.fill(Qt::blue); // Icono azul cuadrado
    setIcon(QIcon(pixmap));
    */

    if (QFile::exists("tray_icon.png")) {
        setIcon(QIcon("tray_icon.png"));
    }


    // 4. Crear menú contextual
    auto menu = new QMenu();
    menu->addAction("Quit", &app, &QApplication::quit);

    setContextMenu(menu);

    /*
    // 5. Mostrar notificación
    showMessage("Aplicación Tray", "La aplicación se está ejecutando",
                        QSystemTrayIcon::Information, 3000);

    // 6. Configuración importante
    app.setQuitOnLastWindowClosed(false);
    */
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 1. Verificar si el sistema soporta system tray
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(nullptr, "Error", "El sistema no soporta system tray");
        return 1;
    }

    Tray tray(app);
    // 6. Configuración importante
    app.setQuitOnLastWindowClosed(false);

    // 7. Mostrar el icono (¡después de configurar el icono!)
    tray.show();

    return app.exec();
}