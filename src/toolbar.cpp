#include "toolbar.h"
#include <QObject>

Toolbar::Toolbar(QWidget *parent) : QWidget(parent){
    this->initWidgets();
    this->initConnections();
    this->setParent(parent);
}

void Toolbar::initWidgets(){
    QSize size = QSize(40, 40);
    toolsLayout = new QVBoxLayout(this);
    buttonGroup = new QButtonGroup(this);
    colorPicker = new QColorDialog(this);

    moveButton = new QPushButton(moveIcon, "");
    brushButton = new QPushButton(brushIcon, "");
    eraseButton = new QPushButton(eraseIcon, "");
    fillButton = new QPushButton(fillIcon, "");
    colorButton = new QPushButton(colorIcon, "");
    circleButton = new QPushButton(circleIcon, "");
    lineButton = new QPushButton(lineIcon, "");
    squareButton = new QPushButton(squareIcon, "");

    fillButton->setCheckable(true);
    brushButton->setCheckable(true);
    eraseButton->setCheckable(true);
    moveButton->setCheckable(true);
    circleButton->setCheckable(true);
    lineButton->setCheckable(true);
    squareButton->setCheckable(true);

    brushButton->setFixedSize(size);
    eraseButton->setFixedSize(size);
    fillButton->setFixedSize(size);
    moveButton->setFixedSize(size);
    colorButton->setFixedSize(size);
    circleButton->setFixedSize(size);
    squareButton->setFixedSize(size);
    lineButton->setFixedSize(size);

    buttonGroup->addButton(brushButton);
    buttonGroup->addButton(moveButton);
    buttonGroup->addButton(eraseButton);
    buttonGroup->addButton(fillButton);
    buttonGroup->addButton(circleButton);
    buttonGroup->addButton(squareButton);
    buttonGroup->addButton(lineButton);
    buttonGroup->setExclusive(true);

    toolsLayout->addWidget(brushButton);
    toolsLayout->addWidget(eraseButton);
    toolsLayout->addWidget(moveButton);
    toolsLayout->addWidget(fillButton);
    toolsLayout->addWidget(circleButton);
    toolsLayout->addWidget(squareButton);
    toolsLayout->addWidget(lineButton);
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
    emit colorChanged(colorPicker->getColor());
}
