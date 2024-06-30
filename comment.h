#ifndef COMMENT_H
#define COMMENT_H

#include <QWidget>
#include<QDialog>
#include<QSqlQueryModel>
namespace Ui {
class comment;
}

class comment : public QDialog
{
    Q_OBJECT

public:

    explicit comment(QWidget *parent = nullptr,int _userid=0,QString _username=QString(),int _dishid=0,QString _dishname=QString());//把菜品的编号传递进去
  //  comment(int _dishid);
    ~comment();
    void calculateAverageScore(int _dishId);

private slots:
    void on_button_write_comment_clicked();

private:
    Ui::comment *ui;
    QSqlQueryModel *model;
    int userid;
    QString username;
    int dishid;
    QString dishname;
};

#endif // COMMENT_H
