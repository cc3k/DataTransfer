#ifndef OPERATIONCOPY_H
#define OPERATIONCOPY_H

#include <QObject>
#include <QFile>

#include <QTime>
#include <QCoreApplication>

#include <QDebug>

class OperationCopy : public QObject {
    Q_OBJECT
    Q_PROPERTY(qreal progress READ progress WRITE setProgress NOTIFY progressChanged)
public:
    OperationCopy(QString source, QString destination, quint64 bSize = 1024 * 1024);
    ~OperationCopy();

    qreal progress() const;
    void setProgress(qreal value);

public slots:
    void begin();
    void step();
    void cancel();

signals:
    void progressChanged(qreal progress);
    void done();

private:
    bool isCancelled;
    quint64 bufferSize;
    qreal progressValue;
    QFile sourceFile;
    QFile destinationFile;
    quint64 fileSize;
    quint64 position;
    char * buff;

    void delay(int msec);
    //QElapsedTimer timer;
};

#endif // OPERATIONCOPY_H
