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
    dirModel->setSorting(QDir::DirsFirst);
    dirModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

    tableView = new CustomTableView;
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_tableView_doubleClicked(QModelIndex)));
    connect(tableView, SIGNAL(keyEnter()), this, SLOT(on_enter_pressed()));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(tableView);
    ui->groupBoxFileSystem->setLayout(vbox);

    tableView->setModel(dirModel);
    tableView->setRootIndex(dirModel->index(rootDir));
    tableView->verticalHeader()->hide();
    tableView->setShowGrid(false);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setColumnWidth(0, this->width()/2);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    tableView->setAlternatingRowColors(true);
    tableView->setSortingEnabled(true);
    tableView->sortByColumn(0, Qt::AscendingOrder);
    tableView->horizontalHeader()->setHighlightSections(false);

    watcher = new QFileSystemWatcher;
    watcher->addPath(rootDir);
    connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(updateCurrentDir(QString)));

    updateModel();
    updateRootDir();

    //QShortcut *shortcutEnter = new QShortcut(QKeySequence("ENTER"), ui->tableView);
    //connect(shortcutEnter, SIGNAL(activated()), this, SLOT(on_enter_pressed()));
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
}

void FileExplorerModelWidget::updateRootDir()
{
    index = dirModel->index(rootDir);
    tableView->setRootIndex(index);
    dirModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
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

void FileExplorerModelWidget::updateCurrentDir(const QString &string)
{
    dirModel->refresh(dirModel->index(string));
}

void FileExplorerModelWidget::on_tableView_doubleClicked(const QModelIndex &index)
{

    if (dirModel->filePath(index) == rootDir)
    {
        dirModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    }
    else
    {
        dirModel->setFilter(QDir::AllEntries | QDir::NoDot);
    }

    tableView->setRootIndex(index);
}

void FileExplorerModelWidget::on_buttonRoot_clicked()
{
    updateRootDir();
}

void FileExplorerModelWidget::on_enter_pressed()
{
    qDebug() << "enter";

    if (dirModel->filePath(tableView->currentIndex()) == rootDir)
    {
        dirModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    }
    else
    {
        dirModel->setFilter(QDir::AllEntries | QDir::NoDot);
    }

    tableView->setRootIndex(tableView->currentIndex());
}

