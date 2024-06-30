#include "mainwindow.h"
#include"mydialog.h"
#include <QApplication>
#include<QLabel>
#include<QComboBox>
#include <QHBoxLayout>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<login.h>
#include<comment.h>
#include<friendlist.h>
#include<changepassword.h>
QSqlDatabase db;//全局变量，确保数据库db只被打开一次
void deleteTable(const QString &tableName) {
    QSqlQuery query;
    QString sql = QString("DROP TABLE IF EXISTS %1").arg(tableName);

    if (!query.exec(sql)) {
        qDebug() << "Error deleting table:" << query.lastError().text();
    } else {
        qDebug() << "Table" << tableName << "deleted successfully.";
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    db=QSqlDatabase::addDatabase("QSQLITE");//QSQLITE告诉系统连接的是什么数据,连接成功会返回一个数据库对象
    db.setDatabaseName("mydatabase.db");// 数据库文件的后缀为.db
    //如果想要进一步操作数据库，就必须要进行数据库打开操作
    if(!db.open()){
        qDebug()<<"Error failed to open"<<db.lastError();
    }
    else{
        qDebug()<<"success to open";
    }//检查打开有没有成功



   login loginwindow;
    loginwindow.show();



    return a.exec();
}
