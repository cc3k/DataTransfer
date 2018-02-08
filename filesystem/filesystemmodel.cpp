#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(QObject *parent) :QFileSystemModel(parent)
{
    this->root = true;
}

FileSystemModel::~FileSystemModel()
{

}

void FileSystemModel::setIsRoot(bool value)
{
    root = value;
}

bool FileSystemModel::isRoot()
{
    return root;
}

QSet<QPersistentModelIndex> FileSystemModel::getSelection() const
{
    return selection;
}

bool FileSystemModel::selectIndex(QModelIndex &index, Qt::CheckState state)
{
    return setData(index, state, Qt::CheckStateRole);
}

bool FileSystemModel::selectIndexToggle(QModelIndex &index)
{
    if (index.data(Qt::CheckStateRole) == Qt::Checked)
    {
        return setData(index, Qt::Unchecked, Qt::CheckStateRole);
    }

    if (index.data(Qt::CheckStateRole) == Qt::Unchecked)
    {
        return setData(index, Qt::Checked, Qt::CheckStateRole);
    }

    return false;
}

bool FileSystemModel::clearSelection(const QModelIndex index)
{
    selection.clear();
    QModelIndex i = index.parent();
    emit dataChanged(i.child(0, 0), i.child(rowCount() +  1, columnCount(index) -  1));
    return true;
}

bool FileSystemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::CheckStateRole)
    {
        if (value == Qt::Checked)
        {
            selection.insert(index);
        }

        if (value == Qt::Unchecked)
        {
            selection.remove(index);
        }

        emit dataChanged(index, index.parent().child(index.row(), columnCount(index) - 1));
        //тут волшебство с обновлением колонок при выделении, говорим что данные в колонках обновились

        return true;
    }

    return QFileSystemModel::setData(index, value, role);
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if (!root )
    {
        if (role == Qt::CheckStateRole && index.column() == 0 && index.row() > 0)
        {
            return selection.contains(index) ? Qt::Checked : Qt::Unchecked;
        }
    }
    else
    {
        if (role == Qt::CheckStateRole && index.column() == 0)
        {
            return selection.contains(index) ? Qt::Checked : Qt::Unchecked;
        }
    }

    if (role == Qt::ForegroundRole)
    {

        if(selection.contains(index))
        {
            return QVariant(QBrush(Qt::blue));
        }
    }

    if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignBottom;
    }

    return QFileSystemModel::data(index, role);
}

Qt::ItemFlags FileSystemModel::flags(const QModelIndex &index) const
{
    return QFileSystemModel::flags(index) | Qt::ItemIsUserCheckable;
}

