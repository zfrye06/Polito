#ifndef LAYERMENU_H
#define LAYERMENU_H

#include <QWidget>
#include <QListView>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include <QLineEdit>
#include <QGroupBox>
#include <QIcon>

class LayerMenu : public QWidget {
    Q_OBJECT
public:
    explicit LayerMenu(QWidget *parent = 0);

    void addLayer();
    void setActiveLayer(int);
    void clear();

    //These signals allow the LayerMenu to send information to the model
    //every time the ordering or number of layers in the LayerMenu is changed.
    //All information is given in terms of index numbers, with 0 representing
    //the bottom layer. A LayerMenu is initialized with one layer.
    //There is only one active layer at a time. It is highlighted and changes when
    //the user clicks in the QLineEdit text box containing the layer's name.
signals:
    void layerAddedSignal (int indexOfAddedLayer);
    void layersSwappedSignal (int indexOfLayer1, int indexOfLayer2);
    void layerDeletedSignal (int indexOfDeletedLayer);
    void activeLayerChangedSignal (int indexOfActiveLayer);

public slots:
    void addLayerButtonClicked();
    void deleteLayerButtonClicked();
    void moveLayerUpButtonClicked();
    void moveLayerDownButtonClicked();
    void textBoxClicked();

protected:

private:
    QIcon upArrow = QIcon(QPixmap(":/icons/up"));
    QIcon downArrow = QIcon(QPixmap(":/icons/down"));
    QIcon deleteX = QIcon(QPixmap(":/icons/delete"));
    QPushButton* addLayerButton;
    QVBoxLayout* layerMenuLayout;
    int indexOfActiveLayer;
    int numLayers;

    void deleteLayer(QGroupBox* layerToBeDeleted);
    void addLayer(QString layerName);
    void highlightGroupBox(QGroupBox*);
    void unhighlightGroupBox(QGroupBox*);
    void swapLayers(int, int);
    int getIndex(QGroupBox*);
    QGroupBox* getBox(int index);
};

#endif // LAYERMENU_H
