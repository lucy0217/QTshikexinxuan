#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include<changepassword.h>
namespace Ui {
class setting;
}

class setting : public QDialog
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr,QString _username=QString());
    ~setting();

private slots:
    void on_savebutton_clicked();

    void on_pushButton_clicked();

private:
    Ui::setting *ui;
    QString username;//记录当前用户的名字
    changepassword* change;
};

#endif // SETTING_H
