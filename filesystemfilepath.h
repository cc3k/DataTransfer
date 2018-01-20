#ifndef FILESYSTEMFILEPATH_H
#define FILESYSTEMFILEPATH_H

#include <QObject>
#include <QDateTime>
#include <QDir>
#include <QDirIterator>
#include <QStringList>

#include <QDebug>

class FileSystemFilePath : public QObject
{
    Q_OBJECT
public:
    explicit FileSystemFilePath(QString path);
    ~FileSystemFilePath() {}

    QStringList getPathList() const;

public slots:
    void begin();
    void step();
    void cancel();

private:
    QString path;
    QStringList pathList;
    QDir dir;
    QDirIterator *it;
    double size;
    int fileCount;
    int dirCount;
    int itemCount;

    int startTime;
    int stopTime;
    bool isCanceled;

signals:
    void progressChanged(int itemCount, int dirCount, int fileCount, double size);
    void data(QStringList);
    void done();
};

#endif // FILESYSTEMFILEPATH_H
