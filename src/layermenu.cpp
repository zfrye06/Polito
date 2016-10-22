#include <QtWidgets>
#include <iostream>
#include "layermenu.h"
#include <QListView>

LayerMenu::LayerMenu(QWidget *parent) : QWidget(parent)
{
    this->resize(200,500);
    QVBoxLayout *layerMenuLayout = new QVBoxLayout;
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
    layerMenuLayout->addWidget(listOfLayers);
    layerMenuLayout->addWidget(addLayerButton);
    this->setLayout(layerMenuLayout);
}

void LayerMenu::addLayerButtonClicked()
{
    //QStandardItem *item = new QStandardItem();
    //item->setData("Layer", Qt::DisplayRole);
    //item->setData( QImage(":/Pix/Pix.png"), Qt::DecorationRole );
    //item->setEditable(false);
    int row = layerNames->rowCount();
    listOfLayers->model()->insertRow(row);
    QModelIndex index = layerNames->index(layerNames->rowCount()-1);
    layerNames->setData(index, "New layer");

}
