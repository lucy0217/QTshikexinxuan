#include "customtableview.h"
#include <QDebug>
#include<QMessageBox>
#include<comment.h>
#include<QSqlQuery>
CustomTableView::CustomTableView(QWidget *parent,QString _username)
    : QTableView(parent),username(_username)//##
{
}

void CustomTableView::setModel(QAbstractItemModel *model) {
    QTableView::setModel(model); // 调用父类的设置模型方法

    // 检查模型是否为空
    if (!model)
        return;

    // 设置列标题，根据需要修改列索引和中文名称
    model->setHeaderData(1, Qt::Horizontal, "菜品名称"); // 第二列的英文名替换为中文名
    model->setHeaderData(7, Qt::Horizontal, "食堂地点"); // 第三列的英文名替换为中文名
    // 继续设置其它列的标题，如果有更多列的话

    // 可以在这里设置列的其他属性，例如列宽等
    setColumnWidth(1, 240); // 根据实际需要设置一个较大的宽度
    setColumnWidth(7, 240);
    setWordWrap(true);

    //resizeColumnToContents(1); // 根据实际情况设置列索引
    //resizeColumnToContents(7); // 根据实际情况设置列索引

}

void CustomTableView::mousePressEvent(QMouseEvent *event) {
    // 获取点击位置的索引
    qDebug() << "Mouse pressed at position:" << event->pos();  // 调试信息
    QModelIndex index = indexAt(event->pos());

    if (index.isValid() && index.column() == 1) {
        // 获取菜名
        QString dishName = model()->data(index, Qt::DisplayRole).toString();
        qDebug()<<"点击的菜名是："<<dishName;

        // 获取同一行第一列的值（假设编号在第一列）
        QModelIndex firstColumnIndex = model()->index(index.row(), 0); // 获取当前行的第一列
        int dishId = model()->data(firstColumnIndex, Qt::DisplayRole).toInt();
        qDebug() << "菜的编号是：" << dishId;
        QSqlQuery query;
        query.prepare("SELECT id FROM users WHERE username=:username");
        query.bindValue(":username",username);
        if(!query.exec()){
            qDebug()<<"Error";
        }
        if(query.next()){
            int id=query.value(0).toInt();
            qDebug()<<"Found id"<<id<<"for name"<<username;
            userid=id;
        }
        else{
            qDebug()<<"No id found for name"<<username;
        }
        //根据username找id
        comment *c=new comment(nullptr,userid,username,dishId,dishName);//把菜的编号传递进去，然后在comment表里面去找到所有符合dishid等于这个值的评论并显示在tableview上面
        c->exec();
    }

    // 调用父类的鼠标点击事件处理
    QTableView::mousePressEvent(event);
}//对鼠标点击菜名所在列的相应函数

