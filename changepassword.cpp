#include "changepassword.h"
#include "ui_changepassword.h"
#include<QDebug>
#include<QSqlQuery>
#include<QSqlError>
#include<QMessageBox>
changepassword::changepassword(QWidget *parent,QString a)
    : QDialog(parent)
    , ui(new Ui::changepassword)
    ,username(a)
{
    qDebug()<<"修改密码，当前用户为："<<username;
    ui->setupUi(this);
    setWindowTitle("修改密码");
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor(240,248,255)); // 设置背景颜色浅蓝色
    this->setPalette(pal);

}

changepassword::~changepassword()
{
    delete ui;
}

void changepassword::on_confirmbutton_clicked()
{
    QString old=ui->oldpassword->text();
    QSqlQuery loginQuery;
    loginQuery.prepare("SELECT username FROM users WHERE username=? AND password=?");
    loginQuery.addBindValue(username);
    loginQuery.addBindValue(old);


    if (!loginQuery.exec()) {
        qDebug() << "Error checking login:" << loginQuery.lastError().text();
    } else {
        if (loginQuery.next()) {
            QString new_p=ui->newpass->text();
            QString new_p_agin=ui->newpass2->text();
            if(new_p==new_p_agin){
                //更新密码
                QSqlQuery updateQuery;
                updateQuery.prepare("UPDATE users SET password = ? WHERE username = ?");
                updateQuery.addBindValue(new_p);
                updateQuery.addBindValue(username);
                if(updateQuery.exec()){
                QMessageBox::information(this,"修改密码","修改成功");
                }

                ui->oldpassword->clear();
                ui->newpass->clear();
                ui->newpass2->clear();
                this->close();
            }
            else{

                QMessageBox::warning(this,"修改密码","两次输入密码不一致");
            }

        }
        else {
            // 登录失败
            QMessageBox::warning(this, "修改密码", "原密码不正确！");
        }
    }
}//点确认按钮时，更新密码信息

