#ifndef LAYERMENU_H
#define LAYERMENU_H

#include <QPoint>
#include <QWidget>
#include <QListView>
#include <QPushButton>
#include <QStringListModel>
#include <QVBoxLayout>
#include <iostream>
#include <QLineEdit>
#include <QGroupBox>
#include <QIcon>


class LayerMenu : public QWidget {
    Q_OBJECT
public:
    explicit LayerMenu(QWidget *parent = 0);

signals:
    void layerAddedSignal (int indexOfAddedLayer);
    void layersSwappedSignal (int indexOfLayer1, int indexOfLayer2);
    void layerDeletedSignal (int indexOfDeletedLayer);
    //If there is no active layer (because all layers have been deleted)
    //then a -1 is emitted.
    void activeLayerChangedSignal (int indexOfActiveLayer);

public slots:
    void addLayerButtonClicked();
    void deleteLayerButtonClicked();
    void textChanged();
    void moveLayerUpButtonClicked();
    void moveLayerDownButtonClicked();
    void activeLayerChanged();

protected:

private:
    QIcon upArrow = QIcon(QPixmap(":/icons/up"));
    QIcon downArrow = QIcon(QPixmap(":/icons/down"));
    QIcon deleteX = QIcon(QPixmap(":/icons/delete"));
    QVector<QGroupBox*> layers;
    QVector<QString> layerNames;
    QPushButton* addLayerButton;
    QVBoxLayout* layerMenuLayout;
    int indexOfActiveLayer;


    void redrawLayerMenu();
    void deleteLayer(QGroupBox* layerToBeDeleted);
    void addLayer(QString layerName);
    void highlightGroupBox(QGroupBox*);
    void unhighlightGroupBox(QGroupBox*);

    //Helper methods for redrawLayerMenu()
    //without modifying the layerNames vector
    //or emitting unnecessary/harmful signals:
    void deleteLayerWithoutEmittingSignals(QGroupBox*);
    void addLayerWithoutEmittingSignals(QString layerName);


};

#endif // LAYERMENU_H
