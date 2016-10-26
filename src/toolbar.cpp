#include "toolbar.h"
#include <QObject>

Toolbar::Toolbar(QWidget *parent) : QWidget(parent){
    initWidgets();
    initConnections();
}

void Toolbar::initWidgets(){
    toolsLayout = new QVBoxLayout(this);
    buttonGroup = new QButtonGroup(this);

    moveButton = new QPushButton;
    brushButton = new QPushButton;
    fillButton = new QPushButton;
    colorButton = new QPushButton;

    fillButton->setCheckable(true);
    brushButton->setCheckable(true);
    moveButton->setCheckable(true);
    colorButton->setCheckable(true);

    buttonGroup->addButton(fillButton);
    buttonGroup->addButton(brushButton);
    buttonGroup->addButton(moveButton);
    buttonGroup->addButton(colorButton);
    buttonGroup->setExclusive(true);

    toolsLayout->addWidget(fillButton);
    toolsLayout->addWidget(brushButton);
    toolsLayout->addWidget(moveButton);
    toolsLayout->addWidget(colorButton);

    this->setLayout(toolsLayout);
}

void Toolbar::initConnections(){

}
