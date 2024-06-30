#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mydialog.h"
#include<QtDebug>
#include<QSqlError>
#include<qsqlquerymodel.h>
#include<qsqlquery.h>
#include<qtableview.h>
#include<qheaderview.h>
#include<QMouseEvent>
#include<customtablemodel.h>
#include<customtableview.h>
#include<QPixmap>
#include<setting.h>
#include<qfile.h>
#include<changeicon.h>
extern QSqlDatabase db;  // 引用全局变量 db
bool tableExists(QString tableName, QSqlDatabase db); // 声明tableExists函数
void MainWindow::updateUserIcon(int newIcon) {
    // 更新用户头像显示的逻辑
    QString s=":/new/prefix1/images/";
    s+=QString::number(newIcon);
    s+=".jpg";
    QPixmap pixmap(s);  // 加载图片资源
    QSize iconSize = ui->userpictrue->size(); // 获取按钮大小
    pixmap = pixmap.scaled(iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->userpictrue->setIcon(QIcon(pixmap));    // 设置按钮图标
    ui->userpictrue->setIconSize(iconSize); // 设置图标尺寸，保持与图片大小一致
}

MainWindow::MainWindow(QWidget *parent,QString a,QString b,int x1,int x2,int x3,int x4,int x5)
    : QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,current_user(a,b,x1,x2,x3,x4,x5)
{
    ui->setupUi(this);
    setWindowTitle("食客心选");
    this->setFixedSize(1000, 640);
    myicon=new changeicon(this,current_user.username);
  connect(myicon, &changeicon::iconChanged, this, &MainWindow::updateUserIcon);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor(240,248,255)); // 设置背景颜色浅蓝色
    this->setPalette(pal);

    //找到当前用户的icon值，显示对应的图像
    QSqlQuery query;
    QString sqlSelect = "SELECT icon FROM users WHERE username=:username";
    query.prepare(sqlSelect);
    query.bindValue(":username",current_user.username);

    if (query.exec()) {
        // 查询成功执行
        if (query.next()) {
            // 在这里获取结果
            int tmp = query.value(0).toInt();
            qDebug() << "显示头像！！ icon值：" << tmp;
            QString s=":/new/prefix1/images/";
            s+=QString::number(tmp);
            s+=".jpg";
            QPixmap pixmap(s);  // 加载图片资源
            if (pixmap.isNull()) {
                qDebug() << "Pixmap is empty. Image load failed or no image loaded.";
            } else {
                qDebug() << "Pixmap loaded successfully.";
                // 这里可以继续处理载入成功后的操作
            }
            QSize iconSize = ui->userpictrue->size(); // 获取按钮大小
            pixmap = pixmap.scaled(iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->userpictrue->setIcon(QIcon(pixmap));    // 设置按钮图标
            ui->userpictrue->setIconSize(iconSize); // 设置图标尺寸，保持与图片大小一致
        }
    }




    customModel = new CustomTableModel;
    customView = new CustomTableView(nullptr,a);




    //ui->comboBox1->addItem("主食");
    ui->comboBox1->addItem("非主食");
    ui->comboBox1->addItem("米");
    ui->comboBox1->addItem("面/粉");
    ui->comboBox1->addItem("不限");

    //ui->comboBox2->addItem("辣度");
    ui->comboBox2->addItem("不辣");
    ui->comboBox2->addItem("辣");
    ui->comboBox2->addItem("不限");

   // ui->comboBox3->addItem("荤素");
    ui->comboBox3->addItem("荤");
    ui->comboBox3->addItem("素");
    ui->comboBox3->addItem("不限");

    //ui->comboBox4->addItem("中/西餐");
    ui->comboBox4->addItem("中餐");
    ui->comboBox4->addItem("其他");
    ui->comboBox4->addItem("不限");

    //ui->comboBox5->addItem("风味");
    ui->comboBox5->addItem("江南");
    ui->comboBox5->addItem("山东");
    ui->comboBox5->addItem("新疆");
    ui->comboBox5->addItem("广东");
    ui->comboBox5->addItem("闽南");
    ui->comboBox5->addItem("蜀湘");
    ui->comboBox5->addItem("西餐");
    ui->comboBox5->addItem("日韩");
    ui->comboBox5->addItem("其他");
    ui->comboBox5->addItem("不限");

    //StarShapeButton *mystar = new StarShapeButton(this); // 将父窗口设置为 MainWindow
    //mystar->setText("Star Shape Button");
   // mystar->setGeometry(500, 300, 200, 200); // 设置按钮位置和大小
   // mystar->show();



}//mainwindow的构造函数,对按钮进行初始化

MainWindow::~MainWindow()
{
    delete ui;
    if(customModel){
        delete customModel;
    }
    if(customView){
        delete customView;
    }
    if(myicon){
        delete myicon;
    }
}

void MainWindow::on_add_dish_clicked()
{
    MyDialog d1;
    d1.setModal(true);
    d1.setWindowTitle("添加菜品");
    d1.exec();

}//在这里面要实现获取combobox的信息并把新菜品信息添加到“表”中


// 修改查询按钮的点击事件处理函数
void MainWindow::on_selectButton_clicked()
{
    // 其他查询逻辑不变
    int x1 = ui->comboBox1->currentIndex(); // 在数据库中索引从1开始
    int x2 = ui->comboBox2->currentIndex();
    int x3 = ui->comboBox3->currentIndex();
    int x4 = ui->comboBox4->currentIndex();
    int x5 = ui->comboBox5->currentIndex();

    qDebug()<<"需要查询的值是："<<x1<<x2<<x3<<x4<<x5;

    QSqlQuery query;
    QString sqlSelect = "SELECT * FROM menu WHERE 1=1";  // 初始查询语句，始终为真

    if(x1!=3){
        sqlSelect += " AND ismain = :x1";

    }
    if (x2!=2) {
        sqlSelect += " AND spice = :x2";
    }
    if (x3!=2) {
        sqlSelect += " AND vegetarian = :x3";
    }
    if(x4!=2){
         sqlSelect += " AND cuisine = :x4";
    }
    if(x5!=9){
         sqlSelect += " AND flavor = :x5";
    }


    query.prepare(sqlSelect);


    if(x1!=3){
        query.bindValue(":x1", x1);

    }
    if (x2!=2) {
        query.bindValue(":x2", x2);
    }
    if (x3!=2) {
        query.bindValue(":x3", x3);
    }
    if(x4!=2){
        query.bindValue(":x4", x4);
    }
    if(x5!=9){
        query.bindValue(":x5", x5);
    }



   // QString sqlSelect = "SELECT * FROM menu WHERE ismain = :x1 AND spice = :x2 AND vegetarian = :x3 AND cuisine = :x4 AND flavor = :x5";




    if (!query.exec()) {
        qDebug() << "Error: Failed to execute query." << query.lastError();
        return;
    }

    // 创建 QSqlQueryModel
   // QSqlQueryModel *model = new QSqlQueryModel;

    // 将 QSqlQuery 对象移动给 QSqlQueryModel
    //model->setQuery(std::move(query));


  //  CustomTableModel *customModel = new CustomTableModel;
    customModel->setQuery(std::move(query));

   // CustomTableView *customView = new CustomTableView;
    customView->setModel(customModel);

    // 隐藏其他列
    customView->hideColumn(0);
    customView->hideColumn(2);
    customView->hideColumn(3);
    customView->hideColumn(4);
    customView->hideColumn(5);
    customView->hideColumn(6);

    // 设置列宽、行高等样式
    customView->resize(600,400);

    customView->show();

    // 注意：需要在适当的时候释放 customModel 和 customView 的内存
    //这个待会问一问chat,该在哪里释放
}

void MainWindow::on_myfriend_clicked()
{
    myfriendlist=new friendlist(this,current_user.username);
    qDebug()<<"好友按钮被点击";
    myfriendlist->show();

}//好友部分,接到friendlist界面上


void MainWindow::on_loginsetting_clicked()
{
    Setting =new setting(nullptr,current_user.username);//把名字传进去，便于后面修改密码这些操作
    Setting->exec();
}//登录设置按钮，转到setting界面


void MainWindow::on_userpictrue_clicked()
{
    myicon->show();
}//点击修改头像后，转到changeicon界面

