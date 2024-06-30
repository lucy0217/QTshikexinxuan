#include "setting.h"
#include "ui_setting.h"
#include<QDebug>
#include<QSqlQuery>
#include<QSqlError>
#include<QMessageBox>
setting::setting(QWidget *parent,QString _username)
    : QDialog(parent)
    , ui(new Ui::setting)
    ,username(_username)
{
    ui->setupUi(this);
    setWindowTitle("设置");
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor(240,248,255)); // 设置背景颜色浅蓝色
    this->setPalette(pal);

    qDebug()<<"setting constructed 当前用户名为："<<_username;
    ui->preferEdit->setWordWrapMode(QTextOption::WrapAnywhere);  // 设置自动换行模式

}

setting::~setting()
{
    delete ui;
}

void setting::on_savebutton_clicked()
{
   QString current= ui->preferEdit->toPlainText();//当前输入的偏好
    qDebug()<<"输入的文本为："<<current;
   QString sqlUpdate = "UPDATE users SET prefer = :prefer WHERE username = :username";
   QSqlQuery query;
   query.prepare(sqlUpdate);
   query.bindValue(":prefer", current);
   query.bindValue(":username", username);
   if (!query.exec()) {
       qDebug() << "Error updating prefer:" << query.lastError().text();
   } else {
       qDebug() << "Preference updated successfully!";
   }
   QMessageBox msg;
   msg.setWindowTitle("提示");
   msg.setText( "保存成功！");
   msg.exec();

}//点击保存后的操作，将信息存入users表prefer栏


void setting::on_pushButton_clicked()
{
    change=new changepassword(this,this->username);
    change->show();
}//修改密码，转到changepassword界面

