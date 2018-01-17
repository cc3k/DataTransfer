#ifndef COPYFILE_H
#define COPYFILE_H

#include <QObject>
#include <QFile>

#include <QDebug>

class CopyFile : public QObject {
    Q_OBJECT
    Q_PROPERTY(qreal progress READ progress WRITE setProgress NOTIFY progressChanged)
public:
    CopyFile(QString source, QString destination, quint64 bSize = 1024 * 1024);
    ~CopyFile();

    qreal progress() const;
    void setProgress(qreal value);

public slots:
    void begin();
    void step();
    void cancel();

signals:
    void progressChanged();
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
    //QElapsedTimer timer;
};

#endif // COPYFILE_H
