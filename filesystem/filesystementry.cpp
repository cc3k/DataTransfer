#include "filesystementry.h"

FileSystemEntry::FileSystemEntry(QString name)
{
    this->name = name;
    this->type = FileSystemEntry::fsnone;

    readOnly = true;
    showHidden = false;
    showSymlink = false;

    filterRoot = QDir::AllEntries | QDir::NoDotAndDotDot;
    filterBase = QDir::AllEntries | QDir::NoDot;
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

QString FileSystemEntry::getMount() const
{
    return mount;
}

void FileSystemEntry::setMount(const QString &value)
{
    mount = value;
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

bool FileSystemEntry::isReadOnly() const
{
    return readOnly;
}

void FileSystemEntry::setReadOnly(bool value)
{
    readOnly = value;
}

bool FileSystemEntry::isShowHidden() const
{
    return showHidden;
}

void FileSystemEntry::setShowHidden(bool value)
{
    showHidden = value;
}

void FileSystemEntry::setMode(const QString &value)
{
    QStringList modeList = value.split(",");

    for (int i = 0; i < modeList.size(); i++)
    {
        if (modeList.at(i) == "show_hid")
        {
            showHidden = true;
            filterRoot = filterRoot | QDir::Hidden;
            filterBase = filterBase | QDir::Hidden;
        }

        if (modeList.at(i) == "mount_rw")
        {
            readOnly = false;
        }

        if (modeList.at(i) == "mount_ro")
        {
            readOnly = true;
        }

        if (modeList.at(i) == "no_symlink")
        {
            showSymlink = true;
            filterRoot = filterRoot | QDir::NoSymLinks;
            filterBase = filterBase | QDir::NoSymLinks;
        }
    }
}

QDir::Filters FileSystemEntry::getFilterRoot() const
{
    return filterRoot;
}

QDir::Filters FileSystemEntry::getFilterBase() const
{
    return filterBase;
}

void FileSystemEntry::setName(const QString &value)
{
    name = value;
}

bool FileSystemEntry::isShowSymlink() const
{
    return showSymlink;
}

void FileSystemEntry::setShowSymlink(bool value)
{
    showSymlink = value;
}
