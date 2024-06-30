#include "comment.h"
#include "ui_comment.h"
#include<QHash>
#include<QSqlQuery>
#include<qsqlquerymodel.h>
#include<QSqlError>
#include<qdialog.h>
#include<writecomment.h>
void comment::calculateAverageScore(int _dishId){
    QSqlQuery query;

    // 准备 SQL 查询
    query.prepare("SELECT AVG(score) FROM comments WHERE dishid = :dishid");//AVG函数实现查询均值
    query.bindValue(":dishid", _dishId);

    // 执行查询
    if (!query.exec()) {
        qDebug() << "Error: Fail to execute query." << query.lastError();
        return;
    }

    // 处理查询结果
    if (query.next()) {
        double averageScore = query.value(0).toDouble();
        qDebug() << "Average score for dish" << _dishId << ":" << averageScore;

        // 你可以在此处将平均得分显示到界面的某个部分，例如 QLabel
        ui->label10->setText(QString::number(averageScore));
    } else {
        qDebug() << "No scores found for dish" << _dishId;
    }
}



comment::comment(QWidget *parent,int _userid,QString _username,int _dishid,QString _dishname)
    : QDialog(parent)
    , ui(new Ui::comment)
{
    userid=_userid;
    username=_username;
    dishid=_dishid;
    dishname=_dishname;
    ui->setupUi(this);
    setWindowTitle("用户评价");
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor(240,248,255)); // 设置背景颜色浅蓝色
    this->setPalette(pal);
    // 创建数据模型
    model = new QSqlQueryModel();

    calculateAverageScore(_dishid);


    // 准备查询语句
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT username, comment FROM comments WHERE dishid = ?");
    checkQuery.addBindValue(_dishid);
    //int cnt=0;
   // double sum=0.0;
    // 执行查询
    if (checkQuery.exec()) {
        // 将查询结果设置到数据模型中
        model->setQuery(std::move(checkQuery));

        // 设置每一列的标题文本
        model->setHeaderData(0, Qt::Horizontal, "用户");
        model->setHeaderData(1, Qt::Horizontal, "评价");

        // 将数据模型设置到tableview中
        ui->tableView->setModel(model);
        ui->tableView->resizeColumnToContents(1);
        ui->tableView->resizeColumnToContents(0);
        ui->tableView->setWordWrap(true);

    } else {
        qDebug() << "Error: Failed to execute query. " << checkQuery.lastError().text();
    }



}//构造函数


comment::~comment()
{
    delete ui;
    delete model;
}

void comment::on_button_write_comment_clicked()
{
    writecomment d4(nullptr,userid,username,dishid,dishname);
    d4.setModal(true);
    d4.setWindowTitle("菜品评价");
    d4.exec();
}//连接到写评论的界面

