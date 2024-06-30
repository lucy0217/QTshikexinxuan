#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);
    ~MyDialog();
    Ui::MyDialog *ui;

private slots:
    void on_add_button_clicked();

private:
    //Ui::MyDialog *ui;
    //QString tmp;//本来是想这个来存放editline里面的内容的，但是怎么同步呢？？？
};

#endif // MYDIALOG_H
