#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(QAbstractItemModel *parent) : QAbstractItemModel(parent)
{
    lastSortColumn = 0;
    lastSortOrder = Qt::AscendingOrder;

    QString path = QDir::rootPath();
    rootItem = new FileItem(path, true);
    readDir(rootItem); //читаем содержимое корня сразу же

}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{

}

Qt::ItemFlags FileSystemModel::flags(const QModelIndex &index) const
{

}

QVariant FileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{

}

QModelIndex FileSystemModel::index(int row, int column, const QModelIndex &parent) const
{

}

QModelIndex FileSystemModel::parent(const QModelIndex &index) const
{

}

int FileSystemModel::rowCount(const QModelIndex &parent) const
{

}

int FileSystemModel::columnCount(const QModelIndex &parent) const
{
    return columns;
}

FileItem *FileSystemModel::getRootItem()
{
    return rootItem;
}

bool FileSystemModel::hasChildren(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return true;
    }

    if (item(index)->getFetched())
    {
        return item(index)->childCount();
    }
    else
    {
        return true;
    }
}

bool FileSystemModel::canFetchMore(const QModelIndex &index) const
{
    return index.isValid()? !item(index)->getFetched(): true;
}

void FileSystemModel::fetchMore(const QModelIndex &index)
{
    if (index.isValid() && !item(index)->getFetched()) // Если еще ни разу детей не загружали то загружаем.
    {
        readDir(item(index));
        item(index)->setFetched(true);
        refresh();
    }
}

void FileSystemModel::refresh()
{
    emit layoutChanged();
}

QList<FileItem *> FileSystemModel::getFileList(FileItem *parent)
{
    // Тут читаем содержимое папки
    //    QList<FileItem *> result;
    //    QString path = parent->getFilePath();
    //    QTextCodec *localeCodec = QTextCodec::codecForLocale();

    //    fs::path full_path(fs::initial_path<fs::path>());
    //    full_path = fs::system_complete(fs::path(localeCodec->fromUnicode(path).append('\0').data())); // Получаем полный путь к директории в представлении boost'a
    //    try // На случай запрета на чтение
    //    {
    //        if (fs::exists(full_path) && fs::is_directory(full_path)) // Проверяем на существование и действительно ли это директория, а то мало ли что
    //        {
    //            fs::directory_iterator end_iter;

    //            for (fs::directory_iterator dir_itr(full_path); dir_itr != end_iter; ++dir_itr)
    //            {
    //                FileItem *fileInfo = 0;
    //                try // На случай запрета на чтение
    //                {
    //                    fileInfo = new FileItem(localeCodec->toUnicode(dir_itr->path().string().c_str()),
    //                                            fs::is_directory(dir_itr->status()),
    //                                            parent,
    //                                            (!fs::is_directory(dir_itr->status())? fs::file_size(dir_itr->path()): 0),
    //                                            QDateTime::fromTime_t(last_write_time(dir_itr->path()))); // Создаем новый элемент дерева


    //                    result.append(fileInfo); // и добавляем его в результат
    //                }
    //                catch(const std::exception &ex)
    //                {
    //                    delete fileInfo; // Если что-то пошло не так надоб удалить
    //                }
    //            }
    //        }
    //    }
    //    catch (const std::exception &ex)
    //    {
    //    }
    QList<FileItem *> result;
    return result;
}

void FileSystemModel::readDir(FileItem *item)
{
    item->setChildList(getFileList(item)); // Получаем детей и сразу связывем их с предком

}

