
#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include "action.h"
#include "layermenu.h"

// Must forward-declare ScribbleAction due to circular dependency.
class ScribbleAction;

class DrawArea : public QWidget {
    Q_OBJECT

public:
    DrawArea(QWidget *parent = 0);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    void setImage( QImage& i );
    QImage& getImage();
    void resizeImage( int width, int height, int filtering = 0);

    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }

public slots:
    void clearImage();

signals:
    void addAction( Action* a );

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    QPointF offset;
    QTransform camera;
    float cameraScale;
    bool modified;
    bool scribbling;
    bool dragging;
    int myPenWidth;
    QColor myPenColor;
    QImage background;
    QImage image;
    QPoint lastPoint;
    QPoint lastDraggingPoint;
    ScribbleAction* currentAction;
};

class ScribbleAction : public Action {
private:
    DrawArea* area;
    QImage before;
    QImage after;
public:
    ScribbleAction( DrawArea* Area );
    void finish();
    void undo();
    void redo();
};

#endif
