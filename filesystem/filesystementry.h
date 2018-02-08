#ifndef FILESYSTEMENTRY_H
#define FILESYSTEMENTRY_H

#include <QString>
#include <QDir>

class FileSystemEntry
{

public:
    enum FsType{fslocal = 0, fsremote, fsnone};

    explicit FileSystemEntry(QString name = 0);

    QString getName() const;
    void setName(const QString &value);

    FsType getType() const;
    void setType(const FsType &value);

    QString getHost() const;
    void setHost(const QString &value);

    QString getUser() const;
    void setUser(const QString &value);

    QString getRemote() const;
    void setRemote(const QString &value);

    QString getMount() const;
    void setMount(const QString &value);

    QString getId_rsa() const;
    void setId_rsa(const QString &value);

    QString getOptions() const;
    void setOptions(const QString &value);

    bool isReadOnly() const;
    void setReadOnly(bool value);

    bool isShowHidden() const;
    void setShowHidden(bool value);

    bool isShowSymlink() const;
    void setShowSymlink(bool value);

    void setMode(const QString &value);

    QDir::Filters getFilterRoot() const;
    QDir::Filters getFilterBase() const;

private:
    QString name;
    FsType type;
    QString host;
    QString user;
    QString remote;
    QString mount;
    QString id_rsa;
    QString options;
    bool readOnly;
    bool showHidden;
    bool showSymlink;

    QDir::Filters filterRoot;
    QDir::Filters filterBase;
};

#endif // FILESYSTEMENTRY_H
