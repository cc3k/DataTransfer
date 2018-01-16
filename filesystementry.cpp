#include "filesystementry.h"

FileSystemEntry::FileSystemEntry(QString name)
{
    this->name = name;
    this->type = FileSystemEntry::fsnone;

    isReadOnly = true;
    showHidden = false;
}

QString FileSystemEntry::getName() const
{
    return name;
}

FileSystemEntry::FsType FileSystemEntry::getType() const
{
    return type;
}

void FileSystemEntry::setType(const FsType &value)
{
    type = value;
}

QString FileSystemEntry::getHost() const
{
    return host;
}

void FileSystemEntry::setHost(const QString &value)
{
    host = value;
}

QString FileSystemEntry::getUser() const
{
    return user;
}

void FileSystemEntry::setUser(const QString &value)
{
    user = value;
}

QString FileSystemEntry::getRemote() const
{
    return remote;
}

void FileSystemEntry::setRemote(const QString &value)
{
    remote = value;
}

QString FileSystemEntry::getLocal() const
{
    return local;
}

void FileSystemEntry::setLocal(const QString &value)
{
    local = value;
}

QString FileSystemEntry::getId_rsa() const
{
    return id_rsa;
}

void FileSystemEntry::setId_rsa(const QString &value)
{
    id_rsa = value;
}

QString FileSystemEntry::getOptions() const
{
    return options;
}

void FileSystemEntry::setOptions(const QString &value)
{
    options = value;
}

bool FileSystemEntry::getIsReadOnly() const
{
    return isReadOnly;
}

void FileSystemEntry::setIsReadOnly(bool value)
{
    isReadOnly = value;
}

bool FileSystemEntry::getShowHidden() const
{
    return showHidden;
}

void FileSystemEntry::setShowHidden(bool value)
{
    showHidden = value;
}
