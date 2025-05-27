//
// Created by david on 25/05/25.
//

#ifndef VIEW_H
#define VIEW_H

#include <qt6/QtCore/qhash.h>
#include <qt6/QtCore/QObject>
#include <qt6/QtCore/qstring.h>
#include <qt6/QtWidgets/QStackedWidget>
#include <qt6/QtWidgets/QWidget>


class View : public QObject{

public:
    View();
    QWidget* getWidget(const QString& widget_name);
private:
    QHash<QString, QWidget*> widgetDictionary;

};



#endif //VIEW_H
