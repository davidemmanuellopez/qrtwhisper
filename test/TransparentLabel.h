//
// Created by david on 24/05/25.
//

#ifndef TRANSPARENTLABEL_H
#define TRANSPARENTLABEL_H

#include <QGraphicsOpacityEffect>
#include <QGuiApplication>
#include <QScreen>

#include <QPainter>
class TransparentLabel : public QLabel {
public:
    TransparentLabel(QWidget *parent = nullptr) : QLabel(parent) {
        // Configuración de ventana flotante
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool |  Qt::X11BypassWindowManagerHint);
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_TransparentForMouseEvents);

        setWindowFlag(Qt::Window, true);
        setAttribute(Qt::WA_ShowWithoutActivating);
        setFocusPolicy(Qt::NoFocus);

        // Estilo del texto
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        setFont(font);

        QPalette palette;
        palette.setColor(QPalette::WindowText, Qt::white);
        setPalette(palette);

        // Sombra para mejor legibilidad
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(10);
        shadow->setColor(Qt::black);
        shadow->setOffset(2, 2);
        setGraphicsEffect(shadow);

        // Asegurar que tiene un tamaño inicial
        setText("Sample Text"); // Texto temporal para calcular tamaño
        adjustSize();
    }

    // Método para posicionar en coordenadas absolutas de pantalla
    void setScreenPosition(int x, int y) {
        // Ajustar posición si el texto es muy largo
        QScreen *screen = QGuiApplication::screenAt(QPoint(x, y));
        if (screen) {
            QRect screenGeometry = screen->geometry();
            if (x + width() > screenGeometry.right()) {
                x = screenGeometry.right() - width();
            }
            if (y + height() > screenGeometry.bottom()) {
                y = screenGeometry.bottom() - height();
            }
        }

        move(x, y);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        // Fondo completamente transparente
        QPainter painter(this);
        painter.setCompositionMode(QPainter::CompositionMode_Clear);
        painter.fillRect(rect(), Qt::transparent);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

        QLabel::paintEvent(event);
    }
};



#endif //TRANSPARENTLABEL_H
