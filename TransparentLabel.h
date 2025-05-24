//
// Created by david on 24/05/25.
//

#ifndef TRANSPARENTLABEL_H
#define TRANSPARENTLABEL_H

#include <QGraphicsOpacityEffect>

class TransparentLabel : public QLabel {
public:
    TransparentLabel(QWidget *parent = nullptr) : QLabel(parent) {
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_TransparentForMouseEvents);
        //setAlignment(Qt::AlignCenter);

        // Estilo moderno del texto
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        setFont(font);

        // Color del texto
        QPalette palette;
        palette.setColor(QPalette::WindowText, Qt::white);
        setPalette(palette);

        // Sombra para mejor legibilidad (sin fondo)
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(10);
        shadow->setColor(Qt::black);
        shadow->setOffset(2, 2);
        setGraphicsEffect(shadow);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        // Eliminamos el dibujo del fondo redondeado
        QLabel::paintEvent(event);
    }
};



#endif //TRANSPARENTLABEL_H
