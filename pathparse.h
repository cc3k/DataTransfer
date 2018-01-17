#ifndef PATHPARSE_H
#define PATHPARSE_H

#include <QObject>
#include <QDateTime>
#include <QDir>
#include <QDirIterator>
#include <QStringList>

#include <QDebug>

class PathParse : public QObject
{
    Q_OBJECT
public:
    explicit PathParse(QString path);
    ~PathParse() {}

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

#endif // PATHPARSE_H
