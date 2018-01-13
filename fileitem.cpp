#include "fileitem.h"

FileItem::FileItem(QString filePath, bool isDir, FileItem *parent, int size, QDateTime date)
{
    this->filePath = filePath;
    if (!filePath.isEmpty())
    {
        QStringList fullPath = filePath.split("/");
        fileName = fullPath.last();
    }
    this->isDir = isDir;
    this->size = size;
    this->date = date;
    this->parent = parent;
    //this->childList = new QList<FileItem *>();
    if (isDir && !filePath.isEmpty())
    {
        fetched = false;
        addChild(new FileItem("foo", false, this)); //хотя бы один потомок для папки, для таблицы можно и закоментить
    }
}

int FileItem::childCount() const
{
    return childList.count();
}

QString FileItem::getFilePath() const
{
    return filePath;
}

void FileItem::setFilePath(const QString &value)
{
    filePath = value;
}

void FileItem::setSize(int value)
{
    size = value;
}

int FileItem::getFileSizeInBytes() const
{
    return size;
}

QString FileItem::getFileSize() const
{
    return "Тут еще посчитать";
}

QDateTime FileItem::getDate() const
{
    return date;
}

void FileItem::setDate(const QDateTime &value)
{
    date = value;
}

QString FileItem::getFileName() const
{
    return fileName;
}

void FileItem::setFileName(const QString &value)
{
    fileName = value;
}

bool FileItem::getFetched() const
{
    return fetched;
}

void FileItem::setFetched(bool value)
{
    fetched = value;
}

bool FileItem::getIsDir() const
{
    return isDir;
}

void FileItem::setIsDir(bool value)
{
    isDir = value;
}

FileItem *FileItem::getParent() const
{
    return parent;
}

void FileItem::setParent(FileItem *value)
{
    parent = value;
}

QList<FileItem *> FileItem::getChildList() const
{
    return childList;
}

void FileItem::setChildList(const QList<FileItem *> &value)
{
    childList = value;
}

void FileItem::addChild(FileItem *item)
{
    childList.append(item);
}
