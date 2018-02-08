#include "operationcalculator.h"

OperationCalculator::OperationCalculator(QStringList pathList,
                                         QFlags<QDirIterator::IteratorFlag> flag,
                                         QFlags<QDir::Filter> filter)
{
    this->isCanceled = false;

    this->inputPathList = pathList;

    this->flag = flag;
    this->filter = filter;

    this->size = 0;

    this->fileCount = 0;
    this->dirCount = 0;
    this->errCount = 0;
    this->totalCount = 0;

    this->startTime = 0;
    this->stopTime = 0;
}

OperationCalculator::OperationCalculator(QFlags<QDirIterator::IteratorFlag> flag, QFlags<QDir::Filter> filter)
{
    this->isCanceled = false;

    this->flag = flag;
    this->filter = filter;

    this->size = 0;

    this->fileCount = 0;
    this->dirCount = 0;
    this->errCount = 0;
    this->totalCount = 0;

    this->startTime = 0;
    this->stopTime = 0;
}

OperationCalculator::~OperationCalculator()
{
    //delete it;
}

qint64 OperationCalculator::getSize() const
{
    return size;
}

QStringList OperationCalculator::getFileList() const
{
    return fileList;
}

QStringList OperationCalculator::getDirList() const
{
    return dirList;
}

QStringList OperationCalculator::getErrList() const
{
    return errList;
}

void OperationCalculator::begin()
{
    dirList.clear();
    fileList.clear();
    errList.clear();

    startTime = QDateTime::currentMSecsSinceEpoch();

    for (int i = 0; i < inputPathList.size(); i++)
    {
        if (QFileInfo(inputPathList.at(i)).isFile())
        {
            QFile file(inputPathList.at(i));

            if (file.open(QIODevice::ReadOnly))
            {
                fileCount++;
                size = size + file.size();
                fileList.append(inputPathList.at(i));
            }
            else
            {
                errCount++;
                errList.append(inputPathList.at(i));
            }

            totalCount++;

            if (totalCount % 10 ==  0)
            {
                emit progress(totalCount, dirCount, fileCount, errCount, size);
            }
        }
    }

    for (int i = 0; i < inputPathList.size(); i++)
    {
        if (QFileInfo(inputPathList.at(i)).isDir())
        {
            QDir dir(inputPathList.at(i));
            if(dir.isReadable())
            {
                dirCount++;
                dir.setFilter(filter);
                it = new QDirIterator(dir, flag);
                QMetaObject::invokeMethod(this, "step", Qt::DirectConnection);
            }
            else
            {
                errCount++;
                errList.append(inputPathList.at(i));
            }

            totalCount++;
        }
    }

    stopTime = QDateTime::currentMSecsSinceEpoch();
    //qDebug() << (stopTime - startTime);
    emit progress(totalCount, dirCount, fileCount, errCount, size);
    emit done();
}

void OperationCalculator::step()
{
    while (it->hasNext() && !isCanceled)
    {
        QFileInfo item(it->next());

        if(item.isFile())
        {
            QFile file(item.absoluteFilePath());

            if (file.open(QIODevice::ReadOnly))
            {
                fileCount++;
                size = size + file.size();
                fileList.append(item.absoluteFilePath());
            }
            else
            {
                errCount++;
                errList.append(item.absoluteFilePath());
            }

            totalCount++;

            if (totalCount % 10 ==  0)
            {
                emit progress(totalCount, dirCount, fileCount, errCount, size);
            }
        }

        if(item.isDir())
        {
            QDir dir(item.absoluteFilePath());

            if (dir.isReadable())
            {
                dirCount++;
                dirList.append(item.absoluteFilePath());
            }
            else
            {
                errCount++;
                errList.append(item.absoluteFilePath());
            }

            totalCount++;

            if (totalCount % 10 ==  0)
            {
                emit progress(totalCount, dirCount, fileCount, errCount, size);
            }
        }
    }
}

void OperationCalculator::setInputPathList(const QStringList &value)
{
    inputPathList = value;
}

void OperationCalculator::cancel()
{
    isCanceled = true;
}
