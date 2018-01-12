#include "fileexplorermodelwidget.h"
#include "ui_fileexplorermodelwidget.h"

FileExplorerModelWidget::FileExplorerModelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileExplorerModelWidget)
{
    ui->setupUi(this);

    rootDir = "/home/projekt";

    isReadOnly = true;

    dirModel = new QDirModel(this);
    dirModel->setReadOnly(isReadOnly);
    dirModel->setResolveSymlinks(false);
    dirModel->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
    dirModel->setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

    tableView = new CustomTableView;
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(tableView_doubleClicked(QModelIndex)));
    connect(tableView,SIGNAL(clicked(QModelIndex)), this, SLOT(tableView_clicked(QModelIndex)));
    connect(tableView, SIGNAL(keyEnter()), this, SLOT(enter_pressed()));
    connect(tableView, SIGNAL(keyLeft()), this, SLOT(dirUp()));



    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(tableView);
    ui->groupBoxFileSystem->setLayout(vbox);

    tableView->setModel(dirModel);
    tableView->verticalHeader()->hide();
    tableView->setShowGrid(false);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setColumnWidth(0, this->width()/2);
    tableView->setSelectionMode(QAbstractItemView::NoSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    tableView->setAlternatingRowColors(true);
    tableView->setSortingEnabled(true);
    tableView->sortByColumn(0, Qt::AscendingOrder);
    tableView->horizontalHeader()->setHighlightSections(false);

    watcher = new QFileSystemWatcher;
    watcher->addPath(rootDir);
    connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(dirUpdate(QString)));

    updateModel();
    updateRootDir();

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

void FileExplorerModelWidget::setFocus()
{
    tableView->setFocus();
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
}

void FileExplorerModelWidget::updateRootDir()
{
    qDebug() << "updateRootDir()";
    index = dirModel->index(rootDir);
    tableView->setRootIndex(index);
    dirModel->setFilter(QDir::Dirs| QDir::Files | QDir::NoDotAndDotDot);
    tableView->setCurrentIndex(tableView->indexAt(QPoint(0,0)));
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

void FileExplorerModelWidget::dirUpdate(const QString &string)
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

void FileExplorerModelWidget::dirChange(QModelIndex index)
{
    if (!index.isValid() || index.column() !=0)
    {
        return;
    }

    tableView->clearSelection();

    ui->groupBoxFileSystem->setTitle(dirModel->filePath(tableView->currentIndex()));

    if (dirModel->filePath(tableView->currentIndex()) == rootDir)
    {
        dirModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    }
    else
    {
        dirModel->setFilter(QDir::AllEntries | QDir::NoDot);
    }

    watcher->removePath(dirModel->filePath(tableView->rootIndex()));

    tableView->setRootIndex(tableView->currentIndex());

    tableView->selectionModel()->setCurrentIndex(tableView->indexAt(QPoint(0,0)), QItemSelectionModel::NoUpdate);

    watcher->addPath(dirModel->filePath(tableView->rootIndex()));
}

void FileExplorerModelWidget::dirUp()
{
    tableView->selectionModel()->setCurrentIndex(tableView->indexAt(QPoint(0,0)), QItemSelectionModel::NoUpdate);

    if (dirModel->fileName(tableView->currentIndex()) == "..")
    {
        dirChange(tableView->currentIndex());
    }
}

void FileExplorerModelWidget::tableView_doubleClicked(const QModelIndex &index)
{
    dirChange(index);
}

void FileExplorerModelWidget::tableView_clicked(const QModelIndex &index)
{
    tableView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
}

void FileExplorerModelWidget::on_buttonRoot_clicked()
{
    updateRootDir();
}

void FileExplorerModelWidget::enter_pressed()
{
    dirChange(tableView->currentIndex());
}


