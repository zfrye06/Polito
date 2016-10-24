//#include "toolbar.h"
//#include <QObject>

//Toolbar::Toolbar(QWidget *parent) : QWidget(parent){
//    initWidgets();
//    initConnections();
//}

//void Toolbar::initWidgets(){
//    toolsLayout = new QVBoxLayout;

//    moveButton = new QPushButton;
//    brushButton = new QPushButton;
//    fillButton = new QPushButton;
//    colorButton = new QPushButton;
//    currentButton = brushButton;

//    fillButton->setCheckable(true);
//    brushButton->setCheckable(true);
//    moveButton->setCheckable(true);
//    colorButton->setCheckable(true);
//}

//void Toolbar::initConnections(){
//    connect(moveButton, &QPushButton::toggled(moveButton->isChecked()), this, &setCheckedButtons(moveButton->isChecked()));
//    connect(brushButton, &QPushButton::toggled(brushButton->isChecked()), this, &setCheckedButtons(brushButton->isChecked()));
//    connect(fillButton, &QPushButton::toggled(fillButton->isChecked()), this, &setCheckedButtons(fillButton->isChecked()));
//    connect(colorButton, &QPushButton::toggled(colorButton->isChecked()), this, &setCheckedButtons(colorButton->isChecked()));

//}

//void Toolbar::setCheckedButtons(bool checked){
//    if(checked){
//        currentButton->setChecked(true);
//    }
//    else{
//        currentButton->setChecked(false);
//        currentButton = (QPushButton*) QObject::sender();
//        currentButton->setChecked(true);
//    }
//}
