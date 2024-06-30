#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QSqlQueryModel>

class CustomTableModel : public QSqlQueryModel
{
public:
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override; // 重写 data 方法
};//继承querymodel类

#endif // CUSTOMTABLEMODEL_H
