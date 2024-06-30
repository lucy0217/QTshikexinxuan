#include "addfriend.h"
#include "ui_addfriend.h"
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QDebug>
#include<QSqlError>
#include<QMessageBox>
addfriend::addfriend(QWidget *parent,QString a,QString b)
    :QDialog(parent)
    ,ui(new Ui::addfriend)
    ,username1(a)
    ,username2(b)
{
    ui->setupUi(this);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor(240,248,255)); // 设置背景颜色浅蓝色
    this->setPalette(pal);
}

addfriend::~addfriend()
{
    delete ui;
}

void addfriend::on_cancelbutton_clicked()
{
    close();
}


void addfriend::on_okbutton_clicked()
{
    //先判断是否已经存在
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT username1,username2 FROM relationship WHERE username1 = ? AND username2=?");
    checkQuery.addBindValue(username1);
      checkQuery.addBindValue(username2);
  QMessageBox msg;
    if (!checkQuery.exec()) {
        qDebug() << "Error checking existing friend:" << checkQuery.lastError().text();
    } else {
        if (checkQuery.next()) {
            // 用户名已存在

            msg.setWindowTitle("提示");
            msg.setText( "该用户已被添加为好友！");
            msg.exec();
            this->close();
        }
        else{
            qDebug() << "Clicked friendwidget with name:" << username2;
            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO relationship (username1,username2) VALUES (?, ?)");
            insertQuery.addBindValue(username1);
            insertQuery.addBindValue(username2);

            if (!insertQuery.exec()) {
                qDebug() << "添加好友失败" << insertQuery.lastError().text();
            } else {
                qDebug()<<"添加好友成功";
            }

            insertQuery.clear();
            insertQuery.prepare("INSERT INTO relationship (username1,username2) VALUES (?, ?)");
            insertQuery.addBindValue(username2);
            insertQuery.addBindValue(username1);

            if (!insertQuery.exec()) {
                qDebug() << "添加好友失败" << insertQuery.lastError().text();
            } else {
                qDebug()<<"添加好友成功";
                msg.setWindowTitle("提示");
                msg.setText( "添加成功！");
                msg.exec();
                this->close();
            }

        }
    }


}//首先检查是否已经是好友了，否则就添加好友，和登陆注册的逻辑是一样的

