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
 * Add a button to change the active layer, allow only one at a time
 * (unfortunately, QGroupBoxes do not emit a suitable signal for clicked)
 *
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

    //    QItemSelectionModel *selectionModel = listOfLayers->selectionModel();
    //    connect(selectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
    //            this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
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
    //groupBox->resize(100, 700);
    groupBox->setCheckable(true);
    connect(groupBox, &QGroupBox::clicked, this, &LayerMenu::layerBoxClicked);
    layers.append(groupBox);

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

    QGridLayout* hbox = new QGridLayout();
    hbox->addWidget(label, 0, 0, 1, 3, Qt::AlignCenter);
    hbox->addWidget(moveLayerUpButton, 1, 0);
    hbox->addWidget(moveLayerDownButton, 1, 1);
    hbox->addWidget(deleteLayerButton, 1, 2);


    groupBox->setLayout(hbox);
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
    int index = layers.indexOf(layerToBeDeleted);
    layerNames.remove(index);
    foreach(auto child, layerToBeDeleted->children())
    {
        delete child;
    }
    layerMenuLayout->removeWidget(layerToBeDeleted);
    //layers.remove(layerToBeDeleted);
    delete layerToBeDeleted;
    layers.remove(index);
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
    QGroupBox* thisBox = qobject_cast<QGroupBox*>(sender()->parent());
    int index = layers.indexOf(thisBox);
        QMessageBox::information(
            this,
            tr("Index is"),
            tr(std::to_string(index).c_str()) );
    if (index > 0){
        QString temp = layerNames[index];
        layerNames[index] = layerNames[index-1];
        layerNames[index-1] = temp;
        redrawLayerMenu();
    }
}

void LayerMenu::moveLayerDownButtonClicked(){

}
