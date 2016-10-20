
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include "imagesizedialog.h"
#include "action.h"

class DrawArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void imageSize();
    void finishImageSize(int w, int h);

private:
    ImageSizeDialog* d;
    void createActions();
    void createMenus();

    DrawArea *scribbleArea;

    ActionHandler* actionHandler;

    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *optionMenu;

    QAction *undoAct;
    QAction *redoAct;
    QAction *imageSizeAct;
    QAction *exitAct;
    QAction *clearScreenAct;
};

#endif
