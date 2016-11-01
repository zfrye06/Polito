#include "layermenu.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QPalette>
#include <QLabel>
#include <QIcon>

LayerMenu::LayerMenu(QWidget *parent) : QWidget(parent) {
    numLayers = 0;

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
    numLayers++;

    QGroupBox* groupBox = new QGroupBox();
    groupBox->setParent(this);

    QLineEdit* label = new QLineEdit(layerName);
    label->setParent(groupBox);
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
    if (numLayers == 1) {
        return;
    }
    numLayers--;
    int index = getIndex(layerToBeDeleted);
    layerMenuLayout->removeWidget(layerToBeDeleted);
    foreach(QObject* child, layerToBeDeleted->children()){
        delete child;
    }
    delete layerToBeDeleted;
    emit layerDeletedSignal(index);
    if (index > indexOfActiveLayer){
        return;
    }
    else if (index < indexOfActiveLayer){
        indexOfActiveLayer--;
    }
    else if (index == indexOfActiveLayer){
        indexOfActiveLayer = index < numLayers ? index : index - 1;
        highlightGroupBox(getBox(indexOfActiveLayer));
    }
    emit activeLayerChangedSignal(indexOfActiveLayer);
}

void LayerMenu::addLayerButtonClicked() {
    addLayer("New Layer");
}

void LayerMenu::deleteLayerButtonClicked() {
    deleteLayer(qobject_cast<QGroupBox*>(sender()->parent()));
}

void LayerMenu::moveLayerUpButtonClicked(){
    QGroupBox* thisBox = qobject_cast<QGroupBox*>(sender()->parent());
    int index = getIndex(thisBox);
    if (index > 0){
        swapLayers(index, index-1);
    }
}

void LayerMenu::moveLayerDownButtonClicked(){
    QGroupBox* thisBox = qobject_cast<QGroupBox*>(sender()->parent());
    int index = getIndex(thisBox);
    if (index < numLayers - 1){
        swapLayers(index, index+1);
    }
}

void LayerMenu::swapLayers(int index1, int index2){
    QGroupBox* thisBox = getBox(index1);

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
    }
    emit layersSwappedSignal(index1, index2);
}

// TODO: Implement these FrameWidget methods. These allow actions to update
// the UI state when undone.

void LayerMenu::addLayer(int index) {

}

void LayerMenu::moveLayer(int from, int to) {
    
}

void LayerMenu::removeLayer(int index) {
    
}

void LayerMenu::setActiveLayer(int index) {

}

void LayerMenu::clear() {

}
