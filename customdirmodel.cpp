#include "customdirmodel.h"

CustomDirModel::CustomDirModel(QWidget *parent) : QDirModel(parent)
{

}

QVariant CustomDirModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignBottom;
    }

    if (role == Qt::UserRole)
    {
        qDebug() << "CustomDirModel::data(const QModelIndex &index, int role) " << "Qt::UserRole";
    }

    return QDirModel::data(index, role);
}
