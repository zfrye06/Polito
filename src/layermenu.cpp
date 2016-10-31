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
    //groupBox->setContentsMargins(0,0,0,0);
    //groupBox->setCheckable(true);

    //layers.push_back(groupBox);

    QLineEdit* label = new QLineEdit(layerName);
    label->setParent(groupBox);
    layerNames.push_back(layerName);
    connect(label, &QLineEdit::textEdited, this, &LayerMenu::textEditedSlot);
    //cursorPositionChanged here just means "when text box is clicked."
    connect(label, &QLineEdit::cursorPositionChanged, this, &LayerMenu::activeLayerChanged);

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

    QGridLayout* hbox = new QGridLayout();
    hbox->addWidget(label, 0, 0, 1, 3, Qt::AlignCenter);
    hbox->addWidget(moveLayerUpButton, 1, 0);
    hbox->addWidget(moveLayerDownButton, 1, 1);
    hbox->addWidget(deleteLayerButton, 1, 2);

    groupBox->setLayout(hbox);

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

void LayerMenu::activeLayerChanged(){
    int oldActiveLayerIndex = indexOfActiveLayer;
    QGroupBox* thisBox = qobject_cast<QGroupBox*>(sender()->parent());
    indexOfActiveLayer = getIndex(thisBox);
    if (oldActiveLayerIndex != indexOfActiveLayer){
        QGroupBox* oldBox = getBox(oldActiveLayerIndex);
        highlightGroupBox(thisBox);
        unhighlightGroupBox(oldBox);
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

    //Now swap the text in the QLineEdits
    QLineEdit* thisLineEdit;
    foreach(QObject* qo, thisBox->children()){
        thisLineEdit = qobject_cast<QLineEdit*>(qo);
        break; //just get the first child; I don't know a better way to do this.
    }

    QLineEdit* otherLineEdit;
    foreach(QObject* qo, otherBox->children()){
        otherLineEdit = qobject_cast<QLineEdit*>(qo);
        break; //just get the first child; I don't know a better way to do this.
    }

    thisLineEdit->setText(layerNames[index1]);
    otherLineEdit->setText(layerNames[index2]);

    //Now swap the GroupBoxWidgets
    layerMenuLayout->removeWidget(thisBox);
    layerMenuLayout->removeWidget(otherBox);
    layerMenuLayout->insertWidget(index1, otherBox);
    layerMenuLayout->insertWidget(index2, thisBox);

    //    QMessageBox::information(
    //         this,
    //         tr("Index is"),
    //         tr(std::to_string(index1).c_str()) );

    //Finally, if we swapped the active layer, highlight it
    //in its new position and emit an activeLayerChangedSignal
    if (index1 == indexOfActiveLayer){
        unhighlightGroupBox(getBox(indexOfActiveLayer));
        indexOfActiveLayer = index2;
        highlightGroupBox(getBox(indexOfActiveLayer));
        emit activeLayerChangedSignal(indexOfActiveLayer);
    }
    emit layersSwappedSignal(index1, index2);
}
