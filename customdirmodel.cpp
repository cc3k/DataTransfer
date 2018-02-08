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

    if (role == Qt::TextColorRole)
    {
        //return QVariant::fromValue(QColor(Qt::blue));
    }

    return QDirModel::data(index, role);
}

bool CustomDirModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role = Qt::TextColorRole)
    {

    }
    return false;
}
