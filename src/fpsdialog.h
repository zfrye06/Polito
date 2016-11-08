#ifndef FPSDIALOG_H
#define FPSDIALOG_H

#include <QDialog>

namespace Ui {
class FPSDialog;
}

class FPSDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FPSDialog(QWidget *parent = 0, int fps = 15);
    ~FPSDialog();

signals:
    void setFPS(int fps);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::FPSDialog *ui;
};

#endif // FPSDIALOG_H
