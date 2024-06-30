#ifndef FRIENDINFO_H
#define FRIENDINFO_H

#include <QDialog>

namespace Ui {
class friendinfo;
}

class friendinfo : public QDialog
{
    Q_OBJECT

public:
    explicit friendinfo(QWidget *parent = nullptr,QString a=QString());
    ~friendinfo();

private:
    Ui::friendinfo *ui;
    QString friendname;

};

#endif // FRIENDINFO_H
