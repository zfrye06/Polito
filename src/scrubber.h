#ifndef SCRUBBER_H
#define SCRUBBER_H

#include <QWidget>
#include "animationwidgets.h"

class Scrubber : public QWidget, public AnimationWidget {
    Q_OBJECT
public:
    explicit Scrubber(QWidget *parent = 0);

    // Calling any of these will not emit the
    // corresponding signal.
    void addFrame(int index) override;
    void moveFrame(int from, int to) override;
    void removeFrame(int index) override;
    void setActiveFrame(int index) override;

signals:

    void frameAdded(int index);
    void frameMoved(int fromIndex, int toIndex);
    void frameRemoved(int index);
    void activeFrameChanged(int newIndex);

public slots:
};

#endif // SCRUBBER_H
