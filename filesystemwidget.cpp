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
        QMessageBox mBox(QMessageBox::Warning
                         ,"Ошибка!"
                         , "Отказано в установке корня для " + name + "://" + path
                         + "\nРесурс: " + path + " Отказано в доступе."
                         + "\nПринудительный сброс корня на домашний каталог"
                         , QMessageBox::Yes);
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
        QMessageBox mBox(QMessageBox::Warning
                         ,"Ошибка!"
                         , "Ресурс: " + path + " Отказано в доступе."
                         , QMessageBox::Yes);
        mBox.setModal(true);
        mBox.setWindowFlags((mBox.windowFlags() | Qt::WindowStaysOnTopHint));
        mBox.exec();
        return;
    }

    tableView->clearSelection();

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
    tableView->selectRow(0);

    watcher->addPath(dirModel->filePath(tableView->rootIndex()));
}

void FileSystemWidget::dirUp()
{
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
    dirModel->setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

    dirModel->setLazyChildCount(true); //Не проверяет есть ли у директории потомки, для таблицы не важно (хотя если считать размеры...)

    tableView->setModel(dirModel);
    tableView->setColumnHidden(2, true);
    tableView->verticalHeader()->hide();
    tableView->setShowGrid(false);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setColumnWidth(0, this->width()/2);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
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
        dirChange(index);
    }
}

void FileSystemWidget::tableView_clicked(const QModelIndex &index)
{
    //    tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    //    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    tableView->selectRow(tableView->currentIndex().row());
    //    tableView->setSelectionMode(QAbstractItemView::NoSelection);
    //    tableView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
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


