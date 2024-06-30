#ifndef USER_H
#define USER_H
#include<qhash.h>
#include <QObject>

class user
{
public:
    user();
    user(QString a,QString b,int x1,int x2,int x3,int x4,int x5);
    QString username;
    QString password;
    int ismain;
    int spice;
    int vegetarian;
    int cuisine;
    int flavor;
    QString prefer;
    QHash<int,QString>comment;//用于存放评论,id表示菜品的名称，qstring存放评论内容
    int icon;//头像的序号

};

#endif // USER_H
