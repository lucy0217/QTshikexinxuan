#include "friendinfo.h"
#include "ui_friendinfo.h"
#include<QSqlQuery>
#include<QSqlError>
friendinfo::friendinfo(QWidget *parent,QString a)
    : QDialog(parent)
    , ui(new Ui::friendinfo)
    ,friendname(a)
{
    ui->setupUi(this);
    setWindowTitle("好友名片");
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor(225,255,255)); // 设置背景颜色浅蓝色
    this->setPalette(pal);

    QSqlQuery query;
    QString sqlSelect = "SELECT prefer FROM users WHERE username=:username";  // 初始查询语句，始终为真
    query.prepare(sqlSelect);
    query.bindValue(":username",friendname);

    if (query.exec()) {
        if (query.next()) { // 移动到结果集的第一条记录
            QString friendprefer = query.value(0).toString(); // 获取第一个字段的值
            ui->perferinfo->setText(friendprefer);
            ui->perferinfo->setWordWrapMode(QTextOption::WrapAnywhere);  // 设置自动换行模式
        } else {
            qDebug() << "显示名片失败"<<query.lastError().text();
        }
    } else {
        qDebug() << "执行查询失败:" << query.lastError().text();
    }
}

friendinfo::~friendinfo()
{
    delete ui;
}
