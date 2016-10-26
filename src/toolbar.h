#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QColorDialog>

class Toolbar : public QWidget {
    Q_OBJECT
public:
    explicit Toolbar(QWidget *parent = 0);

signals:

public slots:
    QColor colorPicked();

private:
    QVBoxLayout* toolsLayout;
    QButtonGroup* buttonGroup;
    QColorDialog* colorPicker;

    QColor currentColor;

    QPushButton* moveButton;
    QPushButton* brushButton;
    QPushButton* fillButton;
    QPushButton* colorButton;

    QIcon brushIcon = QIcon(QPixmap(":/icons/brush"));
    QIcon moveIcon = QIcon(QPixmap(":/icons/pan"));
    QIcon fillIcon = QIcon(QPixmap(":/icons/fill"));
    QIcon colorIcon = QIcon(QPixmap(":/icons/palette"));

    void initWidgets();
    void initConnections();
};

#endif // TOOLBAR_H
