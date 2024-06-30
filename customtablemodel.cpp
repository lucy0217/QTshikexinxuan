#include "customtablemodel.h"

Qt::ItemFlags CustomTableModel::flags(const QModelIndex &index) const
{
    if (index.column() == 0) {  // 第一列设为可点击
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return QSqlQueryModel::flags(index);
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole && index.isValid()) {
        // 最后一列是我们要转换显示的列(食堂地点）
        if (index.column() == columnCount() - 1) {
            int value = QSqlQueryModel::data(index, role).toInt();
            switch (value) {
            case 0: return QString("家园食堂");
            case 1: return QString("燕南食堂");
            case 2:return QString("学一食堂");
            case 3:return QString("学五食堂");
            }
        }
    }
    // 对于其他情况，调用基类的方法
    return QSqlQueryModel::data(index, role);
}
