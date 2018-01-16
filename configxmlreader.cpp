#include "configxmlreader.h"

ConfigXmlReader::ConfigXmlReader(QString fileName, QObject *parent) : QObject(parent)
{
    this->fileName = fileName;
    fileSystemEntryList.clear();
}

QList<FileSystemEntry *> ConfigXmlReader::getFileSystemEntryList()
{
    fileSystemEntryList.clear();
    file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly))
    {
        return fileSystemEntryList;
    }

    reader = new QXmlStreamReader;
    reader->setDevice(file);

    while (!reader->atEnd() && !reader->hasError())
    {
        QXmlStreamReader::TokenType token = reader->readNext();
        if (token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        if (token == QXmlStreamReader::StartElement)
        {
            if (reader->name() == "stations")
            {
                qDebug() << "Чтение конфигурации <stations> node";
            }

            if (reader->name() == "entry")
            {
                qDebug() << "Чтение конфигурации <entry> node";

                FileSystemEntry *fileSystemEntry = new FileSystemEntry(reader->attributes().value("name").toString());

                int type = reader->attributes().value("type").toInt();
                switch (type)
                {
                case 1:
                    fileSystemEntry->setType(FileSystemEntry::fslocal);
                    break;

                case 2:
                    fileSystemEntry->setType(FileSystemEntry::fsremote);
                    break;

                default:
                    qDebug() << "incorrect entry type";
                    break;
                }



                fileSystemEntryList.append(fileSystemEntry);

            }

        }
    }
    return fileSystemEntryList;
}
