#ifndef CHANGEICON_H
#define CHANGEICON_H

#include <QDialog>
class mainwindow;
namespace Ui {
class changeicon;
}

class changeicon : public QDialog
{
    Q_OBJECT

public:
    explicit changeicon(QWidget *parent = nullptr,QString a=QString(),mainwindow* m=nullptr);
    ~changeicon();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
signals:
    void iconChanged(int newIcon);
private:
    Ui::changeicon *ui;
    QString username;
public:
    mainwindow *parentwindow;//父窗口的指针
};

#endif // CHANGEICON_H
