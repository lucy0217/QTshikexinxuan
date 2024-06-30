#ifndef SEARCHFRIEND_H
#define SEARCHFRIEND_H
#include<friendwidget.h>
#include <QWidget>
class friendlist;
namespace Ui {
class searchfriend;
}

class searchfriend : public QWidget
{
    Q_OBJECT

public:
    explicit searchfriend(QString _currentname,QString _searchname,QWidget *parent = nullptr,friendlist* _parentwindow=nullptr);//传递当前用户的名字
    ~searchfriend();
    void search();

private slots:
    void on_returnButton_clicked();
public slots:
    void handlefriendwidgetClicked();//处理点击事件的函数

private:
    Ui::searchfriend *ui;
    QString currentname;
    QString searchname;
    QMap<QString,friendwidget*> searchfriends;//好友指针
    friendlist *parentWindow;
};

#endif // SEARCHFRIEND_H
