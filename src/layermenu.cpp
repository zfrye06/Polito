#include "layermenu.h"
#include <vector>
#include <QMessageBox>
#include <QLineEdit>
#include <QPalette>
#include <QLabel>
#include <QIcon>
#include <QPixmap>

/*To do:
 * The only important information LayerMenu sends out to the model
 * is index numbers: the index of whatever layer has just been deleted,
 * added, the indexes of layers that have been swapped when one moves up or down,
 * or the index of the layer that has become the active layer. So what
 * is the best way to share this information with the model? Emit a signal
 * every time layer index information is changed? Have public instance variables
 * storing the state of each relevant index?
 * */

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
    emit activeLayerChangedSignal(indexOfActiveLayer);
}

void LayerMenu::redrawLayerMenu(){
    QVector<QString> layerNamesCopy = QVector<QString>(layerNames);
    foreach(QGroupBox* qgb, layers){
        deleteLayer(qgb);
    }
    foreach(QString qs, layerNamesCopy){
        addLayer(qs);
    }
}

void LayerMenu::addLayer(QString layerName){
    QGroupBox* groupBox = new QGroupBox();
    groupBox->setParent(this);
    //groupBox->setContentsMargins(0,0,0,0);
    //groupBox->setCheckable(true);

    layers.append(groupBox);

    QLineEdit* label = new QLineEdit(layerName);
    label->setParent(groupBox);
    layerNames.append(layerName);
    connect(label, &QLineEdit::textChanged, this, &LayerMenu::textChanged);
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
    QGroupBox* thisBox = qobject_cast<QGroupBox*>(sender()->parent());
    indexOfActiveLayer = layers.indexOf(thisBox);
    emit activeLayerChangedSignal(indexOfActiveLayer);

    //Add code to change color of QGroupBox at indexOfActiveLayer
    //layers.at(indexOfActiveLayer)->palette();
}

void LayerMenu::deleteLayer(QGroupBox* layerToBeDeleted)
{
    int index = layers.indexOf(layerToBeDeleted);
    layerNames.remove(index);
    foreach(auto child, layerToBeDeleted->children())
    {
        delete child;
    }
    layerMenuLayout->removeWidget(layerToBeDeleted);
    delete layerToBeDeleted->layout();
    delete layerToBeDeleted;
    layers.remove(index);
    emit layerDeletedSignal(index);
}

void LayerMenu::addLayerButtonClicked() {
    addLayer("New Layer");
}

void LayerMenu::deleteLayerButtonClicked() {
    deleteLayer(qobject_cast<QGroupBox*>(sender()->parent()));
}

void LayerMenu::textChanged(){
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
        QString temp = layerNames[index];
        layerNames[index] = layerNames[index-1];
        layerNames[index-1] = temp;
        redrawLayerMenu();
    }
}

void LayerMenu::moveLayerDownButtonClicked(){
    QGroupBox* thisBox = qobject_cast<QGroupBox*>(sender()->parent());
    int index = layers.indexOf(thisBox);
    if (index < layers.size() - 1){
        QString temp = layerNames[index];
        layerNames[index] = layerNames[index+1];
        layerNames[index+1] = temp;
        redrawLayerMenu();
    }
}
