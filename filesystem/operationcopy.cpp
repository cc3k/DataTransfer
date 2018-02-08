#include "operationcopy.h"

OperationCopy::OperationCopy(QString source, QString destination, quint64 bSize)
{
    this->sourceFile.setFileName(source);
    this->destinationFile.setFileName(destination);
    this->isCancelled = false;
    this->bufferSize = bSize;
    this->progressValue = 0.0;
    this->position = 0;
}

OperationCopy::~OperationCopy()
{
    free(buff);
}

qreal OperationCopy::progress() const
{
    return progressValue;
}

void OperationCopy::setProgress(qreal value)
{
    if (value != progressValue)
    {
        progressValue = value;
        qDebug() << QString::number(value);
        emit progressChanged(value);
    }
}

void OperationCopy::begin()
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

void OperationCopy::step()
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
            //qDebug() << QString::number((qreal)position / fileSize);
            setProgress((qreal)position / fileSize);
            delay(500);
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

void OperationCopy::cancel()
{
    isCancelled = true;
}

void OperationCopy::delay(int msec)
{
    QTime dieTime= QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
