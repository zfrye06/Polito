#ifndef LAYERMENU_H
#define LAYERMENU_H

#include <QPoint>
#include <QWidget>
#include <QListView>
#include <QPushButton>
#include <QStringListModel>
#include <QVBoxLayout>
#include <iostream>


class LayerMenu : public QWidget {
    Q_OBJECT
public:
    explicit LayerMenu(QWidget *parent = 0);
    void deleteItem(const QModelIndex& index);
signals:

public slots:
    void addLayerButtonClicked();
    void deleteLayerButtonClicked();
    void moveLayerUpButtonClicked();
    void moveLayerDownButtonClicked();
//    void selectionChangedSlot(const QItemSelection&, const QItemSelection&);


protected:

private:
    QListView *listOfLayers;
    QPushButton *addLayerButton;
    QStringListModel *layerNames;
    QVBoxLayout *layerMenuLayout;
    QPushButton *deleteLayerButton;
    QStringList *list;
    QPushButton *moveLayerUpButton;
    QPushButton *moveLayerDownButton;
    //QModelIndexList selectedIndices;
    //QList<QListViewItem> *selectedItems;
    //QListViewItem
};

#endif // LAYERMENU_H
