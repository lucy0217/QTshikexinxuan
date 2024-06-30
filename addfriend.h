#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QDialog>

namespace Ui {
class addfriend;
}

class addfriend : public QDialog
{
    Q_OBJECT

public:
    explicit addfriend(QWidget *parent = nullptr, QString a = QString(), QString b = QString());
    ~addfriend();

private slots:
    void on_cancelbutton_clicked();

    void on_okbutton_clicked();

private:
    Ui::addfriend *ui;
    QString username1;
    QString username2;
};

#endif // ADDFRIEND_H
