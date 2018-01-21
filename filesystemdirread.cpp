#include "filesystemdirread.h"

FileSystemDirRead::FileSystemDirRead(QString path,
                                     QFlags<QDirIterator::IteratorFlag> flag,
                                     QFlags<QDir::Filter> filter)
{
    this->path = path;
    this->flag = flag;
    this->filter = filter;
    this->size = 0;
    this->fileCount = 0;
    this->dirCount = 0;
    this->itemCount = 0;

    this->startTime = 0;
    this->stopTime = 0;
}

FileSystemDirRead::~FileSystemDirRead()
{

}

void FileSystemDirRead::begin()
{
    pathList.clear();
    startTime = QDateTime::currentMSecsSinceEpoch();

        QDir dir;
        dir.setPath(path);
        dir.setFilter(filter);
        qDebug() << "parsing: " << path;
        it = new QDirIterator(dir, flag);
        //тут еще есть follow symlinks!!!

        QMetaObject::invokeMethod(this, "step", Qt::QueuedConnection);
}

void FileSystemDirRead::step()
{
    while (it->hasNext() && !isCanceled)
    {
        pathList.append(it->next());
        if(it->fileInfo().isFile())
        {
            //qDebug() << it->fileInfo().absoluteFilePath();
            size = size + it->fileInfo().size();
            fileCount++;
            dirCount = pathList.size() - fileCount;

            int i = fileCount;
            if (i % 10 ==  0)
            {
                emit progressChanged(pathList.size(), dirCount, fileCount, size);
            }

        }
        //Читал /usr, первый заход 7319, потом 3028, 737, 308, 305 :)
        //append быстрее чем <<, 145К итемов по сети за 26 сек против 29

        // 1st run (net) time  37054 entries:  145766 files:  110404 dirs:  35362 total size:  4449.56 Mb
        // 2nd run (net) time  28250 entries:  145766 files:  110404 dirs:  35362 total size:  4449.56 Mb

        // 1st run (local) time  7346 entries:  175018 files:  133704 dirs:  41314 total size:  3409.61 Mb
        // 2nd run (local) time  3860 entries:  175018 files:  133704 dirs:  41314 total size:  3409.61 Mb
        // 3rd run (local) time  899 entries:  175018 files:  133704 dirs:  41314 total size:  3409.61 Mb
        // 4th run (local) time  717 entries:  175018 files:  133704 dirs:  41314 total size:  3409.61 Mb
    }

    stopTime = QDateTime::currentMSecsSinceEpoch();

    qDebug() << "time " << stopTime - startTime;
    //qDebug() << "entries: " << pathList.size();
    //qDebug() << "files: " << fileCount;
    //qDebug() << "subdirs: " << pathList.size() - fileCount;
    //qDebug() << "total size: " << size/(1024*1024) << "Mb";

    emit progressChanged(pathList.size(), dirCount, fileCount, size);
    emit data(pathList);
    emit done();
    //все сходится с Fly desktop manager
}

void FileSystemDirRead::cancel()
{
    isCanceled = true;
}
