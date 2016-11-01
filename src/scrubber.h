#ifndef SCRUBBER_H
#define SCRUBBER_H

#include <QWidget>
#include <QScrollArea>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QModelIndexList>
#include <QDropEvent>
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
    void clear();

signals:
    void frameAdded(int index);
    void frameMoved(int fromIndex, int toIndex);
    void frameRemoved(int index);
    void activeFrameChanged(int newIndex);

public slots:
    void frameClicked(QListWidgetItem* item);
    void reordered(QDropEvent* event);

protected:
    void dropEvent(QDropEvent* event) Q_DECL_OVERRIDE;

private:
    QPushButton* addFrameButton;
    QPushButton* removeFrameButton;
    QPushButton* moveFrameRight;
    QPushButton* moveFrameLeft;
    QScrollArea* scrollArea;
    QListWidget* list;
    QVBoxLayout* layout;
};

#endif // SCRUBBER_H
