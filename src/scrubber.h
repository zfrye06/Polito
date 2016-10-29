#ifndef SCRUBBER_H
#define SCRUBBER_H

#include <QWidget>

class Scrubber : public QWidget {
    Q_OBJECT
public:
    explicit Scrubber(QWidget *parent = 0);

signals:

    void frameAdded(int index);
    void frameMoved(int fromIndex, int toIndex);
    void frameRemoved(int index);

public slots:
};

#endif // SCRUBBER_H
