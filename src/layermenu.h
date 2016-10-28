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
    //The active layer is the one where the
    //cursor is blinking in the text box with the blue border
    //The bottom layer (listed at the top of the LayerMenu)
    //has index 0.
    int indexOfActiveLayer;

//    void emitAddLayerSignal(AddLayerAction* action){
//        emit addLayerSignal(action);
//    }

signals:

   // void addLayerSignal(AddLayerAction*);

public slots:
    void addLayerButtonClicked();
    void deleteLayerButtonClicked();
    //void layerBoxClicked();
    void textChanged();
    void moveLayerUpButtonClicked();
    void moveLayerDownButtonClicked();
    void activeLayerChanged();
//    void selectionChangedSlot(const QItemSelection&, const QItemSelection&);


protected:

private:
    QIcon upArrow = QIcon(QPixmap(":/icons/up"));
    QIcon downArrow = QIcon(QPixmap(":/icons/down"));
    QIcon deleteX = QIcon(QPixmap(":/icons/delete"));
    QVector<QGroupBox*> layers;
    QVector<QString> layerNames;
    QPushButton* addLayerButton;
    QVBoxLayout* layerMenuLayout;
    //QGroupBox* selectedLayer;

    void redrawLayerMenu();
    void deleteLayer(QGroupBox* layerToBeDeleted);
    void addLayer(QString layerName);


};

#endif // LAYERMENU_H
