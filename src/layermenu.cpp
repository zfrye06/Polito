#include "layermenu.h"
#include <vector>
#include <QMessageBox>
#include <QLineEdit>
#include <QPalette>
#include <QLabel>
#include <QIcon>
#include <QPixmap>

LayerMenu::LayerMenu(QWidget *parent) : QWidget(parent) {

    addLayerButton = new QPushButton(this);
    addLayerButton->setText("Add Layer");
    connect(addLayerButton, &QPushButton::released,this, &LayerMenu::addLayerButtonClicked);

    layerMenuLayout = new QVBoxLayout();
    layerMenuLayout->setAlignment(Qt::AlignTop);
    layerMenuLayout->addWidget(addLayerButton);
    this->setLayout(layerMenuLayout);

    addLayer("Layer1");
    //We initialize the active layer to be 0:
    indexOfActiveLayer = 0;
    highlightGroupBox(getBox(0));
    emit activeLayerChangedSignal(indexOfActiveLayer);
}

void LayerMenu::addLayer(QString layerName){
    QGroupBox* groupBox = new QGroupBox();
    groupBox->setParent(this);

    QLineEdit* label = new QLineEdit(layerName);
    label->setParent(groupBox);
    layerNames.push_back(layerName);
    connect(label, &QLineEdit::textEdited, this, &LayerMenu::textEditedSlot);
    //cursorPositionChanged here is just used for "when text box is clicked"
    //since there's no "released" event in QLineEdit
    connect(label, &QLineEdit::cursorPositionChanged, this, &LayerMenu::textBoxClicked);

    QPushButton* moveLayerUpButton = new QPushButton();
    moveLayerUpButton->setIcon(upArrow);
    moveLayerUpButton->setParent(groupBox);
    connect(moveLayerUpButton, &QPushButton::released,this, &LayerMenu::moveLayerUpButtonClicked);

    QPushButton* moveLayerDownButton = new QPushButton();
    moveLayerDownButton->setIcon(downArrow);
    moveLayerDownButton->setParent(groupBox);
    connect(moveLayerDownButton, &QPushButton::released,this, &LayerMenu::moveLayerDownButtonClicked);

    QPushButton* deleteLayerButton = new QPushButton();
    deleteLayerButton->setIcon(deleteX);
    deleteLayerButton->setParent(groupBox);
    connect(deleteLayerButton, &QPushButton::released, this, &LayerMenu::deleteLayerButtonClicked);

    QGridLayout* gridBox = new QGridLayout();
    gridBox->addWidget(label, 0, 0, 1, 3, Qt::AlignCenter);
    gridBox->addWidget(moveLayerUpButton, 1, 0);
    gridBox->addWidget(moveLayerDownButton, 1, 1);
    gridBox->addWidget(deleteLayerButton, 1, 2);

    groupBox->setLayout(gridBox);

    layerMenuLayout->addWidget(groupBox);

    int indexOfAddedLayer = getIndex(groupBox);
    emit layerAddedSignal(indexOfAddedLayer);
}

int LayerMenu::getIndex(QGroupBox* thisBox){
    //Because the "Add Layer" button is the first widget
    //in layerMenuLayout, we must subtract 1 to get the index of
    //a QGroupBox counting from 0.
    return layerMenuLayout->indexOf(thisBox) - 1;
}

QGroupBox* LayerMenu::getBox(int index){
    //Because the "Add Layer" button is the first widget
    //in layerMenuLayout, we must add 1 to get the
    //a QGroupBox counting from index 0.
    return qobject_cast<QGroupBox*>(layerMenuLayout->itemAt(index + 1)->widget());
}

void LayerMenu::textBoxClicked(){
    int oldActiveLayerIndex = indexOfActiveLayer;
    QGroupBox* thisBox = qobject_cast<QGroupBox*>(sender()->parent());
    indexOfActiveLayer = getIndex(thisBox);
    if (oldActiveLayerIndex != indexOfActiveLayer){
        QGroupBox* oldBox = getBox(oldActiveLayerIndex);
        unhighlightGroupBox(oldBox);
        highlightGroupBox(thisBox);
        emit activeLayerChangedSignal(indexOfActiveLayer);
    }
}

void LayerMenu::highlightGroupBox(QGroupBox* newActiveLayerBox){
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, QColor(110,135,255,100));
    newActiveLayerBox->setAutoFillBackground(true);
    newActiveLayerBox->setPalette(Pal);
    newActiveLayerBox->show();
}

void LayerMenu::unhighlightGroupBox(QGroupBox* oldActiveLayerBox){
    oldActiveLayerBox->setAutoFillBackground(false);
    oldActiveLayerBox->setPalette(oldActiveLayerBox->style()->standardPalette());
    oldActiveLayerBox->show();
}

void LayerMenu::deleteLayer(QGroupBox* layerToBeDeleted)
{
    if (layerNames.size() == 1) {
        return;
    }
    int index = getIndex(layerToBeDeleted);
    layerNames.remove(index);
    layerMenuLayout->removeWidget(layerToBeDeleted);
    foreach(QObject* child, layerToBeDeleted->children()){
        delete child;
    }
    delete layerToBeDeleted;
    emit layerDeletedSignal(index);
    if (index == indexOfActiveLayer){
        indexOfActiveLayer = index < layerNames.size() ? index : index - 1;
        highlightGroupBox(getBox(indexOfActiveLayer));
        emit activeLayerChangedSignal(indexOfActiveLayer);
    }
}

void LayerMenu::addLayerButtonClicked() {
    addLayer("New Layer");
}

void LayerMenu::deleteLayerButtonClicked() {
    deleteLayer(qobject_cast<QGroupBox*>(sender()->parent()));
}

void LayerMenu::textEditedSlot(){
    QString newText = qobject_cast<QLineEdit*>(sender())->text();
    QGroupBox* thisBox = qobject_cast<QGroupBox*>(sender()->parent());
    int index = getIndex(thisBox);
    layerNames[index] = newText;
}

void LayerMenu::moveLayerUpButtonClicked(){
    QGroupBox* thisBox = qobject_cast<QGroupBox*>(sender()->parent());
    int index = getIndex(thisBox);
    //        QMessageBox::information(
    //            this,
    //            tr("Index is"),
    //            tr(std::to_string(index).c_str()) );
    if (index > 0){
        swapLayers(index, index-1, thisBox);
    }
}

void LayerMenu::moveLayerDownButtonClicked(){
    QGroupBox* thisBox = qobject_cast<QGroupBox*>(sender()->parent());
    int index = getIndex(thisBox);
    if (index < layerNames.size() - 1){
        swapLayers(index, index+1, thisBox);
    }
}

void LayerMenu::swapLayers(int index1, int index2, QGroupBox* thisBox){

    QGroupBox* otherBox = getBox(index2);

    //First swap the strings in layerNames
    QString temp = layerNames[index1];
    layerNames[index1] = layerNames[index2];
    layerNames[index2] = temp;

    QLineEdit* thisLineEdit = qobject_cast<QLineEdit*>(thisBox->layout()->itemAt(0)->widget());
    QLineEdit* otherLineEdit = qobject_cast<QLineEdit*>(otherBox->layout()->itemAt(0)->widget());

    thisLineEdit->setText(layerNames[index2]);
    otherLineEdit->setText(layerNames[index1]);

    //Now swap the GroupBoxWidgets
    int thisInsertionPoint = layerMenuLayout->indexOf(thisBox);
    layerMenuLayout->removeWidget(thisBox);
    if (index1 < index2){ //move down
        layerMenuLayout->insertWidget(thisInsertionPoint + 1, thisBox);
        if (index1 == indexOfActiveLayer){
            indexOfActiveLayer++;
            emit activeLayerChangedSignal(indexOfActiveLayer);
        }
        else if (index2 == indexOfActiveLayer){
            indexOfActiveLayer--;
            emit activeLayerChangedSignal(indexOfActiveLayer);
        }
    }
    else{//move up
        layerMenuLayout->insertWidget(thisInsertionPoint - 1, thisBox);
        if (index1 == indexOfActiveLayer){
            indexOfActiveLayer--;
            emit activeLayerChangedSignal(indexOfActiveLayer);
        }
        else if (index2 == indexOfActiveLayer){
            indexOfActiveLayer++;
            emit activeLayerChangedSignal(indexOfActiveLayer);
        }
        emit activeLayerChangedSignal(indexOfActiveLayer);
    }
    //    QMessageBox::information(
    //         this,
    //         tr("Index is"),
    //         tr(std::to_string(index1).c_str()) );

    //Finally, if we swapped the active layer, highlight it
    //in its new position and emit an activeLayerChangedSignal

    emit layersSwappedSignal(index1, index2);
}
