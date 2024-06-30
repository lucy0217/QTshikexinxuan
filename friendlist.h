#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QDialog>
#include<friendwidget.h>
#include<searchfriend.h>
#include<friendinfo.h>
namespace Ui {
class friendlist;
}

class friendlist : public QDialog
{
    Q_OBJECT

public:
    explicit friendlist(QWidget *parent = nullptr,QString _username=QString());
    ~friendlist();
   void showfriends();//显示好友的函数
    void showfriends(QString sql);
    void refresh(QString sql);//添加好友后刷新列表重新显示的函数
public slots:
    void handlefriendwidgetClicked();//处理点击事件的函数


private slots:
    void on_addfriendbutton_clicked();

private:
    Ui::friendlist *ui;
    QString currentuser;//当前用户的名字
    QMap<QString,friendwidget*> friends;//好友指针
    searchfriend*s;
    friendinfo* f;
};

#endif // FRIENDLIST_H
