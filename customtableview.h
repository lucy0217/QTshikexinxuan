#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QTableView>
#include <QMouseEvent>

class CustomTableView : public QTableView
{
    Q_OBJECT
public:
    explicit CustomTableView(QWidget *parent = nullptr,QString _username=QString());
    void setModel(QAbstractItemModel *model) override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
private:
    QString username;
    int userid;
};

#endif // CUSTOMTABLEVIEW_H
