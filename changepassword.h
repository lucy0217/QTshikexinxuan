#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>

namespace Ui {
class changepassword;
}

class changepassword : public QDialog
{
    Q_OBJECT

public:
    explicit changepassword(QWidget *parent = nullptr,QString a=QString());
    ~changepassword();

private slots:
    void on_confirmbutton_clicked();

private:
    Ui::changepassword *ui;
    QString username;
};

#endif // CHANGEPASSWORD_H
