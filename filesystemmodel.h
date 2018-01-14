#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QAbstractItemModel>
#include <QFileIconProvider>
#include <QtCore>

#include "fileitem.h"

class FileSystemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Columns {NameColumn = 0, SizeColumn, TypeColumn,DateColumn};

    explicit FileSystemModel(QAbstractItemModel *parent = 0);
    ~FileSystemModel() {}

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; // Важная виртуальная функция, ее определение обязательно отвечает за вывод всех информации в дереве
    Qt::ItemFlags flags(const QModelIndex &index) const; // (виртуальная, обязательная)
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const; // Отвечает за заголовки столбцов (виртуальная, обязательная)
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const; // Возвращает индекс элемента (виртуальная, обязательная)
    QModelIndex parent(const QModelIndex &index) const; // Возвращает индекс родителя (виртуальная, обязательная)
    int rowCount(const QModelIndex &parent = QModelIndex()) const; // (виртуальная, обязательная)
    int columnCount(const QModelIndex &parent = QModelIndex()) const; // (виртуальная, обязательная)
    FileItem *item(QModelIndex index) const { return static_cast<FileItem *>(index.internalPointer()); } // Возвращает элемент по индексу
    FileItem *getRootItem();
    bool hasChildren(const QModelIndex &index) const;
    bool canFetchMore(const QModelIndex &index) const;
    void fetchMore(const QModelIndex &index); // Выполняется когда нажали плюсик(или минусик) (виртуальная, обязательная)
    void refresh();

private:
    QList<FileItem *> getFileList(FileItem *parent); //сюда или нет?

    FileItem *rootItem;
    static const int columns = 4; // Колонки всегда 4
    QFileIconProvider iconProvider; // Стандартные иконки дисков, файлов и папок
    int lastSortColumn;
    int lastSortOrder;

protected:
    void readDir(FileItem *item); // Загружает детей
};

#endif // FILESYSTEMMODEL_H
