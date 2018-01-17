#include "copyfile.h"


CopyFile::CopyFile(QString source, QString destination, quint64 bSize) : sourceFile(source), destinationFile(destination)
{
    this->isCancelled = false;
    this->bufferSize = bSize;
    this->progressValue = 0.0;
    this->position = 0;
}

CopyFile::~CopyFile()
{
    free(buff);
}

qreal CopyFile::progress() const
{
    return progressValue;
}

void CopyFile::setProgress(qreal value)
{
    if (value != progressValue) {
        progressValue = value;
        emit progressChanged();
    }
}

void CopyFile::begin()
{
    if (!sourceFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "could not open source, aborting";
        emit done();
        return;
    }

    fileSize = sourceFile.size();

    if (!destinationFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "could not open destination, aborting";
        // maybe check for overwriting and ask to proceed
        emit done();
        return;
    }

    if (!destinationFile.resize(fileSize))
    {
        qDebug() << "could not resize, aborting";
        emit done();
        return;
    }

    buff = (char*)malloc(bufferSize);

    if (!buff)
    {
        qDebug() << "could not allocate buffer, aborting";
        emit done();
        return;
    }

    QMetaObject::invokeMethod(this, "step", Qt::QueuedConnection);
    //timer.start();
}

void CopyFile::step()
{
    if (!isCancelled)
    {
        if (position < fileSize)
        {
            quint64 chunk = fileSize - position;
            quint64 l = chunk > bufferSize ? bufferSize : chunk;
            sourceFile.read(buff, l);
            destinationFile.write(buff, l);
            position += l;
            sourceFile.seek(position);
            destinationFile.seek(position);
            setProgress((qreal)position / fileSize);
            //std::this_thread::sleep_for(std::chrono::milliseconds(100)); // for testing
            QMetaObject::invokeMethod(this, "step", Qt::QueuedConnection);
        }
        else
        {
            //qDebug() << timer.elapsed();
            emit done();
            return;
        }
    }
    else
    {
        if (!destinationFile.remove())
        {
            qDebug() << "delete failed";
        }
        emit done();
    }
}

void CopyFile::cancel()
{
    isCancelled = true;
}
