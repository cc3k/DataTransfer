#ifndef CONFIGXMLREADER_H
#define CONFIGXMLREADER_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>

#include <QDebug>

#include "filesystementry.h"

class ConfigReader : public QObject
{
    Q_OBJECT
public:
    explicit ConfigReader(QString fileName, QObject *parent = 0);
    ~ConfigReader();

    QList<FileSystemEntry *> getEntryList();

private:
    QString fileName;
    QFile *file;
    QXmlStreamReader *reader;

    QList<FileSystemEntry*> entryList;

signals:

public slots:
};

#endif // CONFIGXMLREADER_H
