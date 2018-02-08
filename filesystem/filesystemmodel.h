#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QObject>
#include <QSet>
#include <QPersistentModelIndex>
#include <QFileSystemModel>
#include <QBrush>
#include <QDebug>

class FileSystemModel : public QFileSystemModel
{
public:
    explicit FileSystemModel(QObject *parent);
    ~FileSystemModel();

    void setIsRoot(bool value);
    bool isRoot();

    QSet<QPersistentModelIndex> getSelection() const;

    //selection
    bool selectIndex(QModelIndex &index, Qt::CheckState state);
    bool selectIndexToggle(QModelIndex &index);
    bool clearSelection(const QModelIndex index);

    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;


private:
    QSet<QPersistentModelIndex> selection; //где хранить выделение
    bool root; //для отрисовки чекбокса

protected:
};

#endif // FILESYSTEMMODEL_H
