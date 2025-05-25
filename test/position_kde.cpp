#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QScreen>
#include <QWindow>

class TransparentWindow : public QWidget {
public:
    TransparentWindow(QWidget* parent = nullptr) : QWidget(parent) {
        // Configuración básica de ventana transparente
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        setAttribute(Qt::WA_TranslucentBackground);

        // Cubrir toda la pantalla
        setGeometry(QApplication::primaryScreen()->geometry());
    }

protected:
    void showEvent(QShowEvent* event) override {
        QWidget::showEvent(event);

        // Configurar click-through usando QWindow
        if (windowHandle()) {
            windowHandle()->setFlags(windowHandle()->flags() | Qt::WindowTransparentForInput);
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Crear ventana transparente
    TransparentWindow window;

    // Crear QLabel
    QLabel* label = new QLabel("Texto Informativo", &window);
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
    label->setAttribute(Qt::WA_TransparentForMouseEvents);

    window.show();

    return app.exec();
}