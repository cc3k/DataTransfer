#include "filesystemwidget.h"
#include "ui_filesystemwidget.h"

FileSystemWidget::FileSystemWidget(QString name, QString root, bool isReadOnly, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileSystemWidget)
{
    ui->setupUi(this);

    this->name = name;
    this->root = root;
    this->isReadOnly = isReadOnly;
    parentRow = 0;

    tableView = new CustomTableView;
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(tableView_doubleClicked(QModelIndex)));
    connect(tableView,SIGNAL(clicked(QModelIndex)), this, SLOT(tableView_clicked(QModelIndex)));
    connect(tableView, SIGNAL(keyEnter()), this, SLOT(enter_pressed()));
    connect(tableView, SIGNAL(keyLeft()), this, SLOT(dirUp()));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setContentsMargins(0,12,0,0);
    ui->groupBoxFileSystem->setContentsMargins(0,0,0,0);
    vbox->addWidget(tableView);
    ui->groupBoxFileSystem->setLayout(vbox);

    //    QProcess process;
    //    process.startDetached("/bin/sh", QStringList()<< "-c" << "sudo -S");

}

FileSystemWidget::~FileSystemWidget()
{
    delete ui;
}

void FileSystemWidget::setFocus()
{
    tableView->setFocus();
}

void FileSystemWidget::on_buttonDirMode_clicked()
{
    isReadOnly=!isReadOnly;
    updateModel();
}

void FileSystemWidget::updateModel()
{
    updateDirMode();
    ui->groupBoxFileSystem->setTitle(root);
}

void FileSystemWidget::updateRootDir()
{
    if (!dirModel->fileInfo(dirModel->index(root)).isReadable())
    {
        QString path = dirModel->fileName(dirModel->index(root));
        QMessageBox mBox(QMessageBox::NoIcon
                         ,"Ошибка!"
                         , "Отказано в установке корня для " + name + "://" + path
                         + "\nРесурс: " + path + " Отказано в доступе."
                         + "\nПринудительный сброс корня на домашний каталог"
                         , QMessageBox::Yes);
        mBox.setWindowIcon(QIcon(":/images/dialog-warning.png"));
        mBox.setModal(true);
        mBox.setWindowFlags((mBox.windowFlags() | Qt::WindowStaysOnTopHint));
        root = QDir::homePath();
        mBox.exec();
    }

    index = dirModel->index(root);

    tableView->setRootIndex(index);

    dirModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

    //tableView->setCurrentIndex(tableView->indexAt(QPoint(0,0)));
    tableView->selectRow(0);
    ui->groupBoxFileSystem->setTitle(root);
}

void FileSystemWidget::updateDirMode()
{
    if (isReadOnly)
    {
        ui->buttonDirMode->setText("RO");
    }

    if (!isReadOnly)
    {
        ui->buttonDirMode->setText("RW");
    }

    dirModel->setReadOnly(isReadOnly);
}

void FileSystemWidget::dirUpdate(const QString &string)
{
    if (dirModel->index(string).isValid())
    {
        dirModel->refresh(dirModel->index(string));
    }
    else
    {
        updateRootDir();
    }
}

void FileSystemWidget::dirChange(QModelIndex index)
{
    if (!index.isValid() || index.column() != 0 )
    {
        return;
    }

    if (!dirModel->fileInfo(tableView->currentIndex()).isReadable())
    {
        QString path = dirModel->fileName(tableView->currentIndex());
        QMessageBox mBox(QMessageBox::NoIcon
                         ,"Ошибка!"
                         , "Ресурс: " + path + " Отказано в доступе."
                         , QMessageBox::Yes);
        mBox.setWindowIcon(QIcon(":/images/dialog-warning.png"));
        mBox.setModal(true);
        mBox.setWindowFlags((mBox.windowFlags() | Qt::WindowStaysOnTopHint));
        mBox.exec();
        return;
    }

    //Когда выходишь на уровень вверх не ставить курсор на верхний элемент, а на
    //тот с которого входили в директорию (на предка)
    parentIndex = tableView->currentIndex();
    parentRow = tableView->currentIndex().parent().row();

    //это задумка пока не работает

    //tableView->clearSelection(); //беp него тоже неплохо

    ui->groupBoxFileSystem->setTitle(dirModel->filePath(tableView->currentIndex()));

    if (dirModel->filePath(tableView->currentIndex()) == root)
    {
        dirModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    }
    else
    {
        dirModel->setFilter(QDir::AllEntries | QDir::NoDot);
    }

    watcher->removePath(dirModel->filePath(tableView->rootIndex()));

    //qDebug() << dirModel->filePath(tableView->currentIndex());
    //qDebug() << "is accessable" << dirModel->fileInfo(tableView->currentIndex()).isReadable();

    tableView->setRootIndex(tableView->currentIndex());

    //это выбор элемента
    //tableView->selectionModel()->setCurrentIndex(tableView->indexAt(QPoint(0,0)), QItemSelectionModel::NoUpdate);

    //это выбор ряда
    if (tableView->rootIndex() == parentIndex)
    {
        tableView->selectRow(parentRow);
    }
    else
    {
    tableView->selectRow(0);
    }

    watcher->addPath(dirModel->filePath(tableView->rootIndex()));
}

void FileSystemWidget::dirUp()
{
    qDebug() << tableView->rootIndex().parent().data(Qt::DisplayRole);

    //tableView->selectionModel()->setCurrentIndex(tableView->indexAt(QPoint(0,0)), QItemSelectionModel::NoUpdate);
    tableView->selectRow(0);


    if (dirModel->fileName(tableView->currentIndex()) == "..")
    {
        dirChange(tableView->currentIndex());
    }
}

void FileSystemWidget::setupWidget()
{
    dirModel = new CustomDirModel(this);
    dirModel->setReadOnly(isReadOnly);
    dirModel->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
    dirModel->setFilter(QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot);

    //for testing
    model_ = new QFileSystemModel;
    model_->setReadOnly(isReadOnly);
    model_->setRootPath("/home/projekt");
    model_->setFilter(QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot);

    dirModel->setLazyChildCount(true); //Не проверяет есть ли у директории потомки, для таблицы не важно (хотя если считать размеры...)

    tableView->setModel(dirModel);
    tableView->setColumnHidden(2, true);
    tableView->verticalHeader()->hide();
    tableView->setShowGrid(false);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setColumnWidth(0, this->width()/2);
    tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    tableView->setAlternatingRowColors(true);
    tableView->setSortingEnabled(true);
    tableView->sortByColumn(0, Qt::AscendingOrder);
    tableView->horizontalHeader()->setHighlightSections(false);

    //    можно разом менять шрифт на таблицу
    //    QFont font;
    //    font.setWeight(QFont::Bold);
    //    font.setPointSize(10);
    //    tableView->setFont(font);

    watcher = new QFileSystemWatcher;
    connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(dirUpdate(QString)));

    //tableView->setRootIndex(model_->index(root));
    updateModel();
    updateRootDir();

    if (dirModel->filePath(tableView->currentIndex().parent()) != root)
    {
        qDebug() << "error open " << root;
    }
}

void FileSystemWidget::tableView_doubleClicked(const QModelIndex &index)
{
    if (dirModel->fileInfo(index).isDir())
    {
        tableView->selectRow(tableView->currentIndex().row());
        dirChange(index);
    }

}

void FileSystemWidget::tableView_clicked(const QModelIndex &index)
{
    if (index.isValid())
    {
        tableView->selectRow(index.row());
    }
}

void FileSystemWidget::on_buttonRoot_clicked()
{
    updateRootDir();
}

void FileSystemWidget::enter_pressed()
{
    if (dirModel->fileInfo(tableView->currentIndex()).isDir())
    {
        dirChange(tableView->currentIndex());
    }
}

void FileSystemWidget::setFileSystemRW(bool mode)
{

}

void FileSystemWidget::setShowHidden(bool mode)
{

}
