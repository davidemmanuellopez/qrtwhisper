//
// Created by david on 25/05/25.
//

#include "MainWidget.h"

#include <QLabel>
#include <QPushButton>

MainWidget::MainWidget() {
    auto label = new QLabel("Select device:");
    start_button.setText("Start");

    auto layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(&q_device_selection);

    v_layout.addLayout(layout);

    label = new QLabel("Select display method:");
    layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(&q_display_selection);

    q_display_selection.addItem("System notification");
    q_display_selection.addItem("Subtitle");


    v_layout.addLayout(layout);


    v_layout.addWidget(&start_button);
    setLayout(&v_layout);

    connect(&start_button, &QPushButton::clicked, [this]() {
         this->start_button.setEnabled(false);  // Deshabilita el botón

     });;
}

void MainWidget::add_mic_dev(QString& dev_name) {
    q_device_selection.addItem(dev_name);
    // Seleccionar el último
    q_device_selection.setCurrentIndex(q_device_selection.count() - 1);
}

int MainWidget::get_device_selected() {
    return q_device_selection.currentIndex();
}
