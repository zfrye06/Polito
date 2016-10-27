#ifndef LAYERMENU_H
#define LAYERMENU_H

#include <QPoint>
#include <QWidget>
#include <QListView>
#include <QPushButton>
#include <QStringListModel>
#include <QVBoxLayout>
#include <iostream>
#include <QLabel>
#include <QGroupBox>


class LayerMenu : public QWidget {
    Q_OBJECT
public:
    explicit LayerMenu(QWidget *parent = 0);
    void deleteLayer(QGroupBox* layerToBeDeleted);
    void addLayer(QString layerName);
    void redrawLayerMenu();

//    void emitAddLayerSignal(AddLayerAction* action){
//        emit addLayerSignal(action);
//    }

signals:

   // void addLayerSignal(AddLayerAction*);

public slots:
    void addLayerButtonClicked();
    void deleteLayerButtonClicked();
    //void moveLayerUpButtonClicked();
    //void moveLayerDownButtonClicked();
//    void selectionChangedSlot(const QItemSelection&, const QItemSelection&);


protected:

private:
    //Each QGroupBox
    QVector<QGroupBox*> layers;
    QVector<QString> layerNames;
    QPushButton* addLayerButton;
    QPushButton* moveLayerUpButton;
    QPushButton* moveLayerDownButton;
    QVBoxLayout* layerMenuLayout;
    QGroupBox* selectedLayer;
    //The layer that has most recently been deleted.
    QGroupBox* deletedLayer;
};

#endif // LAYERMENU_H
