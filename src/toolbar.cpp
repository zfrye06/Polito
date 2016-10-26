#include "toolbar.h"
#include <QObject>

Toolbar::Toolbar(QWidget *parent) : QWidget(parent){
    initWidgets(parent);
    initConnections();
}

void Toolbar::initWidgets(QWidget *parent){
    toolsLayout = new QVBoxLayout(parent);
    buttonGroup = new QButtonGroup(parent);

    moveButton = new QPushButton;
    brushButton = new QPushButton;
    fillButton = new QPushButton;
    colorButton = new QPushButton;

//    fillButton->setCheckable(true);
//    brushButton->setCheckable(true);
//    moveButton->setCheckable(true);
//    colorButton->setCheckable(true);

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
