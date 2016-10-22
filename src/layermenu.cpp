#include <QtWidgets>
#include <iostream>
#include "layermenu.h"
#include <QListView>

/*To do:
 * Allow deleting layers;
 * use another button or just delete key?
 * Actually hook up LayerMenu to model.
 * Fix drag-and-drop copying layer names.
 *
 * */

LayerMenu::LayerMenu(QWidget *parent) : QWidget(parent)
{
    this->resize(170,500);
    layerMenuLayout = new QVBoxLayout;
    listOfLayers = new QListView(parent);
    listOfLayers->setMovement(QListView::Snap);
    addLayerButton = new QPushButton(listOfLayers);
    addLayerButton->setText("Add Layer");
    connect(addLayerButton, &QPushButton::released,this, &LayerMenu::addLayerButtonClicked);
    layerNames = new QStringListModel(listOfLayers);
    QStringList List;
    List << "Layer1";
    layerNames->setStringList(List);
    listOfLayers->setModel(layerNames);
    listOfLayers->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                  QAbstractItemView::DoubleClicked);
    layerMenuLayout->addWidget(addLayerButton);
    layerMenuLayout->addWidget(listOfLayers);
    this->setLayout(layerMenuLayout);
}

void LayerMenu::addLayerButtonClicked()
{
    int row = layerNames->rowCount();
    listOfLayers->model()->insertRow(row);
    QModelIndex index = layerNames->index(layerNames->rowCount()-1);
    layerNames->setData(index, "New layer");
}
