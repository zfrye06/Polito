#include "imagesizedialog.h"
#include "ui_imagesizedialog.h"
#include <unistd.h>

ImageSizeDialog::ImageSizeDialog(QWidget *parent, int Width, int Height) :
    QDialog(parent),
    ui(new Ui::ImageSizeDialog) {
    ui->setupUi(this);
    ui->filtering->addItem("Bilinear",0);
    ui->filtering->addItem("None",1);
    ui->width->setValue( Width );
    ui->height->setValue( Height );
    width = Width;
    height = Height;
}

ImageSizeDialog::~ImageSizeDialog() {
    delete ui;
}

void ImageSizeDialog::on_buttonBox_accepted() {
    width = ui->width->value();
    height = ui->height->value();
    emit done( width, height);
}
