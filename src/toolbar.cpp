#include "toolbar.h"
#include <QObject>

Toolbar::Toolbar(QWidget *parent) : QWidget(parent){
    initWidgets();
    initConnections();
}

void Toolbar::initWidgets(){
    toolsLayout = new QVBoxLayout;

    moveButton = new QPushButton;
    brushButton = new QPushButton;
    fillButton = new QPushButton;
    colorButton = new QPushButton;
    currentButton = brushButton;

    fillButton->setCheckable(true);
    brushButton->setCheckable(true);
    moveButton->setCheckable(true);
    colorButton->setCheckable(true);

    currentButton->setChecked(true);
}

void Toolbar::initConnections(){
    connect(moveButton, &QPushButton::toggled(), this, &setCheckedButtons());
    connect(brushButton, &QPushButton::toggled(), this, &setCheckedButtons());
    connect(fillButton, &QPushButton::toggled(), this, &setCheckedButtons());
    connect(colorButton, &QPushButton::toggled(), this, &setCheckedButtons());

}

void Toolbar::setCheckedButtons(){
    if(((QPushButton*) QObject::sender())->isChecked()){
    }
    else{
        currentButton->setChecked(false);
        currentButton = (QPushButton*) QObject::sender();
        currentButton->setChecked(true);
    }
}
