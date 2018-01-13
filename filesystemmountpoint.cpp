#include "filesystemmountpoint.h"

FileSystemMountPoint::FileSystemMountPoint(QObject *parent, QString name) : QObject(parent)
{
    this->name = name;
}

QString FileSystemMountPoint::getName() const
{
    return name;
}

void FileSystemMountPoint::setName(const QString &value)
{
    name = value;
}

QString FileSystemMountPoint::getRoot() const
{
    return root;
}

void FileSystemMountPoint::setRoot(const QString &value)
{
    root = value;
}

bool FileSystemMountPoint::getIsReadOnly() const
{
    return isReadOnly;
}

void FileSystemMountPoint::setIsReadOnly(bool value)
{
    isReadOnly = value;
}

bool FileSystemMountPoint::getShowHidden() const
{
    return showHidden;
}

void FileSystemMountPoint::setShowHidden(bool value)
{
    showHidden = value;
}
