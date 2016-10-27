#include "toolbar.h"
#include <QObject>

Toolbar::Toolbar(QWidget *parent) : QWidget(parent){
    initWidgets();
    initConnections();
    setParent(parent);
}

void Toolbar::initWidgets(){
    QSize size = QSize(40, 40);
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

    brushButton->setFixedSize(size);
    fillButton->setFixedSize(size);
    moveButton->setFixedSize(size);
    colorButton->setFixedSize(size);

    brushButton->setIcon(brushIcon);
    moveButton->setIcon(moveIcon);
    fillButton->setIcon(fillIcon);
    colorButton->setIcon(colorIcon);

    buttonGroup->addButton(brushButton);
    buttonGroup->addButton(moveButton);
    buttonGroup->addButton(fillButton);
    buttonGroup->setExclusive(true);

    toolsLayout->addWidget(brushButton);
    toolsLayout->addWidget(moveButton);
    toolsLayout->addWidget(fillButton);
    toolsLayout->addWidget(colorButton);
}

void Toolbar::initConnections(){
    //connect(colorButton, &QPushButton::pressed, colorPicker, &QColorDialog::open(&Toolbar::colorPicked));
}

QColor Toolbar::colorPicked(){
    return nullptr;
}
