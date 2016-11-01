#ifndef PREVIEWAREA_H
#define PREVIEWAREA_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QGraphicsView>
#include <QTimer>
#include <memory>
#include <vector>
#include "animation.h"

using namespace std;

class PreviewArea : public QWidget {
    Q_OBJECT
public:
    explicit PreviewArea(QWidget *parent, vector<unique_ptr<Frame>> *publicFrames);
    void setFrames(vector<unique_ptr<Frame>> *publicFrames);
signals:

public slots:
    void playAnimation();
    void pauseAnimation();
    void goToNextFrameIsPlaying();
    void goToNextFrame();
    void goToPreviousFrame();

private:
    bool isPlaying = false;
    int currentFrameNumber = 0;

    vector<unique_ptr<Frame>> *frames;
    QTimer* timer;

    QVBoxLayout* previewLayout;
    QHBoxLayout* buttonLayout;
    QButtonGroup* playbackButtons;

    QGraphicsView* currentFrame;
    QPushButton* playButton;
    QPushButton* pauseButton;
    QPushButton* nextFrame;
    QPushButton* previousFrame;

    QIcon playIcon = QIcon(QPixmap(":/icons/play"));
    QIcon pauseIcon = QIcon(QPixmap(":/icons/pause"));
    QIcon nextIcon = QIcon(QPixmap(":/icons/next"));
    QIcon previousIcon = QIcon(QPixmap(":/icons/previous"));

    void initWidgets();
    void initConnections();
};

#endif // PREVIEWAREA_H
