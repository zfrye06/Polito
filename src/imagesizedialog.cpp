#include "imagesizedialog.h"
#include "ui_imagesizedialog.h"

ImageSizeDialog::ImageSizeDialog(QWidget *parent, int dimension) :
    QDialog(parent),
    ui(new Ui::ImageSizeDialog) {
    ui->setupUi(this);
    ui->filtering->addItem("Bilinear",0);
    ui->filtering->addItem("None",1);
    ui->dimensionsBox->setValue(dimension);
}

ImageSizeDialog::~ImageSizeDialog() {
    delete ui;
}

void ImageSizeDialog::on_buttonBox_accepted() {
//    int dim = ui->dimensionsBox->value();
    emit done(64);
}
