#include "layermenu.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QPalette>
#include <QLabel>
#include <QIcon>
#include <QSize>

LayerMenu::LayerMenu(QWidget *parent, vector<Layer *> *layers) : QWidget(parent), layers(layers) {
    addLayerButton = new QPushButton();
    removeLayerButton = new QPushButton();
    moveLayerUp = new QPushButton();
    moveLayerDown = new QPushButton();

    addLayerButton->setIcon(addIcon);
    removeLayerButton->setIcon(deleteIcon);
    moveLayerUp->setIcon(upIcon);
    moveLayerDown->setIcon(downIcon);

    addLayerButton->setToolTip("Add Layer");
    removeLayerButton->setToolTip("Delete Current Layer");
    moveLayerUp->setToolTip("Move Layer Up");
    moveLayerDown->setToolTip("Move Layer Down");

    layerMenuLayout = new QVBoxLayout(this);
    layerButtons = new QHBoxLayout();
    layerMenuLayout->addLayout(layerButtons);

    layerButtons->addWidget(addLayerButton);
    layerButtons->addWidget(removeLayerButton);
    layerButtons->addWidget(moveLayerUp);
    layerButtons->addWidget(moveLayerDown);

    list = new QListWidget();
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    list->setFlow(QListView::TopToBottom);
    list->setIconSize(QSize(100,100));
    list->setAlternatingRowColors(true);

    layerMenuLayout->addWidget(list);

    addLayerIcons();

    list->setCurrentRow(0);

    connect(addLayerButton, &QPushButton::clicked,this, &LayerMenu::addLayerButtonClicked);
    connect(removeLayerButton, &QPushButton::clicked, this, &LayerMenu::deleteLayerButtonClicked);
    connect(moveLayerUp, &QPushButton::clicked, this, &LayerMenu::moveLayerUpButtonClicked);
    connect(moveLayerDown, &QPushButton::clicked, this, &LayerMenu::moveLayerDownButtonClicked);
    connect(list, &QListWidget::clicked, this, &LayerMenu::layerClicked);
}

void LayerMenu::updateLayer(){
    Layer* layer = layers->at(list->currentRow());
    QPixmap &px = layer->pixmap();
    QIcon icon(px);
    QListWidgetItem* item = list->item(list->currentRow());
    item->setIcon(icon);
}

void LayerMenu::addLayer(int index) {
    QSize size(100,100);
    QPixmap pixmap;
    QIcon icon(pixmap);

    QListWidgetItem* item = new QListWidgetItem(icon, "");
    item->setSizeHint(size);
    list->insertItem(list->currentRow(), item);
    item->setTextAlignment(Qt::AlignCenter);
}

void LayerMenu::moveLayer(int from, int to) {
    auto item = list->takeItem(from);
    list->insertItem(to, item);
}

void LayerMenu::removeLayer(int index) {
    auto item = list->takeItem(index);
    delete item;
}

void LayerMenu::setActiveLayer(int index) {
    list->setCurrentRow(index);
}

void LayerMenu::setLayers(vector<Layer *> *l){
    clear();
    layers = l;
    addLayerIcons();
}

void LayerMenu::clear() {
    list->clear();
}

void LayerMenu::addLayerIcons() {
    vector<Layer *> &l = *layers;
    for (auto layer : l) {
        QPixmap &pixmap = layer->pixmap();
        QIcon icon(pixmap);
        QListWidgetItem* item = new QListWidgetItem(pixmap, "");
        list->addItem(item);        
    }
}

void LayerMenu::layerClicked(){
    emit activeLayerChangedSignal(list->currentRow());
}

void LayerMenu::addLayerButtonClicked() {
    emit layerAddedSignal(list->currentRow());
}

void LayerMenu::deleteLayerButtonClicked() {
    emit layerDeletedSignal(list->currentRow());
}

void LayerMenu::moveLayerUpButtonClicked(){
    emit layersSwappedSignal(list->currentRow(), list->currentRow() - 1);
}

void LayerMenu::moveLayerDownButtonClicked(){
    emit layersSwappedSignal(list->currentRow(), list->currentRow() + 1);
}
