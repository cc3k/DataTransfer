#ifndef FILESYSTEMMOUNTPOINT_H
#define FILESYSTEMMOUNTPOINT_H

#include <QObject>

class FileSystemMountPoint : QObject
{
    Q_OBJECT

public:
    explicit FileSystemMountPoint(QObject *parent = 0, QString name = 0);
    ~FileSystemMountPoint() {}

    QString getName() const;
    void setName(const QString &value);

    QString getRoot() const;
    void setRoot(const QString &value);

    bool getIsReadOnly() const;
    void setIsReadOnly(bool value);

    bool getShowHidden() const;
    void setShowHidden(bool value);

private:
    bool showHidden;
    bool isReadOnly;
    QString name;
    QString root;

};

#endif // FILESYSTEMMOUNTPOINT_H
