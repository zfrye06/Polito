#ifndef IMAGESIZEDIALOG_H
#define IMAGESIZEDIALOG_H

#include <QDialog>

namespace Ui {
class ImageSizeDialog;
}

class ImageSizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageSizeDialog(QWidget *parent = 0, int width = 0, int height = 0);
    ~ImageSizeDialog();

signals:
    void done(int width, int height);

private slots:
    void on_buttonBox_accepted();

private:
    int width;
    int height;
    Ui::ImageSizeDialog *ui;
};

#endif // IMAGESIZEDIALOG_H
