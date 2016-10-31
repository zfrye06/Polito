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
    highlightGroupBox(layers.at(0));
    emit activeLayerChangedSignal(indexOfActiveLayer);
}

void LayerMenu::addLayer(QString layerName){
    QGroupBox* groupBox = new QGroupBox();
    groupBox->setParent(this);
    //groupBox->setContentsMargins(0,0,0,0);
    //groupBox->setCheckable(true);

    layers.push_back(groupBox);

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

    int indexOfAddedLayer = layers.indexOf(groupBox);
    emit layerAddedSignal(indexOfAddedLayer);
}

void LayerMenu::activeLayerChanged(){
    int oldActiveLayerIndex = indexOfActiveLayer;
    QGroupBox* thisBox = qobject_cast<QGroupBox*>(sender()->parent());
    indexOfActiveLayer = layers.indexOf(thisBox);
    if (oldActiveLayerIndex != indexOfActiveLayer){
        QGroupBox* oldBox = layers.at(oldActiveLayerIndex);
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
    if (layers.size() == 1) {
        return;
    }
    int index = layers.indexOf(layerToBeDeleted);
    layerNames.remove(index);
    layers.remove(index);
    layerMenuLayout->removeWidget(layerToBeDeleted);
    foreach(QObject* child, layerToBeDeleted->children()){
        delete child;
    }
    delete layerToBeDeleted;
    emit layerDeletedSignal(index);
    if (index == indexOfActiveLayer){
        indexOfActiveLayer = index < layers.size() ? index : index - 1;
        highlightGroupBox(layers.at(indexOfActiveLayer));
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
    int index = layers.indexOf(thisBox);
    layerNames[index] = newText;
}

void LayerMenu::moveLayerUpButtonClicked(){
    QGroupBox* thisBox = qobject_cast<QGroupBox*>(sender()->parent());
    int index = layers.indexOf(thisBox);
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
    int index = layers.indexOf(thisBox);
    if (index < layers.size() - 1){
        swapLayers(index, index+1, thisBox);
    }
}

void LayerMenu::swapLayers(int index1, int index2, QGroupBox* thisBox){
    QString temp = layerNames[index1];
    layerNames[index1] = layerNames[index2];
    layerNames[index2] = temp;


    QGroupBox* otherBox = layers[index2];
    //use .at rather than [] to ensure a shallow copy
    layers[index1] = otherBox;
    layers[index2] = thisBox;
    //This swaps the data in the underlying data structures:


    //Now this swaps the text that appears in the LayerMenu QLineEdit widgets:
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
    //thisLineEdit->setText("test");
    otherLineEdit->setText(layerNames[index2]);
    //otherLineEdit->setText("test2");


    //    QMessageBox::information(
    //         this,
    //         tr("Index is"),
    //         tr(std::to_string(index1).c_str()) );

    if (index1 == indexOfActiveLayer){
        unhighlightGroupBox(layers[indexOfActiveLayer]);
        indexOfActiveLayer = index2;
        highlightGroupBox(layers[indexOfActiveLayer]);
        emit activeLayerChangedSignal(indexOfActiveLayer);
    }

    //std::swap(layerNames[index1], layerNames[index2]);
    //std::swap(layers[index1], layers[index2]);
    emit layersSwappedSignal(index1, index2);
}
