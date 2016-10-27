#include "layermenu.h"
#include <vector>
#include <QMessageBox>
#include <QLineEdit>
#include <QPalette>
#include <QLabel>
#include <QIcon>
#include <QPixmap>

/*To do:
 * Allow deleting layers;
 * use another button or just delete key?
 * Actually hook up LayerMenu to model.
 * Fix drag-and-drop copying layer names.
 * Add destructor?
 * Do I need all these instance variables
 * dynamically allocated in constructor,
 * or just declare them statically in constructor?
 * How do I get access to the animation vector<Frame>?
 * Pass a reference into the layer menu constructor?
 * Each Frame has its own set of layers that are
 * totally independent from the layers of other frames, right?
 * */

LayerMenu::LayerMenu(QWidget *parent) : QWidget(parent) {
    //this->resize(this->sizeHint());
    //this->resize(100,700);
    addLayerButton = new QPushButton(this);
    addLayerButton->setText("Add Layer");

    connect(addLayerButton, &QPushButton::released,this, &LayerMenu::addLayerButtonClicked);

    layerMenuLayout = new QVBoxLayout();
    layerMenuLayout->addWidget(addLayerButton);

    this->setLayout(layerMenuLayout);
    addLayer("Layer1");

    //    QItemSelectionModel *selectionModel = listOfLayers->selectionModel();
    //    connect(selectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
    //            this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
}

void LayerMenu::redrawLayerMenu(){
    foreach(QGroupBox* qgb, layers){
        deleteLayer(qgb);
    }
    foreach(QString qs, layerNames){

    }
}

void LayerMenu::addLayer(QString layerName){
    QGroupBox* groupBox = new QGroupBox();
    groupBox->setCheckable(true);
    connect(groupBox, &QGroupBox::clicked, this, &LayerMenu::layerBoxClicked);


   // QLabel* showHide = new QLabel("show/hide");

    QLineEdit* label = new QLineEdit(layerName);
    label->setParent(groupBox);
    layerNames.append(layerName);
    connect(label, &QLineEdit::textChanged, this, &LayerMenu::textChanged);
    //connect(label, &QLineEdit::clicked, this, &LayerMenu::layerBoxClicked);

    QPushButton* moveLayerUpButton = new QPushButton();
    //moveLayerUpButton->setText("Up");
    moveLayerUpButton->setIcon(upArrow);
    //moveLayerUpButton->setIconSize(QSize(20,20));
    connect(moveLayerUpButton, &QPushButton::released,this, &LayerMenu::moveLayerUpButtonClicked);

    QPushButton* moveLayerDownButton = new QPushButton();
    //moveLayerDownButton->setText("Down");
    moveLayerDownButton->setIcon(downArrow);
    connect(moveLayerDownButton, &QPushButton::released,this, &LayerMenu::moveLayerDownButtonClicked);

    QPushButton* deleteLayerButton = new QPushButton();
    deleteLayerButton->setIcon(deleteX);
    deleteLayerButton->setParent(groupBox);
    connect(deleteLayerButton, &QPushButton::released, this, &LayerMenu::deleteLayerButtonClicked);

    QHBoxLayout *vbox = new QHBoxLayout();
    //vbox->addWidget(showHide);
    vbox->addWidget(label);
    vbox->addWidget(moveLayerUpButton);
    vbox->addWidget(moveLayerDownButton);
    vbox->addWidget(deleteLayerButton);



    groupBox->setLayout(vbox);
    //groupBox->resize(50,70);
    layers.push_back(groupBox);
    layerMenuLayout->addWidget(groupBox);

    //emitAddLayerSignal(new AddLayerAction());
}

void LayerMenu::layerBoxClicked(){
   //highlight sender()
//        QMessageBox::information(
//            this,
//            tr("Application Name"),
//            tr("An information message.") );
    QGroupBox* thisBox = qobject_cast<QGroupBox*>(sender());
    if (selectedLayer == NULL){
        selectedLayer = thisBox;
    }
    else{
        //old selected layer restore old format


    }
    //now highlight the new selected layer and then assign it
    QPalette p = thisBox->palette();
    p.setColor(QPalette::Dark, Qt::white);
    thisBox->setPalette(p);
    selectedLayer = thisBox;
}


void LayerMenu::deleteLayer(QGroupBox* layerToBeDeleted)
{
    foreach(auto child, layerToBeDeleted->children())
    {
        delete child;
    }
    layerMenuLayout->removeWidget(layerToBeDeleted);
    delete layerToBeDeleted;
}

void LayerMenu::addLayerButtonClicked() {
//    QMessageBox::information(
//        this,
//        tr("Application Name"),
//        tr("An information message.") );
    addLayer("New Layer");
}

void LayerMenu::deleteLayerButtonClicked() {
    deleteLayer(qobject_cast<QGroupBox*>(sender()->parent()));
    //emit an action for undo/redo
}

void LayerMenu::textChanged(){
    QString newText = qobject_cast<QLineEdit*>(sender())->text();
    QGroupBox* thisBox = qobject_cast<QGroupBox*>(sender()->parent());
    int index = layers.indexOf(thisBox);
    layerNames[index] = newText;
}

//void LayerMenu::selectionChangedSlot(const QItemSelection& selected, const QItemSelection& deselected){
//    //selectedIndices = selected.indexes();
//}

void LayerMenu::moveLayerUpButtonClicked(){

}

void LayerMenu::moveLayerDownButtonClicked(){

}
