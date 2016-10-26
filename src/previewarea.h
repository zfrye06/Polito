#ifndef PREVIEWAREA_H
#define PREVIEWAREA_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QGraphicsView>
#include <vector>
#include "animation.h"

using namespace std;

class PreviewArea : public QWidget {
    Q_OBJECT
public:
    explicit PreviewArea(QWidget *parent = 0);

signals:

public slots:

private:
    vector<unique_ptr<Frame>>* frames;

    QVBoxLayout* previewLayout;
    QButtonGroup* playbackButtons;

    QGraphicsView* currentFrame;
    QPushButton* playButton;
    QPushButton* pauseButton;
    QPushButton* nextFrame;
    QPushButton* previousFrame;

    void initWidgets();
    void initConnections();
};

#endif // PREVIEWAREA_H
