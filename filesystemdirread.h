#ifndef FILESYSTEMFILEPATH_H
#define FILESYSTEMFILEPATH_H

#include <QObject>
#include <QDateTime>
#include <QDir>
#include <QDirIterator>
#include <QStringList>

#include <QDebug>

class FileSystemDirRead : public QObject
{
    Q_OBJECT
public:
    explicit FileSystemDirRead(QString path,
                               QFlags<QDirIterator::IteratorFlag> flag = QDirIterator::NoIteratorFlags,
                               QFlags<QDir::Filter> filter = QDir::Dirs | QDir::Files | QDir::NoSymLinks |
            QDir::NoDotAndDotDot);
    ~FileSystemDirRead();

public slots:
    void begin();
    void cancel();
    void step();

private slots:


private:
    QString path;
    QStringList itemList;
    QDirIterator *it;

    double size;
    int fileCount;
    int dirCount;
    int itemCount;

    int startTime;
    int stopTime;
    QFlags<QDir::Filter> filter;
    QFlags<QDirIterator::IteratorFlag> flag;

    bool isCanceled;

signals:
    void progressChanged(int itemCount, int dirCount, int fileCount, double size);
    void data(QStringList);
    void done();
};

#endif // FILESYSTEMFILEPATH_H
