#include "searchfriend.h"
#include "ui_searchfriend.h"
#include<QSqlQuery>
#include<QSqlError>
#include<friendwidget.h>
#include<friendlist.h>
#include<QDialog>
#include<addfriend.h>
extern QSqlDatabase db; // 或者直接声明 QSqlDatabase db;
searchfriend::searchfriend(QString _currentname,QString _searchname,QWidget *parent,friendlist* _parentwindow)
    : QWidget(parent)
    , ui(new Ui::searchfriend)
{
    parentWindow=_parentwindow;
    qDebug()<<"searchfriend constructed!";
    ui->setupUi(this);
    setWindowTitle("搜索");
    currentname=_currentname;
    searchname=_searchname;

    //显示符合要求的模糊搜索结果
    search();

}//构造函数，记录当前用户

void searchfriend::handlefriendwidgetClicked()
{



    // 处理 friendwidget 被点击后的逻辑，可以在这里更新界面或执行其他操作
    friendwidget *senderWidget = qobject_cast<friendwidget*>(sender());
    if (senderWidget) {
        QString s2 = senderWidget->getfriendname(); // 有一个获取 friendname 的函数
        //弹出弹窗提示是否添加好友
       // addfriend* a=new addfriend(nullptr,currentname,s2);//进入到addfriend界面
        std::unique_ptr<addfriend> a(new addfriend(nullptr, currentname, s2));
        a->exec();
    }
    qDebug()<<"???";
    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
        // 在这里可以进行错误处理，比如退出程序或者给出用户提示
    } else {
        qDebug() << "Database connected!";
        // 连接成功，可以执行后续的数据库操作
    }
   parentWindow->friendlist::showfriends();//希望在这里直接对friendlist的好友列表进行刷新。

}

void searchfriend::search(){
    QSqlQuery query;
    QString sql = QString("SELECT username,icon FROM users WHERE username LIKE '%%1%'").arg(searchname);
    if (!query.exec(sql)) {
        qDebug() << "Error executing query:" << query.lastError();
        return;
    }
    while (query.next()) {

        QString peername = query.value(0).toString();
        int tmpicon=query.value(1).toInt();
        qDebug() << "Peer name:" << peername;


        friendwidget* f = new friendwidget(peername, tmpicon, ui->searchresult);

        QListWidgetItem *item = new QListWidgetItem(ui->searchresult);
        item->setSizeHint(QSize(240, 60));
        item->setBackground(QColor(135, 206, 250));

        ui->searchresult->addItem(item);
        ui->searchresult->setItemWidget(item, f);
        connect(f, &friendwidget::clicked, this, &searchfriend::handlefriendwidgetClicked);
        f->show();

        searchfriends.insert(peername, f);

    }

}

searchfriend::~searchfriend()
{
    delete ui;
    delete parentWindow;
}


void searchfriend::on_returnButton_clicked()
{
    close();
}

