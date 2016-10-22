#ifndef LAYERMENU_H
#define LAYERMENU_H

#include <QWidget>
#include <QListView>
#include <QPushButton>
#include <QStringListModel>

class LayerMenu : public QWidget
{
    Q_OBJECT
public:
    explicit LayerMenu(QWidget *parent = 0);

    void addLayer();
signals:

public slots:
    void addLayerButtonClicked();

protected:

private:
    QListView *listOfLayers;
    QPushButton *addLayerButton;
    QStringListModel *layerNames;
};

#endif // LAYERMENU_H
