#include <QtWidgets>
#include <iostream>
#include "layermenu.h"
#include <QListView>

LayerMenu::LayerMenu(QWidget *parent) : QWidget(parent)
{

    listOfLayers = new QListView(parent);
    listOfLayers->resize(100,1000);
    listOfLayers->setMovement(QListView::Snap);
    addLayerButton = new QPushButton(listOfLayers);
    addLayerButton->setText("Add Layer");
    connect(addLayerButton, &QPushButton::released,this, &LayerMenu::addLayerButtonClicked);
    listOfLayers->show();

   // QStandardItemModel *model = new QStandardItemModel();
    //listOfLayers->setModel(model);

    //ui->setupUi(this);

       // Create model
       layerNames = new QStringListModel(listOfLayers);

       // Make data
       QStringList List;
       List << "Layer1" << "Layer2" << "Layer3";

       // Populate our model
       layerNames->setStringList(List);

       // Glue model and view together
       listOfLayers->setModel(layerNames);
       //ui->comboBox->setModel(model);

       // Add additional feature so that
       // we can manually modify the data in ListView
       // It may be triggered by hitting any key or double-click etc.
      listOfLayers->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                               QAbstractItemView::DoubleClicked);
}

void LayerMenu::addLayerButtonClicked()
{
    // QWidget* newLayerWidget = new QWidget(listOfLayers);
    //newLayerWidget->setText("Layer");
    //newLayerWidget->show();
    QStandardItem *item = new QStandardItem();
    item->setData("Layer", Qt::DisplayRole);
    //item->setData( QImage(":/Pix/Pix.png"), Qt::DecorationRole );
    item->setEditable(false);
    listOfLayers->model()->insertRow(0);

}
