#ifndef FILESYSTEMMOUNTPOINT_H
#define FILESYSTEMMOUNTPOINT_H

#include <QObject>
#include "filesystemwidget.h"

class FileSystemMountPoint : QObject
{
    Q_OBJECT

public:
    explicit FileSystemMountPoint(QObject *parent = 0, QString name = 0);
    ~FileSystemMountPoint() {}

    QString getName() const;

    bool getIsReadOnly() const;
    void setIsReadOnly(bool value);

    bool getShowHidden() const;
    void setShowHidden(bool value);

    QString getLocalRoot() const;
    void setLocalRoot(const QString &value);

    QString getRemoteRoot() const;
    void setRemoteRoot(const QString &value);

    FileSystemWidget *getFileSystemWidget() const;

    QString getRsaPath() const;
    void setRsaPath(const QString &value);

    bool setupWidget();

public slots:
    void refreshWidget();
    void mount();
    void umount();

private:
    bool isMount;
    bool showHidden;
    bool isReadOnly;
    QString name;

    QString rsaPath;
    QString localRoot;
    QString remoteRoot;

    FileSystemWidget *fileSystemWidget;
};

#endif // FILESYSTEMMOUNTPOINT_H
