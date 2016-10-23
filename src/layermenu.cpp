#include <QtWidgets>
#include <iostream>
#include "layermenu.h"
#include <QListView>

/*To do:
 * Allow deleting layers;
 * use another button or just delete key?
 * Actually hook up LayerMenu to model.
 * Fix drag-and-drop copying layer names.
 * Add destructor?
 * Do I need all these instance variables
 * dynamically allocated in constructor,
 * or just declare them statically in constructor?
 * */

LayerMenu::LayerMenu(QWidget *parent) : QWidget(parent) {
    this->resize(170,500);
    layerMenuLayout = new QVBoxLayout;
    listOfLayers = new QListView(parent);
    listOfLayers->setMovement(QListView::Snap);
    addLayerButton = new QPushButton(listOfLayers);
    addLayerButton->setText("Add Layer");
    connect(addLayerButton, &QPushButton::released,this, &LayerMenu::addLayerButtonClicked);
    deleteLayerButton = new QPushButton(listOfLayers);
    deleteLayerButton->setText("Delete Layer");
    connect(deleteLayerButton, &QPushButton::released, this, &LayerMenu::deleteLayerButtonClicked);
    layerNames = new QStringListModel(listOfLayers);
    List = new QStringList();
    *List << "Layer1";
    layerNames->setStringList(*List);
    listOfLayers->setModel(layerNames);
    listOfLayers->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                  QAbstractItemView::DoubleClicked);
    layerMenuLayout->addWidget(addLayerButton);
    layerMenuLayout->addWidget(deleteLayerButton);
    layerMenuLayout->addWidget(listOfLayers);
    this->setLayout(layerMenuLayout);

    //selectedItems = new QList<QListViewItem>();

    QItemSelectionModel *selectionModel = listOfLayers->selectionModel();
      connect(selectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
              this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
}

void LayerMenu::addLayerButtonClicked() {
    int row = layerNames->rowCount();
    listOfLayers->model()->insertRow(row);
    QModelIndex index = layerNames->index(layerNames->rowCount()-1);
    layerNames->setData(index, "New layer");
}

void LayerMenu::deleteLayerButtonClicked() {
//    foreach (QListViewItem ql, listOfLayers){
//        if (ql.isSelected()){
//            listOfLayers->
//        }
//    }

//    foreach (QString qs, *List) {
//        if (qs.isSelected()){
//            List->removeOne(qs);
//        }
//    }
    listOfLayers->model()->removeRow(0);

    //QListViewItem.isSelected();
}

void LayerMenu::selectionChangedSlot(const QItemSelection& selected, const QItemSelection& deselected){
}
