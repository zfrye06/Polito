
#ifndef FRAME_H
#define FRAME_H

#include <QImage>
#include <vector>

class Frame
{
public:
    Frame();

    void addLayer();
    void removeLayer();
    void setDuration();
    void setActiveLayer();
    int getDuration();
    QImage *getActiveLayer();

 private:
    std::vector<QImage> layers;
    int activeLayerIndex;
    int duration;
};

#endif // FRAME_H
