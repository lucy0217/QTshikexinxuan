#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>//可以真正用于访问操作数据库
#include<user.h>
#include<customtablemodel.h>
#include<customtableview.h>
#include<setting.h>
#include<friendlist.h>
#include<changeicon.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //MainWindow(QWidget *parent = nullptr); 不需要默认构造函数 每个主窗口必然对应一个用户信息
    MainWindow(QWidget *parent = nullptr,QString a=QString(),QString b=QString(),int x1=-1,int x2=-1,int x3=-1,int x4=-1,int x5=-1);
    ~MainWindow();
    void refresh();//修改头像之后刷新的函数
private slots:
    void on_add_dish_clicked();

    void on_selectButton_clicked();

    void on_myfriend_clicked();


    void on_loginsetting_clicked();

    void on_userpictrue_clicked();
public slots:
    void updateUserIcon(int newIcon);

private:
    Ui::MainWindow *ui;
    user current_user;//存放当前登录者的信息
    //QSqlDatabase db;//跟着b站视频学的 试试连接数据库
    //把db放在main函数里面作为全局变量进行声明，这里不再需要这个了（？）
    CustomTableModel *customModel;//写成成员变量，方便后面的析构释放内存
    CustomTableView *customView;
    friendlist* myfriendlist;//指针要记得释放
    setting* Setting;
    changeicon* myicon;

};
#endif // MAINWINDOW_H
