//
// Created by david on 25/05/25.
//

#include "View.h"

#include "MainWidget.h"
#include "TextRender.h"

View::View() : QObject() {
    auto text_render = new TextRender();
    auto main = new MainWidget();
    widgetDictionary[QString("TextRender")] = text_render;
    widgetDictionary[QString("Main")] = main;

}

QWidget * View::getWidget(const QString &widget_name) {
    return widgetDictionary[widget_name];
}
