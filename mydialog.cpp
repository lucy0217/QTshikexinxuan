#include "mydialog.h"
#include "ui_mydialog.h"
#include<mainwindow.h>
#include<QMessageBox>
//#include<dish.h>
MyDialog::MyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MyDialog)
{
    ui->setupUi(this);

    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor(240,248,255)); // 设置背景颜色浅蓝色
    this->setPalette(pal);

   // ui->comboBox_1->addItem("主食");
    ui->comboBox_1->addItem("非主食");
    ui->comboBox_1->addItem("米");
    ui->comboBox_1->addItem("面/粉");
   // ui->comboBox_1->addItem("不限");
   // ui->comboBox_2->addItem("辣度");
    ui->comboBox_2->addItem("不辣");
    ui->comboBox_2->addItem("辣");
    //ui->comboBox_2->addItem("不限");
    //ui->comboBox_3->addItem("荤素");
    ui->comboBox_3->addItem("荤");
    ui->comboBox_3->addItem("素");
    ui->comboBox_3->addItem("不限");
   // ui->comboBox_4->addItem("中/西餐");
    ui->comboBox_4->addItem("中餐");
    ui->comboBox_4->addItem("其他");
  //  ui->comboBox_4->addItem("不限");
   // ui->comboBox_5->addItem("风味");
    ui->comboBox_5->addItem("江南");
    ui->comboBox_5->addItem("山东");
    ui->comboBox_5->addItem("新疆");
    ui->comboBox_5->addItem("广东");
    ui->comboBox_5->addItem("闽南");
    ui->comboBox_5->addItem("蜀湘");
    ui->comboBox_5->addItem("西餐");
    ui->comboBox_5->addItem("日韩");
    ui->comboBox_5->addItem("其他");
   // ui->comboBox_5->addItem("不限");
    // ui->comboBox_6->addItem("食堂");
    ui->comboBox_6->addItem("家园食堂");
    ui->comboBox_6->addItem("燕南食堂");
    ui->comboBox_6->addItem("学一食堂");
    ui->comboBox_6->addItem("学五食堂");

    ui->dishname_input->setPlaceholderText("请输入菜品名称");


}

MyDialog::~MyDialog()
{  
    delete ui;
}//析构函数

void print(QString& s,int x1,int x2,int x3,int x4,int x5,int x6){
    qDebug()<<s;
    switch(x1){
       case 0:
        qDebug()<<"主食类型：非主食";
           break;
       case 1:
           qDebug()<<"主食类型：米";
           break;
       case 2:
           qDebug()<<"主食类型：面/粉";
           break;
       case 3:
           qDebug()<<"主食类型：不限";
           break;
    }
    switch(x2){
       case 0:
        qDebug()<<"辣度为：不辣";
           break;
       case 1:
           qDebug()<<"辣度为：辣";
           break;
       case 2:
           qDebug()<<"辣度为：不限";
           break;
    }
     switch(x3){
    case 0:
         qDebug()<<"荤素为：荤";
        break;
    case 1:
        qDebug()<<"荤素为：素";
        break;
    case 2:
        qDebug()<<"荤素为：不限";
        break;
    }
    switch(x4){
    case 0:
        qDebug()<<"中西餐为：中餐";
        break;
    case 1:
        qDebug()<<"中西餐为：其他";
        break;
    case 2:
        qDebug()<<"中西餐为：不限";
        break;
    }

    qDebug()<<"第五项指标风味为："<<x5;
    qDebug()<<"第六项指标食堂地点为："<<x6;

}//用于打印添加菜品的结果的函数，用来debug

//“添加菜品”按钮被点击之后的反应，应该弹出提示“菜品添加成功”的提示
void MyDialog::on_add_button_clicked()
{
     QMessageBox msgBox;
    //这里面应该有生成新的菜品对象的程序
    //先输出看看能不能成功获取comboBox信息
    QString dishname=ui->dishname_input->text();
    if(dishname.isEmpty()){
        msgBox.setText("请输入菜品名称！");
        msgBox.setWindowTitle("提示");
        // 显示消息框
        msgBox.exec();
        return;

    }//如果菜品名是空的，弹出窗口提示“请输入菜名！”
    int x1=ui->comboBox_1->currentIndex();
    int x2=ui->comboBox_2->currentIndex();
    int x3=ui->comboBox_3->currentIndex();
    int x4=ui->comboBox_4->currentIndex();
    int x5=ui->comboBox_5->currentIndex();
    int x6=ui->comboBox_6->currentIndex();

    QSqlQuery query;


    QString sqlInsert = "INSERT INTO menu(name, ismain, spice, vegetarian, cuisine, flavor, loc) "
                        "VALUES (:name, :ismain, :spice, :vegetarian, :cuisine, :flavor, :loc)";

    query.prepare(sqlInsert);
    query.bindValue(":name", dishname);
    query.bindValue(":ismain", x1);
    query.bindValue(":spice", x2);
    query.bindValue(":vegetarian", x3);
    query.bindValue(":cuisine", x4);
    query.bindValue(":flavor", x5);
    query.bindValue(":loc", x6);


    if(query.exec()){
        qDebug()<<"insert one info successfully";
        print(dishname,x1,x2,x3,x4,x5,x6);//debug
    }
    else{
        qDebug()<<"failed to insert info to the table menu";
    }//插入成功则打印输出，否则打印插入失败的提示

    int lastId = query.lastInsertId().toInt();
    //Dish tmp(lastId+1,dishname,x1,x2,x3,x4,x5,x6);
    qDebug()<<"!! lastId="<<lastId;//经检验在插入操作之后可以成功获取lastid

    ui->dishname_input->clear();

    msgBox.setWindowTitle("提示");
    msgBox.setText("菜品添加成功！");
    msgBox.addButton(QMessageBox::Ok);//添加一个确认按钮
    // 显示消息框
    msgBox.exec();
}

