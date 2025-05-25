#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QScreen>

#include <QWindow>
#include <qpa/qplatformwindow.h>

void forceClickThrough(QWidget* widget) {
    widget->createWinId();
    QWindow* window = widget->windowHandle();
    if (window) {
        window->setFlags(window->flags() | Qt::WindowTransparentForInput);
    }
}


class ClickThroughWidget : public QWidget {
public:
    ClickThroughWidget(QWidget* parent = nullptr) : QWidget(parent) {
        // Configuración esencial para ventana transparente
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
        setAttribute(Qt::WA_TranslucentBackground);

        // Hacer completamente transparente a eventos del mouse
        setAttribute(Qt::WA_TransparentForMouseEvents);

        // Cubrir toda la pantalla
        setGeometry(QGuiApplication::primaryScreen()->geometry());
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 1. Crear widget padre transparente y click-through
    ClickThroughWidget screenContainer;

    // 2. Crear QLabel hijo (también click-through)
    QLabel* label = new QLabel("Texto no interactivo", &screenContainer);
    label->setStyleSheet(
        "QLabel {"
        "color: white;"
        "font-size: 24px;"
        "background-color: rgba(0, 0, 0, 150);"
        "padding: 10px;"
        "border-radius: 5px;"
        "}"
    );
    label->setAlignment(Qt::AlignCenter);
    label->resize(300, 100);
    label->move(100, 100);

    // 3. Configurar el label para ignorar eventos del mouse
    label->setAttribute(Qt::WA_TransparentForMouseEvents);

    // 4. Mostrar
    screenContainer.show();
    // Llamar después de show():
    forceClickThrough(&screenContainer);

    return app.exec();
}