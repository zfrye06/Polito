#include "fpsdialog.h"
#include "ui_fpsdialog.h"

FPSDialog::FPSDialog(QWidget *parent, int fps) :
    QDialog(parent),
    ui(new Ui::FPSDialog)
{
    ui->setupUi(this);
    ui->fpsBox->setMaximum(30);
    ui->fpsBox->setMinimum(1);
    ui->fpsBox->setValue(fps);
}

FPSDialog::~FPSDialog()
{
    delete ui;
}

void FPSDialog::on_buttonBox_accepted()
{
    emit setFPS(ui->fpsBox->value());
}
