#include "layermenu.h"

/*To do:
 * Allow deleting layers;
 * use another button or just delete key?
 * Actually hook up LayerMenu to model.
 * Fix drag-and-drop copying layer names.
 * Add destructor?
 * Do I need all these instance variables
 * dynamically allocated in constructor,
 * or just declare them statically in constructor?
 * How do I get access to the animation vector<Frame>?
 * Pass a reference into the layer menu constructor?
 * Each Frame has its own set of layers that are
 * totally independent from the layers of other frames, right?
 * */

LayerMenu::LayerMenu(QWidget *parent) : QWidget(parent) {

    this->resize(170,500);

    listOfLayers = new QListView(parent);
    listOfLayers->setMovement(QListView::Snap);

    listOfLayers->setMaximumWidth(200);

    layerNames = new QStringListModel(listOfLayers);
    list = new QStringList();
    *list << "Layer1";
    layerNames->setStringList(*list);
    listOfLayers->setModel(layerNames);
    listOfLayers->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                  QAbstractItemView::DoubleClicked);

    addLayerButton = new QPushButton(listOfLayers);
    addLayerButton->setText("Add Layer");
    connect(addLayerButton, &QPushButton::released,this, &LayerMenu::addLayerButtonClicked);

    deleteLayerButton = new QPushButton(listOfLayers);
    deleteLayerButton->setText("Delete Selected Layer");
    connect(deleteLayerButton, &QPushButton::released, this, &LayerMenu::deleteLayerButtonClicked);

    moveLayerUpButton = new QPushButton(listOfLayers);
    moveLayerUpButton->setText("Move Layer Up");
    connect(moveLayerUpButton, &QPushButton::released,this, &LayerMenu::moveLayerUpButtonClicked);

    moveLayerDownButton = new QPushButton(listOfLayers);
    moveLayerDownButton->setText("Move Layer Down");
    connect(moveLayerDownButton, &QPushButton::released,this, &LayerMenu::moveLayerDownButtonClicked);

    layerMenuLayout = new QVBoxLayout;
    layerMenuLayout->addWidget(addLayerButton);
    layerMenuLayout->addWidget(deleteLayerButton);
    layerMenuLayout->addWidget(moveLayerUpButton);
    layerMenuLayout->addWidget(moveLayerDownButton);
    layerMenuLayout->addWidget(listOfLayers);
    this->setLayout(layerMenuLayout);

//    QItemSelectionModel *selectionModel = listOfLayers->selectionModel();
//    connect(selectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
//            this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
}

void LayerMenu::deleteItem(const QModelIndex& index)
{
    if (!index.isValid() || index.row() >= listOfLayers->model()->rowCount())
        return;
    layerNames->removeRows(index.row(), 1);
}

void LayerMenu::addLayerButtonClicked() {
    int row = layerNames->rowCount();
    listOfLayers->model()->insertRow(row);
    QModelIndex index = layerNames->index(layerNames->rowCount()-1);
    layerNames->setData(index, "New layer");
    //Call Frame->addLayer() or something?
}

void LayerMenu::deleteLayerButtonClicked() {
    deleteItem(listOfLayers->currentIndex());
    //call Frame->deleteLayer(currentIndex()) or something?
}

//void LayerMenu::selectionChangedSlot(const QItemSelection& selected, const QItemSelection& deselected){
//    //selectedIndices = selected.indexes();
//}

void LayerMenu::moveLayerUpButtonClicked(){
    QModelIndex current = listOfLayers->currentIndex();
    if (current.row() - 1 >= 0){
        QModelIndex previous = listOfLayers->indexAt(QPoint(current.row() - 1, 0));
        //QModelIndex previous = current.parent();
        //QModelIndex previous = layerNames->QStringListModel::createIndex(current.row() - 1, 0, [] () {;});
        //QModelIndex prev = listOfLayers->indexAt(previous);
        //save the string in previous
        //QString temp = (QString)(listOfLayers->model()->data(previous, 0));
        QString temp = layerNames->data(previous, 0).toString();
        //remove previous
        //int previousIndex = previous.row();
        listOfLayers->model()->removeRow(previous.row());
        //layerNames->removeRows(previous, 1);
        //now add previous back after current (that is, where current used to be
        //before we deleted previous)
        //current = listOfLayers->currentIndex();
        //QModelIndex insertionIndex = listOfLayers->indexAt(QPoint(current.row() + 1, 0));
        int insertionIndex = listOfLayers->currentIndex().row() + 1;
        listOfLayers->model()->insertRow(insertionIndex);
        listOfLayers->model()->setData(listOfLayers->model()->index(insertionIndex, 0), temp);
                //ui->listview->model()->setData(ui->listview->model()->index ( row, column),ui.lineEdit->text());
        //QModelIndex swapIndex = listOfLayers->currentIndex();
        //current = listOfLayers->currentIndex();
        //QModelIndex swapIndex = listOfLayers->indexAt(QPoint(insertionIndex, 0));
        //layerNames->setData(previous, "test", 0);
        //list->append("test");
        //layerNames->data(swapIndex, 0).setValue(temp);
        //listOfLayers->model()->data(swapIndex).setValue(temp);


        //add code to rearrange layers in Frame vector<Qimage>
    }
}

void LayerMenu::moveLayerDownButtonClicked(){

}
