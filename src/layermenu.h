#ifndef LAYERMENU_H
#define LAYERMENU_H

#include <QWidget>
#include <QListView>
#include <QGroupBox>
#include <QIcon>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "animationwidgets.h"

class LayerWidget;

class LayerMenu : public QWidget, public FrameWidget {
    Q_OBJECT
public:
    explicit LayerMenu(QWidget *parent = 0);

    void addLayer(int index) override;
    void moveLayer(int from, int to) override;
    void removeLayer(int index) override;
    void setActiveLayer(int index) override;
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

private:
    QPushButton* addLayerButton;
    QVBoxLayout* layerMenuLayout;
    LayerWidget* highlightedWidget;

    // I maintain this as an external index. It's purely for
    // recordkeeping. Don't use internally without translating
    // to an internal index.
    int indexOfActiveLayer;
    int translateToInternalIndex(int);
    int translateToExternalIndex(int);
    int translatedClickIndex();
    LayerWidget *widgetAtExternalIndex(int);
};

class LayerWidget : public QGroupBox {
    Q_OBJECT
 public:
    LayerWidget(LayerMenu *parent = 0);
    void highlight();
    void unhighlight();
 private:
    QIcon upArrow = QIcon(QPixmap(":/icons/up"));
    QIcon downArrow = QIcon(QPixmap(":/icons/down"));
    QIcon deleteX = QIcon(QPixmap(":/icons/delete"));
};

#endif // LAYERMENU_H
