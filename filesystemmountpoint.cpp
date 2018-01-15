#include "filesystemmountpoint.h"

FileSystemMountPoint::FileSystemMountPoint(QObject *parent, QString name) : QObject(parent)
{
    isReadOnly = true;
    showHidden = false;

    this->name = name;
}

QString FileSystemMountPoint::getName() const
{
    return name;
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

QString FileSystemMountPoint::getLocalRoot() const
{
    return localRoot;
}

void FileSystemMountPoint::setLocalRoot(const QString &value)
{
    localRoot = value;
}

QString FileSystemMountPoint::getRemoteRoot() const
{
    return remoteRoot;
}

void FileSystemMountPoint::setRemoteRoot(const QString &value)
{
    remoteRoot = value;
}

FileSystemWidget *FileSystemMountPoint::getFileSystemWidget() const
{
    return fileSystemWidget;
}

bool FileSystemMountPoint::setupWidget()
{

}

void FileSystemMountPoint::refreshWidget()
{

}

void FileSystemMountPoint::mount()
{

}

void FileSystemMountPoint::umount()
{

}

QString FileSystemMountPoint::getRsaPath() const
{
    return rsaPath;
}

void FileSystemMountPoint::setRsaPath(const QString &value)
{
    rsaPath = value;
}
