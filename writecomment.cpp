#include "writecomment.h"
#include "ui_writecomment.h"
#include<QDebug>
#include<QSqlQuery>
#include<QMessageBox>

writecomment::writecomment(QWidget *parent,int _userid,QString _username,int _dishid,QString _dishname)
    : QDialog(parent)
    , ui(new Ui::writecomment),userid(_userid),username(_username),dishid(_dishid),dishname(_dishname)
{
    ui->setupUi(this);
}

writecomment::~writecomment()
{
    delete ui;
}

void writecomment::on_pushButton_clicked()
{
    close();
}


void writecomment::on_pushButton_2_clicked()
{
    QString current= ui->lineEdit->text();//当前输入的评价
    qDebug()<<"输入的文本为："<<current;
    int scores=cnt;
    qDebug()<<cnt;
    QString sqlInsert = "INSERT INTO comments(userid,username,dishid,dishname,score,comment)"
                        "VALUES(:userid,:username,:dishid,:dishname,:score,:comment)";
    QSqlQuery query;
    query.prepare(sqlInsert);
    query.bindValue(":userid", userid);
    query.bindValue(":username", username);
    query.bindValue(":dishid", dishid);
    query.bindValue(":dishname", dishname);
    query.bindValue(":score",scores);
    query.bindValue(":comment", current);

    if (!query.exec()) {
        qDebug() << "Error";
    } else {
        qDebug() << "Insert successfully!";
    }
    QMessageBox::information(this,"菜品评价","保存成功");
    close();
}//点击确认后，保存评价到表中


void writecomment::on_pushButton_3_pressed()
{
    if(ui->pushButton_3->isChecked()){
        cnt=1;
        ui->pushButton_3->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
    }
    else{
        cnt=0;
        ui->pushButton_3->setIcon(QIcon(":/new/prefix1/images/ccc.jpg"));
    }
}


void writecomment::on_pushButton_4_pressed()
{
    if(ui->pushButton_4->isChecked()){
        ui->pushButton_3->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
        ui->pushButton_4->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
        cnt=2;
    }
    else{
        cnt=1;
        ui->pushButton_4->setIcon(QIcon(":/new/prefix1/images/ccc.jpg"));
    }
}


void writecomment::on_pushButton_5_pressed()
{
    if(ui->pushButton_5->isChecked()){
        ui->pushButton_3->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
        ui->pushButton_4->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
        ui->pushButton_5->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
        cnt=3;
    }
    else{
        cnt=2;
        ui->pushButton_5->setIcon(QIcon(":/new/prefix1/images/ccc.jpg"));
    }
}


void writecomment::on_pushButton_6_pressed()
{
    if(ui->pushButton_6->isChecked()){
        ui->pushButton_3->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
        ui->pushButton_4->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
        ui->pushButton_5->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
        ui->pushButton_6->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
        cnt=4;
    }
    else{
        cnt=3;
        ui->pushButton_6->setIcon(QIcon(":/new/prefix1/images/ccc.jpg"));
    }
}


void writecomment::on_pushButton_7_pressed()
{
    if(ui->pushButton_7->isChecked()){
        ui->pushButton_3->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
        ui->pushButton_4->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
        ui->pushButton_5->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
        ui->pushButton_6->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
        ui->pushButton_7->setIcon(QIcon(":/new/prefix1/images/aaa1.png"));
        cnt=5;
    }
    else{
        cnt=4;
        ui->pushButton_7->setIcon(QIcon(":/new/prefix1/images/ccc.jpg"));
    }

}


void writecomment::on_pushButton_3_released()
{
    //cnt=0;
    //ui->pushButton_3->setIcon(QIcon(":/new/prefix1/images/ccc.jpg"));
}


void writecomment::on_pushButton_4_released()
{
    //cnt=1;
    //ui->pushButton_4->setIcon(QIcon(":/new/prefix1/images/ccc.jpg"));
}


void writecomment::on_pushButton_5_released()
{
    //cnt=2;
    //ui->pushButton_5->setIcon(QIcon(":/new/prefix1/images/ccc.jpg"));
}


void writecomment::on_pushButton_6_released()
{
    //cnt=3;
    //ui->pushButton_6->setIcon(QIcon(":/new/prefix1/images/ccc.jpg"));
}


void writecomment::on_pushButton_7_released()
{
    //cnt=4;
    //ui->pushButton_7->setIcon(QIcon(":/new/prefix1/images/ccc.jpg"));
}

