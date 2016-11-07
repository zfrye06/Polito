#ifndef TWITTERDIALOG_H
#define TWITTERDIALOG_H

#include <QString>
#include <QDialog>

namespace Ui {
class twitterdialog;
}

class twitterdialog : public QDialog
{
    Q_OBJECT

public:
    explicit twitterdialog(QWidget *parent = 0);
    ~twitterdialog();

signals:
    void finish(QString string);

private slots:

    void on_buttonBox_accepted();

private:
    Ui::twitterdialog *ui;
};

#endif // TWITTERDIALOG_H
