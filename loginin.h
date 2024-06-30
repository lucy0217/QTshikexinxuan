#ifndef LOGININ_H
#define LOGININ_H

#include <QMainWindow>

namespace Ui {
class loginin;
}

class loginin : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginin(QWidget *parent = nullptr);
    ~loginin();

private:
    Ui::loginin *ui;
};

#endif // LOGININ_H
