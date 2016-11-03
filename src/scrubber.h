#ifndef SCRUBBER_H
#define SCRUBBER_H

#include <QWidget>
#include <QScrollArea>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QModelIndexList>
#include <QDropEvent>
#include <vector>
#include <memory>
#include "animation.h"
#include "animationwidgets.h"

using namespace std;

class Scrubber : public QWidget, public AnimationWidget {
    Q_OBJECT
public:
    explicit Scrubber(QWidget *parent, vector<unique_ptr<Frame>> *frames);
    void setFrames(vector<unique_ptr<Frame>> *publicFrames);

    // Calling any of these will not emit the
    // corresponding signal.
    void addFrame(int index) override;
    void moveFrame(int from, int to) override;
    void removeFrame(int index) override;
    void setActiveFrame(int index) override;
    void clear();

signals:
    void addFrameClicked();
    void moveFrameClicked(int fromIndex, int toIndex);
    void removeFrameClicked();
    void frameIconClicked(int newIndex);

public slots:
    void frameClicked(QListWidgetItem* item);

protected:

private:
    QPushButton* addFrameButton;
    QPushButton* removeFrameButton;
    QPushButton* moveFrameRight;
    QPushButton* moveFrameLeft;
    QScrollArea* scrollArea;
    QListWidget* list;
    QHBoxLayout* layout;
    QVBoxLayout* buttons;

    vector<unique_ptr<Frame>> *frames;
};

#endif // SCRUBBER_H
