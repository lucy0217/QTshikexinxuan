#include "login.h"
#include "ui_login.h"
#include<mainwindow.h>
#include<QSqlError>
#include<QtDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include<QMessageBox>
extern QSqlDatabase db;  // 引用全局变量 db

bool tableExists(QString tableName, QSqlDatabase db)
{
    QStringList tables = db.tables();
    return tables.contains(tableName, Qt::CaseInsensitive);
}//检查一个表是否已经存在的函数

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowTitle("食客心选");
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor(240,255,255)); // 设置背景颜色浅蓝色
    this->setPalette(pal);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    QSqlQuery query;//在创建该对象时，系统会自动完成跟数据库的关联

    if(!tableExists("users",db)){
        QString sqlCreate=QString("CREATE TABLE users(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                    "username TEXT,"
                                    "password TEXT,"
                                    "ismain INTEGER,"
                                    "spice INTEGER,"
                                    "vegetarian INTEGER,"
                                    "cuisine INTEGER,"
                                    "flavor INTEGER,"
                                    "comment TEXT[],"
                                    "prefer TEXT,"
                                    "icon INTEGET)");//菜单的表定义 与dish的七项指标对应
        if(!query.exec(sqlCreate)){
            qDebug() << "Error: Fail to create table. " << query.lastError();
        }
        else
        {
            qDebug() << "Table users created!";
        }
    }


}

login::~login()
{
    delete ui;
}


void login::on_pushButton_exit_clicked()
{
    close();
}//1.点击退出按钮后的响应函数

//2.点击注册的漕函数
void login::on_pushButton_regist_clicked()
{
    QMessageBox msg;

    inputName=ui->lineEdit_name->text();//接收用户名
    QString inputPassword=ui->lineEdit_password->text();//接收密码
    // 检查用户名是否已存在
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT username FROM users WHERE username = ?");
    checkQuery.addBindValue(inputName);

    if (!checkQuery.exec()) {
        qDebug() << "Error checking existing user:" << checkQuery.lastError().text();
    } else {
        if (checkQuery.next()) {
            // 用户名已存在
            msg.setWindowTitle("提示");
            msg.setText( "该用户名已存在");
            msg.exec();
            //QMessageBox::warning(this, "Registration", "Username already exists.");

        } else {
            // 用户名不存在，可以进行注册
            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO users (username, password,icon) VALUES (?, ?,?)");
            insertQuery.addBindValue(inputName);
            insertQuery.addBindValue(inputPassword);
              insertQuery.addBindValue(1);//头像的序号新用户默认选择第一张作为头像

            if (!insertQuery.exec()) {
                qDebug() << "Error inserting new user:" << insertQuery.lastError().text();
            } else {
                QMessageBox::information(this, "注册", "注册成功！请返回登陆");
                // 清空输入框
                ui->lineEdit_name->clear();
                ui->lineEdit_password->clear();
            }
        }//注册成功
    }


}

//3.点击登录的函数
void login::on_pushButton_login_clicked()
{

    QString inputName = ui->lineEdit_name->text();       // 接收用户名
    QString inputPassword = ui->lineEdit_password->text();// 接收密码

    // 检查用户名和密码是否匹配
    QSqlQuery loginQuery;
    loginQuery.prepare("SELECT username,password FROM users WHERE username = ? AND password = ?");
    loginQuery.addBindValue(inputName);
    loginQuery.addBindValue(inputPassword);

    if (!loginQuery.exec()) {
        qDebug() << "Error checking login:" << loginQuery.lastError().text();
    } else {
        if (loginQuery.next()) {
            // 登录成功
            //QMessageBox::information(this, "Login", "Login successful.");
            // 在这里可以进行登录成功后的操作，比如打开主界面等
           QString user_name = loginQuery.value("username").toString();
           QString _password=loginQuery.value("password").toString();

           int _ismain=loginQuery.value("ismain").toInt();
           int _spice=loginQuery.value("spice").toInt();
           int _vegetarian=loginQuery.value("vegetarian").toInt();
           int _cuisine=loginQuery.value("cuisine").toInt();
           int _flavor=loginQuery.value("flavor").toInt();//查询当前登录用户的信息，对mainwindow进行初始化，便于后续对用户信息进行展示


           MainWindow *w1 = new MainWindow(nullptr,user_name,_password,_ismain,_spice,_vegetarian,_cuisine,_flavor);
           w1->show();
           this->close();//关闭登录窗口

        } else {
            // 登录失败
            QMessageBox::warning(this, "登录", "用户名或密码不正确！");
        }
    }



}
