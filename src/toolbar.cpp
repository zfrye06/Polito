#include "toolbar.h"
#include <QObject>

Toolbar::Toolbar(QWidget *parent) : QWidget(parent){
    initWidgets();
    initConnections();
    setParent(parent);
}

void Toolbar::initWidgets(){
    toolsLayout = new QVBoxLayout(this);
    buttonGroup = new QButtonGroup(this);
    colorPicker = new QColorDialog(this);

    moveButton = new QPushButton;
    brushButton = new QPushButton;
    fillButton = new QPushButton;
    colorButton = new QPushButton;

    fillButton->setCheckable(true);
    brushButton->setCheckable(true);
    moveButton->setCheckable(true);

    brushButton->setIcon(brushIcon);
    moveButton->setIcon(moveIcon);
    fillButton->setIcon(fillIcon);
    colorButton->setIcon(colorIcon);

    buttonGroup->addButton(fillButton);
    buttonGroup->addButton(brushButton);
    buttonGroup->addButton(moveButton);
    buttonGroup->setExclusive(true);

    toolsLayout->addWidget(fillButton);
    toolsLayout->addWidget(brushButton);
    toolsLayout->addWidget(moveButton);
    toolsLayout->addWidget(colorButton);
}

void Toolbar::initConnections(){
    //connect(colorButton, &QPushButton::pressed, colorPicker, &QColorDialog::open(&Toolbar::colorPicked));
}

QColor Toolbar::colorPicked(){
    return nullptr;
}
