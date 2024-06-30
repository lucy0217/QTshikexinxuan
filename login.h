#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>//可以真正用于访问操作数据库
bool tableExists(QString tableName, QSqlDatabase db);

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_regist_clicked();

    void on_pushButton_login_clicked();


private:
    Ui::login *ui;
    QString inputName;

};

#endif // LOGIN_H
