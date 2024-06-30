#include "user.h"
#include<QDebug>
user::user() {

    ismain=-1;
    spice=-1;
    vegetarian=-1;
    cuisine=-1;
    flavor=-1;
    icon=1;//头像默认选择第一张

}//构造函数,将指标都初始化为-1；
user::user(QString a,QString b,int x1,int x2,int x3,int x4,int x5){
    username=a;
    password=b;
    ismain=x1;
    spice=x2;
    vegetarian=x3;
    cuisine=x4;
    flavor=x5;
    //qDebug()<<"用户初始化信息成功！"<<a<<b<<x1<<x2<<x3<<x4<<x5;
}//用于从登陆界面转到mainwindow时，获取当前的用户名密码初始化mainwindow里的user对象的信息

