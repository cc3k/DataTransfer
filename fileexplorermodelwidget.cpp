#include "fileexplorermodelwidget.h"
#include "ui_fileexplorermodelwidget.h"

FileExplorerModelWidget::FileExplorerModelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileExplorerModelWidget)
{
    ui->setupUi(this);

    rootDir = "/home/projekt/Workspace";

    isReadOnly = false;

    dirModel = new QDirModel(this);
    dirModel->setReadOnly(isReadOnly);
    dirModel->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);


    fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(QDir::currentPath());
    fileSystemModel->setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    fileSystemModel->setReadOnly(isReadOnly);

    ui->treeView->setModel(fileSystemModel);
    ui->treeView->setRootIndex(fileSystemModel->index(rootDir));

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

void FileExplorerModelWidget::on_buttonDirRoot_clicked()
{
    updateModel();
}

void FileExplorerModelWidget::on_buttonDirUp_clicked()
{

}

void FileExplorerModelWidget::on_buttonDirMode_clicked()
{
    isReadOnly=!isReadOnly;
    updateModel();
}

void FileExplorerModelWidget::updateModel()
{
    updateDirMode();
    updateRootDir();
    ui->groupBoxFileSystem->setTitle(rootDir);
}

void FileExplorerModelWidget::updateRootDir()
{
    index = fileSystemModel->index(rootDir);
    ui->treeView->expand(index);
    ui->treeView->scrollTo(index);
    ui->treeView->setCurrentIndex(index);
    ui->treeView->resizeColumnToContents(0);
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
    dirModel->setReadOnly(isReadOnly);
}
