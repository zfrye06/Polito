#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>

class Toolbar : public QWidget {
    Q_OBJECT
public:
    explicit Toolbar(QWidget *parent = 0);

signals:

public slots:
    void setCheckedButtons();

private:
    QVBoxLayout* toolsLayout;
    QButtonGroup* buttonGroup;

    QPushButton* moveButton;
    QPushButton* brushButton;
    QPushButton* fillButton;
    QPushButton* colorButton;
    QPushButton* currentButton;

    void initWidgets(QWidget*);
    void initConnections();
};

#endif // TOOLBAR_H
