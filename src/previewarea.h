#ifndef PREVIEWAREA_H
#define PREVIEWAREA_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QGraphicsView>
#include <memory>
#include <vector>
#include "animation.h"

using namespace std;

class PreviewArea : public QWidget {
    Q_OBJECT
public:
    explicit PreviewArea(QWidget *parent, vector<unique_ptr<Frame>> &publicFrames);

signals:

public slots:

private:
    const vector<unique_ptr<Frame>> &frames;

    QVBoxLayout* previewLayout;
    QHBoxLayout* buttonLayout;
    QButtonGroup* playbackButtons;

    QGraphicsView* currentFrame;
    QPushButton* playButton;
    QPushButton* pauseButton;
    QPushButton* nextFrame;
    QPushButton* previousFrame;

    QIcon playIcon = QIcon(QPixmap(":/icons/icons/play"));
    QIcon pauseIcon = QIcon(QPixmap(":/icons/icons/pause"));
    QIcon nextIcon = QIcon(QPixmap(":/icons/icons/next"));
    QIcon previousIcon = QIcon(QPixmap(":/icons/icons/previous"));

    void initWidgets();
    void initConnections();
};

#endif // PREVIEWAREA_H
