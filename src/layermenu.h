#ifndef LAYERMENU_H
#define LAYERMENU_H

#include <QWidget>
#include <QListView>
#include <QPushButton>
#include <QStringListModel>
#include <QVBoxLayout>

class LayerMenu : public QWidget {
    Q_OBJECT
public:
    explicit LayerMenu(QWidget *parent = 0);

    //void addLayer();
signals:

public slots:
    void addLayerButtonClicked();
    void deleteLayerButtonClicked();

protected:

private:
    QListView *listOfLayers;
    QPushButton *addLayerButton;
    QStringListModel *layerNames;
    QVBoxLayout *layerMenuLayout;
    QPushButton *deleteLayerButton;
    QStringList *List;
    //QListViewItem
};

#endif // LAYERMENU_H
