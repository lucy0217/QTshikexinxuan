#include "friendwidget.h"
#include "ui_friendwidget.h"
#include<qpalette.h>
friendwidget::friendwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::friendwidget)
{
    ui->setupUi(this);

}

friendwidget::~friendwidget()
{
    delete ui;
}

friendwidget::friendwidget(QString _friendname,int icon_,QWidget *parent):
    QWidget(parent)
    ,ui(new Ui::friendwidget){
    ui->setupUi(this);
    friendname=_friendname;
    ui->namelabel->setText(friendname);
    setLayout(nullptr);
    ui->iconlabel->setGeometry(QRect(2, 2, 50, 50));
    //设置iconlabel为头像图标
    QString s=":/new/prefix1/images/";
    s+=QString::number(icon_);
    s+=".jpg";
    QPixmap pixmap(s);  // 加载图片资源
    QSize labelSize = ui->iconlabel->size();
    // 缩放图片以适应 QLabel 大小，并设置为 QLabel 的背景
    pixmap = pixmap.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->iconlabel->setPixmap(pixmap);

    qDebug() << "Constructing friendwidget for" << _friendname;


}

void friendwidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    // 更改背景颜色或执行其他操作
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(135, 206, 250));
    setAutoFillBackground(true);
    setPalette(pal);

    // 发出信号或执行其他相关操作
    emit clicked();
}

QString friendwidget::getfriendname(){
    return friendname;
}

void friendwidget::setBackgroundColor(const QColor &color)
{
    // Update widget's appearance here
    QPalette pal = palette();
    pal.setColor(QPalette::Window, color);
    setAutoFillBackground(true);
    setPalette(pal);
}
