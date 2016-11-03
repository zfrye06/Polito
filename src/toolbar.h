#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QColorDialog>

#include "painthandler.h"

class Toolbar : public QWidget {
    Q_OBJECT
public:
    explicit Toolbar(QWidget *parent = 0);
    ~Toolbar();

signals:
    
    void colorChanged(QColor);
    void setPaintHandler( PaintHandler* paintHandler );

public slots:
    void getColor();
    void setBrush();
    void setEraser();
    void setFill();
    void setMove();
    void setSquare();
    void setCircle();
    void setLine();
    void initWidgets();
    void initConnections();

private:
    QVBoxLayout* toolsLayout;
    QButtonGroup* buttonGroup;
    QColorDialog* colorPicker;

    QPushButton* moveButton;
    QPushButton* brushButton;
    QPushButton* eraseButton;
    QPushButton* fillButton;
    QPushButton* colorButton;
    QPushButton* circleButton;
    QPushButton* squareButton;
    QPushButton* lineButton;

    QIcon brushIcon = QIcon(QPixmap(":/icons/brush"));
    QIcon eraseIcon = QIcon(QPixmap(":/icons/erase"));
    QIcon moveIcon = QIcon(QPixmap(":/icons/pan"));
    QIcon fillIcon = QIcon(QPixmap(":/icons/fill"));
    QIcon colorIcon = QIcon(QPixmap(":/icons/palette"));
    QIcon circleIcon = QIcon(QPixmap(":/icons/circle"));
    QIcon squareIcon = QIcon(QPixmap(":/icons/square"));
    QIcon lineIcon = QIcon(QPixmap(":/icons/line"));

};

#endif // TOOLBAR_H
