#include "toolbar.h"
#include <QObject>
#include <QPalette>

Toolbar::Toolbar(QWidget *parent) : QWidget(parent){
    this->initWidgets();
    this->initConnections();
    this->setParent(parent);
}

Toolbar::~Toolbar(){
    delete lineButton;
    delete moveButton;
    delete brushButton;
    delete eraseButton;
    delete fillButton;
    delete colorButton;
    delete circleButton;
    delete squareButton;
    delete buttonGroup;
    delete toolsLayout;
    delete colorPicker;
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
    colorButton = new QPushButton();

    moveButton->setToolTip("Pan Tool");
    brushButton->setToolTip("Paintbrush");
    eraseButton->setToolTip("Eraser");
    fillButton->setToolTip("Fill");
    colorButton->setToolTip("Color Picker");

    QPalette pal;
    pal.setColor(QPalette::Button, Qt::red);
    colorButton->setFlat(true);
    colorButton->setAutoFillBackground(true);
    colorButton->setPalette(pal);
    colorButton->update();

    circleButton = new QPushButton(circleIcon, "");
    lineButton = new QPushButton(lineIcon, "");
    squareButton = new QPushButton(squareIcon, "");

    circleButton->setToolTip("Circle Tool");
    lineButton->setToolTip("Line Tool");
    squareButton->setToolTip("Square Tool");

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

    toolsLayout->addWidget(colorButton);
    toolsLayout->addWidget(brushButton);
    toolsLayout->addWidget(eraseButton);
    toolsLayout->addWidget(moveButton);
    toolsLayout->addWidget(fillButton);
    toolsLayout->addWidget(circleButton);
    toolsLayout->addWidget(squareButton);
    toolsLayout->addWidget(lineButton);

}

void Toolbar::initConnections(){
    connect(colorButton, &QPushButton::clicked, this, &Toolbar::getColor);
    connect(eraseButton, &QPushButton::clicked, this, &Toolbar::setEraser);
    connect(moveButton, &QPushButton::clicked, this, &Toolbar::setMove);
    connect(brushButton, &QPushButton::clicked, this, &Toolbar::setBrush);
    connect(fillButton, &QPushButton::clicked, this, &Toolbar::setFill);
    connect(squareButton, &QPushButton::clicked, this, &Toolbar::setSquare);
    connect(circleButton, &QPushButton::clicked, this, &Toolbar::setCircle);
    connect(lineButton, &QPushButton::clicked, this, &Toolbar::setLine);
}

void Toolbar::setBrush() {
    brushButton->setChecked(true);
    emit setPaintHandler( new PaintBrush() );
}

void Toolbar::setMove() {
    moveButton->setChecked(true);
    emit setPaintHandler( new PanTool() );
}

void Toolbar::setEraser() {
    eraseButton->setChecked(true);
    emit setPaintHandler( new Eraser() );
}

void Toolbar::setFill() {
    fillButton->setChecked(true);
    emit setPaintHandler( new PaintBucket() );
}

void Toolbar::setSquare(){
    squareButton->setChecked(true);
    emit setPaintHandler( new PaintSquare() );
}

void Toolbar::setCircle(){
    circleButton->setChecked(true);
    emit setPaintHandler( new PaintCircle() );
}

void Toolbar::setLine(){
    lineButton->setChecked(true);
    emit setPaintHandler( new PaintLine() );
}

void Toolbar::getColor(){
    QColor newColor = colorPicker->getColor();

    QPalette pal = colorButton->palette();
    pal.setColor(QPalette::Button, newColor);
    colorButton->setPalette(pal);
    colorButton->update();

    emit colorChanged(newColor);
}
