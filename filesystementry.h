#ifndef FILESYSTEMENTRY_H
#define FILESYSTEMENTRY_H

#include <QtCore>

class FileSystemEntry
{

public:
    enum FsType{fslocal = 0, fsremote, fsnone};

    FileSystemEntry(QString name = 0);
    ~FileSystemEntry() {}

    QString getName() const;

    FsType getType() const;
    void setType(const FsType &value);

    QString getHost() const;
    void setHost(const QString &value);

    QString getUser() const;
    void setUser(const QString &value);

    QString getRemote() const;
    void setRemote(const QString &value);

    QString getLocal() const;
    void setLocal(const QString &value);

    QString getId_rsa() const;
    void setId_rsa(const QString &value);

    QString getOptions() const;
    void setOptions(const QString &value);

    bool getIsReadOnly() const;
    void setIsReadOnly(bool value);

    bool getShowHidden() const;
    void setShowHidden(bool value);

private:
    QString name;
    FsType type;
    QString host;
    QString user;
    QString remote;
    QString local;
    QString id_rsa;
    QString options;
    bool isReadOnly;
    bool showHidden;
};

#endif // FILESYSTEMENTRY_H
