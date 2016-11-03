#include "layermenu.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QPalette>
#include <QLabel>
#include <QIcon>

// TODO: We shouldn't be manually managing the layout and indices of stuff at all here...

LayerMenu::LayerMenu(QWidget *parent) : QWidget(parent), indexOfActiveLayer(-1), highlightedWidget(nullptr) {
    addLayerButton = new QPushButton(this);
    addLayerButton->setText("Add Layer");
    connect(addLayerButton, &QPushButton::released,this, &LayerMenu::addLayerButtonClicked);

    layerMenuLayout = new QVBoxLayout();
    layerMenuLayout->setAlignment(Qt::AlignTop);
    layerMenuLayout->addWidget(addLayerButton);
    this->setLayout(layerMenuLayout);

    addLayer(0);
    setActiveLayer(0);
}

void LayerMenu::addLayer(int index) {
    
    // When adding, the translated index is actually one greater
    // than it would otherwise be.
    int indexTranslated = layerMenuLayout->count() - index;
    layerMenuLayout->insertWidget(indexTranslated, new LayerWidget(this));
}

void LayerMenu::moveLayer(int from, int to) {
    int fromTranslated = translateToInternalIndex(from);
    int toTranslated = translateToInternalIndex(to);
    auto toMove = layerMenuLayout->takeAt(fromTranslated)->widget();
    layerMenuLayout->insertWidget(toTranslated, toMove);
}

void LayerMenu::removeLayer(int index) {
    auto item = widgetAtExternalIndex(index);
    layerMenuLayout->removeWidget(item);
    if (item == highlightedWidget) {
        highlightedWidget = nullptr;
    }
    delete item;
}

void LayerMenu::setActiveLayer(int index) {
    indexOfActiveLayer = index;
    if (highlightedWidget != nullptr) {
        highlightedWidget->unhighlight();
    }
    LayerWidget *widget = widgetAtExternalIndex(index);
    widget->highlight();
    highlightedWidget = widget;
}

void LayerMenu::clear() {
    while (layerMenuLayout->count() > 1) {
        removeLayer(0);
    }
    indexOfActiveLayer = -1;
    highlightedWidget = nullptr;
}

void LayerMenu::textBoxClicked(){
    int translated = translatedClickIndex();
    emit activeLayerChangedSignal(translated);
}

void LayerMenu::addLayerButtonClicked() {
    emit layerAddedSignal(indexOfActiveLayer + 1);
}

void LayerMenu::deleteLayerButtonClicked() {
    int translated = translatedClickIndex();
    emit layerDeletedSignal(translated);
}

void LayerMenu::moveLayerUpButtonClicked(){
    int translated = translatedClickIndex();
    emit layersSwappedSignal(translated, translated + 1);
}

void LayerMenu::moveLayerDownButtonClicked(){
    int translated = translatedClickIndex();
    emit layersSwappedSignal(translated, translated - 1);
}

int LayerMenu::translatedClickIndex() {
    auto w = qobject_cast<LayerWidget*>(sender()->parent());
    int index = layerMenuLayout->indexOf(w);
    int translated = translateToExternalIndex(index);
    return translated;
}

int LayerMenu::translateToInternalIndex(int index) {
    return layerMenuLayout->count() - index - 1;
}

int LayerMenu::translateToExternalIndex(int index) {
    // The reverse translation is the same.
    return translateToInternalIndex(index);
}

LayerWidget *LayerMenu::widgetAtExternalIndex(int index) {
    int translated = translateToInternalIndex(index);
    QWidget *qw = layerMenuLayout->itemAt(translated)->widget();
    return qobject_cast<LayerWidget*>(qw);
}

LayerWidget::LayerWidget(LayerMenu *parent) : QGroupBox(parent) {
    QLineEdit* label = new QLineEdit("layer", this);
    //cursorPositionChanged here is just used for "when text box is clicked"
    //since there's no "released" event in QLineEdit
    connect(label, &QLineEdit::cursorPositionChanged,
            parent, &LayerMenu::textBoxClicked);

    QPushButton* moveLayerUpButton = new QPushButton(this);
    moveLayerUpButton->setIcon(upArrow);
    connect(moveLayerUpButton, &QPushButton::released,
            parent, &LayerMenu::moveLayerUpButtonClicked);

    QPushButton* moveLayerDownButton = new QPushButton(this);
    moveLayerDownButton->setIcon(downArrow);
    connect(moveLayerDownButton, &QPushButton::released,
            parent, &LayerMenu::moveLayerDownButtonClicked);

    QPushButton* deleteLayerButton = new QPushButton(this);
    deleteLayerButton->setIcon(deleteX);
    connect(deleteLayerButton, &QPushButton::released,
            parent, &LayerMenu::deleteLayerButtonClicked);

    QGridLayout* gridBox = new QGridLayout();
    gridBox->addWidget(label, 0, 0, 1, 3, Qt::AlignCenter);
    gridBox->addWidget(moveLayerUpButton, 1, 0);
    gridBox->addWidget(moveLayerDownButton, 1, 1);
    gridBox->addWidget(deleteLayerButton, 1, 2);

    setLayout(gridBox);
}

void LayerWidget::highlight() {
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, QColor(110,135,255,100));
    setAutoFillBackground(true);
    setPalette(Pal);
    show();
}

void LayerWidget::unhighlight() {
    setAutoFillBackground(false);
    setPalette(style()->standardPalette());
    show();
}
