#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QScreen>
#include <QWindow>

class TransparentWindow : public QWidget {
public:
    TransparentWindow(QWidget* parent = nullptr) : QWidget(parent) {
        // Configuración básica de ventana transparente
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Window);
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_ShowWithoutActivating);
        setFocusPolicy(Qt::NoFocus);

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
