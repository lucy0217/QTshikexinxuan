#ifndef WRITECOMMENT_H
#define WRITECOMMENT_H

#include <QDialog>

namespace Ui {
class writecomment;
}

class writecomment : public QDialog
{
    Q_OBJECT

public:
    explicit writecomment(QWidget *parent = nullptr,int _userid=0,QString _username=QString(),int _dishid=0,QString _dishname=QString());
    ~writecomment();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_pressed();

    void on_pushButton_4_pressed();

    void on_pushButton_5_pressed();

    void on_pushButton_6_pressed();

    void on_pushButton_7_pressed();

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void on_pushButton_5_released();

    void on_pushButton_6_released();

    void on_pushButton_7_released();

private:
    Ui::writecomment *ui;
    int userid;
    QString username;
    int dishid;
    QString dishname;
    int cnt=0;//星级
};

#endif // WRITECOMMENT_H
