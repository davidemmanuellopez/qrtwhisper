#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QWindow>
#include <QDebug>
#include  <QScreen>
class FocusAwareTransparentWindow : public QWidget {
public:
    FocusAwareTransparentWindow(QWidget* parent = nullptr) : QWidget(parent) {
        // Configuración de ventana transparente
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
        setAttribute(Qt::WA_TranslucentBackground);
        
        // Mantener el foco cuando se hace click
        setAttribute(Qt::WA_ShowWithoutActivating);
        
        // Configurar tamaño
        setGeometry(QApplication::primaryScreen()->geometry());
    }

protected:
    void showEvent(QShowEvent* event) override {
        QWidget::showEvent(event);
        
        // Configurar click-through pero mantener el foco
        if (windowHandle()) {
            windowHandle()->setFlags(windowHandle()->flags() | 
                                  Qt::WindowTransparentForInput |
                                  Qt::WindowDoesNotAcceptFocus);
        }
    }

    // Opcional: Mantener el foco activo periódicamente
    void timerEvent(QTimerEvent *event) override {
        Q_UNUSED(event)
        if (isVisible()) {
            activateWindow();
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FocusAwareTransparentWindow window;
    
    // Label con estilo
    QLabel* label = new QLabel("Ventana no interactiva\nque mantiene el foco", &window);
    label->setStyleSheet(
        "QLabel {"
        "color: white;"
        "font-size: 24px;"
        "background-color: rgba(0, 0, 0, 150);"
        "padding: 20px;"
        "border-radius: 10px;"
        "}"
    );
    label->setAlignment(Qt::AlignCenter);
    label->resize(400, 200);
    label->move(100, 100);
    label->setAttribute(Qt::WA_TransparentForMouseEvents);
    
    // Opcional: Timer para asegurar el foco (cada 500ms)
    window.startTimer(500);
    
    window.show();

    return app.exec();
}