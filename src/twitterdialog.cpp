#include "twitterdialog.h"
#include "ui_twitterdialog.h"

twitterdialog::twitterdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::twitterdialog)
{
    ui->setupUi(this);
    ui->Website->setText("<a href=\"http://www.twitter.com\">www.twitter.com</a>");
    ui->Website->setTextFormat(Qt::RichText);
    ui->Website->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->Website->setOpenExternalLinks(true);

}

void twitterdialog::on_buttonBox_accepted(){
    emit finish(ui->PinValue->text());
}

twitterdialog::~twitterdialog()
{
    delete ui;
}
