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
    eraseButton = new QPushButton;
    fillButton = new QPushButton;
    colorButton = new QPushButton;

    fillButton->setCheckable(true);
    brushButton->setCheckable(true);
    eraseButton->setCheckable(true);
    moveButton->setCheckable(true);

    brushButton->setFixedSize(size);
    eraseButton->setFixedSize(size);
    fillButton->setFixedSize(size);
    moveButton->setFixedSize(size);
    colorButton->setFixedSize(size);

    brushButton->setIcon(brushIcon);
    moveButton->setIcon(moveIcon);
    eraseButton->setIcon(eraseIcon);
    fillButton->setIcon(fillIcon);
    colorButton->setIcon(colorIcon);

    buttonGroup->addButton(brushButton);
    buttonGroup->addButton(moveButton);
    buttonGroup->addButton(eraseButton);
    buttonGroup->addButton(fillButton);
    buttonGroup->setExclusive(true);

    toolsLayout->addWidget(brushButton);
    toolsLayout->addWidget(eraseButton);
    toolsLayout->addWidget(moveButton);
    toolsLayout->addWidget(fillButton);
    toolsLayout->addWidget(colorButton);
}

void Toolbar::initConnections(){
    connect(colorButton, &QPushButton::pressed, this, &Toolbar::getColor);
    connect(eraseButton, &QPushButton::pressed, this, &Toolbar::setEraser);
    connect(brushButton, &QPushButton::pressed, this, &Toolbar::setBrush);
    connect(fillButton, &QPushButton::pressed, this, &Toolbar::setFill);
}

void Toolbar::setBrush() {
    emit setPaintHandler( new PaintBrush() );
}

void Toolbar::setEraser() {
    emit setPaintHandler( new Eraser() );
}

void Toolbar::setFill() {
    emit setPaintHandler( new PaintBucket() );
}

void Toolbar::getColor(){
    currentColor = colorPicker->getColor();
    emit colorChanged(currentColor);
}
