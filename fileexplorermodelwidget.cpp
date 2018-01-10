#include "fileexplorermodelwidget.h"
#include "ui_fileexplorermodelwidget.h"

FileExplorerModelWidget::FileExplorerModelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileExplorerModelWidget)
{
    ui->setupUi(this);

    rootDir = "/home/projekt/";

    isReadOnly = true;

    dirModel = new QDirModel(this);
    dirModel->setReadOnly(isReadOnly);
    dirModel->setSorting(QDir::DirsFirst);
    dirModel->setFilter(QDir::AllEntries | QDir::NoDot);

    fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setReadOnly(isReadOnly);
    fileSystemModel->setRootPath(QDir::currentPath());
    fileSystemModel->setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

    proxyFileSystemModel = new QSortFilterProxyModel();
    proxyFileSystemModel->setSourceModel(fileSystemModel);

    ui->treeView->setModel(fileSystemModel);
    ui->treeView->setRootIndex(fileSystemModel->index(rootDir));

    ui->tableView->setModel(dirModel);
    ui->tableView->setRootIndex(dirModel->index(rootDir));
    ui->tableView->verticalHeader()->hide();

    updateModel();
}

FileExplorerModelWidget::~FileExplorerModelWidget()
{
    delete ui;
}

void FileExplorerModelWidget::setRoot(QString rootDir)
{
    this->rootDir = rootDir;
    updateModel();
}

void FileExplorerModelWidget::on_buttonDirMode_clicked()
{
    isReadOnly=!isReadOnly;
    updateModel();
}

void FileExplorerModelWidget::updateModel()
{
    updateDirMode();
    ui->groupBoxFileSystem->setTitle(rootDir);
    updateRootDir();
}

void FileExplorerModelWidget::updateRootDir()
{
    index = fileSystemModel->index(rootDir);
    ui->treeView->expand(index);
    ui->treeView->scrollTo(index);
    ui->treeView->setCurrentIndex(index);
    ui->treeView->resizeColumnToContents(0);

    index = dirModel->index(rootDir);
    ui->tableView->setRootIndex(index);
    ui->tableView->scrollTo(index);
    ui->tableView->setCurrentIndex(index);
    ui->tableView->resizeColumnToContents(0);
}

void FileExplorerModelWidget::updateDirMode()
{
    if (isReadOnly)
    {
        ui->buttonDirMode->setText("RO");
    }

    if (!isReadOnly)
    {
        ui->buttonDirMode->setText("RW");
    }

    fileSystemModel->setReadOnly(isReadOnly);
    qDebug() << "fileSystemModel->setReadOnly" << isReadOnly;

    dirModel->setReadOnly(isReadOnly);
    qDebug() << "dirModel->setReadOnly" << isReadOnly;
}

void FileExplorerModelWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    qDebug() << index;
    ui->tableView->setModel(dirModel);
    ui->tableView->setRootIndex(index);
    ui->tableView->scrollTo(index);
    ui->tableView->setCurrentIndex(index);

    //ui->tableView->scrollTo(index);
    //ui->tableView->setCurrentIndex(index);
    //ui->tableView->resizeColumnToContents(0);
}
