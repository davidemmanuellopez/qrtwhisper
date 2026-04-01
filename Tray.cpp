#include "Tray.h"

#include <QFile>
#include <QMenu>

Tray::Tray() {
    if (QFile::exists("tray_icon.png")) {
        setIcon(QIcon("tray_icon.png"));
    }

    menu = new QMenu();
    setContextMenu(menu);
}

void Tray::addMenuAction(const QString &text, std::function<void()> callback) {
    menu->addAction(text, callback);
}
