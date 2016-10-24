
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include <vector>
#include "action.h"
#include "frame.h"
#include "imagesizedialog.h"
#include "toolbar.h"
#include "layermenu.h"
#include <QGridLayout>

class DrawArea;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void imageSize();
    void finishImageSize(int w, int h);

private:

    std::vector<Frame> animation;
    ActionHistory actionHistory;

    ImageSizeDialog* d;
    DrawArea *scribbleArea;
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *optionMenu;
    QAction *undoAct;
    QAction *redoAct;
    QAction *imageSizeAct;
    QAction *exitAct;
    QAction *clearScreenAct;
    Toolbar *toolbar;
    QWidget *window;
    LayerMenu *layermenu;
    QGridLayout *layout;
    
    void createActions();
    void createMenus();
};

#endif
