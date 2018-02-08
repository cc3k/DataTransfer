#ifndef OPERATIONCALCULATOR_H
#define OPERATIONCALCULATOR_H

#include <QObject>
#include <QDateTime>
#include <QDir>
#include <QFlags>
#include <QDirIterator>
#include <QStringList>

#include <QDebug>

class OperationCalculator : public QObject
{
    Q_OBJECT
public:
    OperationCalculator
    (QStringList inputPathList,
     QFlags<QDirIterator::IteratorFlag> flag = QDirIterator::NoIteratorFlags,
     QFlags<QDir::Filter> filter =
            QDir::AllEntries |
            QDir::Hidden |
            QDir::NoDotAndDotDot);
    OperationCalculator
    (QFlags<QDirIterator::IteratorFlag> flag = QDirIterator::NoIteratorFlags,
     QFlags<QDir::Filter> filter =
            QDir::AllEntries |
            QDir::Hidden |
            QDir::NoDotAndDotDot);
    ~OperationCalculator();

    qint64 getSize() const;
    QStringList getFileList() const;
    QStringList getDirList() const;
    QStringList getErrList() const;
    void setInputPathList(const QStringList &value);

public slots:
    void begin();
    void cancel();
    void step();

private:
    QStringList inputPathList;

    QStringList fileList;
    QStringList dirList;
    QStringList errList;
    QDirIterator *it;

    qint64 size;

    int fileCount;
    int dirCount;
    int errCount;
    int totalCount;

    int startTime;
    int stopTime;
    QFlags<QDir::Filter> filter;
    QFlags<QDirIterator::IteratorFlag> flag;

    bool isCanceled;

signals:
    void progress(int total, int dir, int file, int err, double size);
    void done(int i = 0);
};

#endif // OPERATIONCALCULATOR_H
