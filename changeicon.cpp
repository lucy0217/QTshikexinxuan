#include "changeicon.h"
#include "ui_changeicon.h"
#include<ui_mainwindow.h>
#include<mainwindow.h>
#include<QSqlError>
#include<qmessagebox.h>
changeicon::changeicon(QWidget *parent,QString a,mainwindow*m)
    : QDialog(parent)
    , ui(new Ui::changeicon)
    ,username(a)
    ,parentwindow(m)
{
    ui->setupUi(this);
    setWindowTitle("头像设置");
   // connect(this, &changeicon::iconChanged, this->parent(), &MainWindow::updateIcon);
}

changeicon::~changeicon()
{
    delete ui;
}

void changeicon::on_pushButton_2_clicked()
{
    int tmp=0;
    //根据选中的图片来进行图片更新（路径)以及users表中的icons值更新
    if(ui->checkBox_1->isChecked()){
        tmp=1;
    }
    if(ui->checkBox_2->isChecked()){
        tmp=2;
    }
    if(ui->checkBox_3->isChecked()){
        tmp=3;
    }
    if(ui->checkBox_4->isChecked()){
        tmp=4;
    }
    if(ui->checkBox_5->isChecked()){
        tmp=5;
    }
    if(ui->checkBox_6->isChecked()){
        tmp=6;
    }
    if(ui->checkBox_7->isChecked()){
        tmp=7;
    }
    if(ui->checkBox_8->isChecked()){
        tmp=8;
    }
    if(ui->checkBox_9->isChecked()){
        tmp=9;
    }
    if(ui->checkBox_10->isChecked()){
        tmp=10;
    }
    if(ui->checkBox_11->isChecked()){
        tmp=11;
    }
    if(ui->checkBox_12->isChecked()){
        tmp=12;
    }
    //接下来到users表中修改icon值
    QString sqlUpdate = "UPDATE users SET icon = :icon WHERE username = :username";
    QSqlQuery query;
    query.prepare(sqlUpdate);
    query.bindValue(":icon", tmp);
    query.bindValue(":username", username);
    if (!query.exec()) {
        qDebug() << "Error updating icon:" << query.lastError().text();
    } else {
        qDebug() << "icon updated successfully!";
         emit iconChanged(tmp);
    }
    QMessageBox::information(this, "头像", "更换头像成功！");
    ui->checkBox_1->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    ui->checkBox_6->setChecked(false);
    ui->checkBox_7->setChecked(false);
    ui->checkBox_8->setChecked(false);
    ui->checkBox_9->setChecked(false);
    ui->checkBox_10->setChecked(false);
    ui->checkBox_11->setChecked(false);
    ui->checkBox_12->setChecked(false);
    close();

}//点击保存之后，就会更改头像,要在mainwindow中写一个刷新函数，点击保存函数之后就进行刷新


void changeicon::on_pushButton_clicked()
{
    close();
}

