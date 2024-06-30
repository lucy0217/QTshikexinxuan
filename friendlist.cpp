#include "friendlist.h"
#include "ui_friendlist.h"
#include<QSqlQuery>
#include<friendwidget.h>
#include<QDebug>
#include<QSqlError>
#include<QDialog>
#include<searchfriend.h>
#include<QMessageBox>
#include<friendinfo.h>
extern QSqlDatabase db; // 声明外部全局变量
void friendlist::handlefriendwidgetClicked()
{
    // 处理 friendwidget 被点击后的逻辑，展示好友的偏好名片
    friendwidget *clickedWidget = qobject_cast<friendwidget*>(sender());
    if (clickedWidget) {
        clickedWidget->setBackgroundColor(QColor(135, 206, 250)); // Set clicked background color
    //接下来展示这个人的偏好信息
        QString _name=clickedWidget->getfriendname();
        f=new friendinfo(this,_name);
        f->show();
    }

}
friendlist::friendlist(QWidget *parent,QString _username)
    : QDialog(parent)
    , ui(new Ui::friendlist)
{
    ui->setupUi(this);
    connect(ui->friendlistWidget, &QListWidget::itemClicked, this, &friendlist::handlefriendwidgetClicked);
    currentuser=_username;
    qDebug()<<"构造friendlist对象";
    setWindowTitle("我的好友");
    showfriends();//展示好友界面

}

friendlist::~friendlist()
{
    delete ui;
    if(s){
        delete s;
    }//释放搜索窗口的指针
    if(f){
        delete f;
    }

}//析构函数

void friendlist::showfriends(){
    qDebug()<<"showfriends尝试中";
   // QString sql="SELECT username2 FROM relationship WHERE username1=" + QString(currentuser);
    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
        // 在这里可以进行错误处理，比如退出程序或者给出用户提示
    } else {
        qDebug() << "Database connected!";
        // 连接成功，可以执行后续的数据库操作
    }
   qDebug() << "currentuser value:" << currentuser;
    QString sql = QString("SELECT username2 FROM relationship WHERE username1='%1'").arg(currentuser);
    qDebug()<<"为什么会这样 呜呜";
   refresh(sql);
}

void friendlist::showfriends(QString sql){
    refresh(sql);
}

void friendlist::refresh(QString sql)
{
    qDebug()<<"进入refresh函数";
    QSqlQuery query;
    if (!query.exec(sql)) {
        qDebug() << "SQL query execution failed: " << query.lastError();
        return;
    }

    ui->friendlistWidget->clear();
    qDeleteAll(friends);//清空指针空间
    friends.clear();



    while (query.next()) { // 显示好友列表
        QString peername = query.value(0).toString();
        int _icon=0;
        qDebug() << "Peer name:" << peername;
        //然后从users表中去找好友的icon，显示出对应头像
        QSqlQuery query1;
        QString sql1="SELECT icon FROM users WHERE username=?";
        query1.prepare(sql1);
        query1.addBindValue(peername);
        if(query1.exec()){
            while(query1.next()){
                _icon=query1.value(0).toInt();
            }
        }
        else{
            qDebug()<<" 查询失败";
        }

        friendwidget* f = new friendwidget(peername, _icon, ui->friendlistWidget);

        QListWidgetItem *item = new QListWidgetItem(ui->friendlistWidget);
        item->setSizeHint(QSize(240, 60));
        item->setBackground(QColor(135, 206, 250));


        ui->friendlistWidget->addItem(item);
        ui->friendlistWidget->setItemWidget(item, f);
        connect(f, &friendwidget::clicked, this, &friendlist::handlefriendwidgetClicked);
        f->show();

        friends.insert(peername, f);
    }
}


//点击添加好友之后重新弹出一个新界面，依然用friendwidget构建
void friendlist::on_addfriendbutton_clicked()
{
    qDebug()<<"“搜索”被点击";
    QString _name=ui->searchline->text();
    s= new searchfriend(currentuser,_name,nullptr,this);

    s->show();

}

