#ifndef FRIENDWIDGET_H
#define FRIENDWIDGET_H

#include <QWidget>

namespace Ui {
class friendwidget;
}

class friendwidget : public QWidget
{
    Q_OBJECT

public:
    explicit friendwidget(QWidget *parent = nullptr);
    ~friendwidget();
     explicit friendwidget(QString _friendname,int icon_,QWidget *parent = nullptr);//构造函数
    QString getfriendname();
     void setBackgroundColor(const QColor &color);

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void clicked();  // 声明 clicked 信号
private:
    Ui::friendwidget *ui;
    QString friendname;
    QColor backgroundColor; // Declare backgroundColor here

};

#endif // FRIENDWIDGET_H
