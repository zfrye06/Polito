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

int LayerMenu::translateClickIndex(){
    int index = list->currentRow();
    int translated = translateToExternalIndex(index);
    return translated;
}

int LayerMenu::translateToExternalIndex(int index){
    return translateToInternalIndex(index);
}

int LayerMenu::translateToInternalIndex(int index){
    return list->count() - index - 1;
}

void LayerMenu::updateLayer(){
    Layer* layer = layers->at(this->translateToExternalIndex(list->currentRow()));
    QPixmap &px = layer->pixmap();
    QIcon icon(px.scaled(QSize(100,100)));
    QListWidgetItem* item = list->item(list->currentRow());
    item->setIcon(icon);
}

void LayerMenu::updateLayers(){
    for(int i = 0; i < (int)layers->size(); i++){
        QPixmap &px = layers->at(i)->pixmap();
        QIcon icon(px.scaled(QSize(100,100)));
        QListWidgetItem* item = list->item(i);
        item->setIcon(icon);
    }
}

void LayerMenu::addLayer(int index) {
    QSize size(100,100);
    QPixmap pixmap;
    QIcon icon(pixmap);

    QListWidgetItem* item = new QListWidgetItem(icon, "");
    item->setSizeHint(size);
    list->insertItem(list->count() - index, item);
    item->setTextAlignment(Qt::AlignCenter);
}

void LayerMenu::moveLayer(int from, int to) {
    auto item = list->takeItem(translateToInternalIndex(from));
    list->insertItem(translateToInternalIndex(to) + 1, item);
}

void LayerMenu::removeLayer(int index) {
    auto item = list->takeItem(translateToInternalIndex(index));
    delete item;
}

void LayerMenu::setActiveLayer(int index) {
    list->setCurrentRow(translateToInternalIndex(index));
}

void LayerMenu::setLayers(vector<Layer *> *l){
    clear();
    layers = l;
    addLayerIcons();
}

void LayerMenu::clear() {
    list->clear();
}

void LayerMenu::addLayerIconsLoad() {
    vector<Layer *> &l = *layers;
    for (auto layer : l) {
        QPixmap &pixmap = layer->pixmap();
        QIcon icon(pixmap.scaled(QSize(100,100)));
        QListWidgetItem* item = new QListWidgetItem(icon, "");
        item->setSizeHint(QSize(100,100));
        list->addItem(item);
    }
}

void LayerMenu::addLayerIcons() {
    vector<Layer *> &l = *layers;
    for (auto layer : l) {
        QPixmap &pixmap = layer->pixmap();
        QIcon icon(pixmap.scaled(QSize(100,100)));
        QListWidgetItem* item = new QListWidgetItem(icon, "");
        item->setSizeHint(QSize(100,100));
        list->insertItem(0, item);
    }
}

void LayerMenu::layerClicked(){
    emit activeLayerChangedSignal(translateClickIndex());
}

void LayerMenu::addLayerButtonClicked() {
    emit layerAddedSignal(list->currentRow() + 1);
}

void LayerMenu::deleteLayerButtonClicked() {
    emit layerDeletedSignal(translateClickIndex());
}

void LayerMenu::moveLayerUpButtonClicked(){
    int translated = translateClickIndex();
    emit layersSwappedSignal(translated, translated + 1);
}

void LayerMenu::moveLayerDownButtonClicked(){
    int translated = translateClickIndex();
    emit layersSwappedSignal(translated, translated - 1);
}
