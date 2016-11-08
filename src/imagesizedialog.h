#ifndef IMAGESIZEDIALOG_H
#define IMAGESIZEDIALOG_H

#include <QDialog>

namespace Ui {
class ImageSizeDialog;
}

class ImageSizeDialog : public QDialog {
    Q_OBJECT

public:
    explicit ImageSizeDialog(QWidget *parent = 0, int dimension = 0);
    ~ImageSizeDialog();

signals:
    void finish(int dimension, bool bilinear);

private slots:


    void on_buttonBox_accepted();

private:
    Ui::ImageSizeDialog *ui;
};

#endif // IMAGESIZEDIALOG_H
