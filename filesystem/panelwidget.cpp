#include "panelwidget.h"
#include "ui_panelwidget.h"

static const QString RO = "Режим: RO";
static const QString RW = "Режим: RW";
static const QString SELECTNONE = "Нет выбранных элементов";
static const int READDELAY = 10;

PanelWidget::PanelWidget(QWidget *parent) :
    QWidget(parent)
{
    ui = new Ui::PanelWidget;
    ui->setupUi(this);

    model = new FileSystemModel(this);
    model->setReadOnly(true);
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

    proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);

    FocusControlDelegate *delegate = new FocusControlDelegate(this);

    table = new TableView(this);
    table->setItemDelegate(delegate);
    table->setModel(proxy);
    table->setRootIndex(proxy->mapFromSource(model->setRootPath(QDir::currentPath()))); //очень важная строка, её надо понимать
    table->setFocusPolicy(Qt::StrongFocus);
    table->setColumnHidden(2, true);
    table->verticalHeader()->hide();
    table->setShowGrid(false);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setColumnWidth(0, (this->width() / 2) + 100);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);
    table->horizontalHeader()->setHighlightSections(false);
    table->setIconSize(QSize(32, 32));
    table->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->layoutTable->addWidget(table);

    currentPath = QDir::currentPath();
    emit currentItemChanged();
    ui->labelFileSystemInfo->setText(getFileSystemInfo(currentPath));
    ui->groupBoxDown->setTitle(SELECTNONE);

    connect(model, SIGNAL(directoryLoaded(QString)), this, SLOT(rowCounted(QString)));

    connect(table, &TableView::keyTab, this, &PanelWidget::switchPanel);
    connect(table, &TableView::keyEnter, this, &PanelWidget::changeDirToCurrentIndex);
    connect(table, &TableView::keySelect, this, &PanelWidget::selectCurrentItem);
    connect(table, &TableView::keyCtrlA, this, &PanelWidget::selectAll);
    connect(table, &TableView::keyLeft, this, &PanelWidget::scrollToTop);
    connect(table, &TableView::keyRight, this, &PanelWidget::scrollToBottom);
    connect(table, &TableView::doubleClicked, this, &PanelWidget::changeDir);
    connect(table->selectionModel(), &QItemSelectionModel::currentChanged, this, &PanelWidget::itemChanged);
}

PanelWidget::~PanelWidget()
{
    delete ui;
    delete model;
    delete proxy;
    delete table;
}

void PanelWidget::setFocus()
{
    table->setFocus();
    emit active(this);
}

void PanelWidget::openBox()
{
    ui->comboBox->showPopup();
}

void PanelWidget::rowCounted(QString item)
{
    rowCount = model->rowCount(model->index(item));
    emit modelFetched();
}

void PanelWidget::selectCurrentItem()
{
    QString path = model->fileInfo(proxy->mapToSource(table->currentIndex())).absoluteFilePath();
    QModelIndex index =  model->index(path);

    model->selectIndexToggle(index);
    table->selectRow(table->currentIndex().row() + 1);

    ui->groupBoxDown->setTitle(model->getSelection().size() > 0 ? "Выбрано " + QString::number(model->getSelection().size()) + " элементов" : SELECTNONE);
}

void PanelWidget::selectAll()
{
    QModelIndex index;
    QModelIndex item;
    QString path;

    int count = model->isRoot() ? 0 : 1;

    for (int i = rowCount; i >= count; i--)
    {
        item = proxy->index(i, 0, table->currentIndex().parent());
        path = model->fileInfo(proxy->mapToSource(item)).absoluteFilePath();
        index = model->index(path);
        if (path != QDir::currentPath())
        {
            model->selectIndex(index, Qt::Checked);
        }
    }
    ui->groupBoxDown->setTitle("Выделено " + QString::number(model->getSelection().size()) + " элементов");
}

void PanelWidget::changeDir(QModelIndex index)
{
    if (!index.isValid() || !model->fileInfo(proxy->mapToSource(index)).isDir())
    {
        return;
    }

    QString indexPath = model->fileInfo(proxy->mapToSource(index)).absoluteFilePath();

    if (!model->fileInfo(proxy->mapToSource(index)).isReadable())
    {
        emit readError(indexPath);
        return;
    }

    QString currentPathOld =  currentPath;

    QModelIndex root = model->setRootPath(indexPath);
    table->setRootIndex(proxy->mapFromSource(root));

    model->clearSelection(index);
    ui->groupBoxDown->setTitle(SELECTNONE);

    if (indexPath == entry.getMount())
    {
        model->setFilter(QDir::NoFilter);
        model->setIsRoot(true);
        model->setFilter(entry.getFilterRoot());
    }
    else
    {
        model->setFilter(QDir::NoFilter);
        model->setIsRoot(false);
        model->setFilter(entry.getFilterBase());
    }

    if(!indexPath.startsWith(currentPathOld))
    {
        delay(READDELAY);
        table->selectRow(proxy->mapFromSource(model->index(currentPathOld)).row());
    }
    else
    {
        delay(READDELAY);
        table->selectRow(0);
    }

    ui->panelBox->setTitle(indexPath);

    this->currentPath = indexPath;
    emit currentItemChanged();

    ui->labelFileSystemInfo->setText(getFileSystemInfo(entry.getMount()));
}

void PanelWidget::changeDirToCurrentIndex()
{
    changeDir(table->currentIndex());
}

void PanelWidget::scrollToBottom()
{
    table->selectRow(rowCount - 1);
    table->scrollToBottom();
}

void PanelWidget::scrollToTop()
{
    table->selectRow(0);
    table->scrollToTop();
}

void PanelWidget::itemChanged(QModelIndex current, QModelIndex previous)
{
    Q_UNUSED(previous)
    QString item = current.data(Qt::DisplayRole).toString();
    ui->labelCurrentItem->setText(item != ".." ? "./" + item : "ВВЕРХ");

    currentItem = model->fileInfo(proxy->mapToSource(table->currentIndex())).absoluteFilePath();
    emit currentItemChanged();
}

void PanelWidget::setConfigFile(const QString &value)
{
    configFile = value;
}

void PanelWidget::resetCurrentPosition()
{
    delay(10);
    table->clearSelection();
}

void PanelWidget::updateConfig(QString fileName)
{
    ConfigReader *configReader = new ConfigReader(fileName);
    entryList = configReader->getEntryList();

    for (int i = 0; i < entryList.size(); i++)
    {
        ui->comboBox->insertItem(i, entryList.at(i)->getName());

        if (entryList.at(i)->getType() == FileSystemEntry::fslocal)
            ui->comboBox->setItemIcon(i, QIcon(":/images/drive-harddisk.png"));

        if (entryList.at(i)->getType() == FileSystemEntry::fsremote)
            ui->comboBox->setItemIcon(i, QIcon(":/images/drive-remote.png"));
    }

    configReader->deleteLater();
}

void PanelWidget::updateConfig()
{
    updateConfig(configFile);
}

QString PanelWidget::getCurrentPath() const
{
    return currentPath;
}

QString PanelWidget::getCurrentItem() const
{
    return currentItem;
}

QStringList PanelWidget::getSelection() const
{
    QStringList list;
    int selectionSize = model->getSelection().size();

    for (int i = 0; i < selectionSize; i++)
    {
        int row = model->getSelection().toList().at(i).row();
        QModelIndex item = proxy->index(row, 0, table->currentIndex().parent());
        QFileInfo info = model->fileInfo(proxy->mapToSource(item));
        list.append(info.absoluteFilePath());
    }
    return list;
}

void PanelWidget::selectItemPath(QString path, Qt::CheckState state)
{
    QModelIndex index = model->index(path);
    model->selectIndex(index, state);
}

bool PanelWidget::isActive()
{
    return table->hasFocus();
}

void PanelWidget::delay(int msec)
{
    QTime dieTime= QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

QString PanelWidget::getFileSystemInfo(QString path)
{
    QProcess process;
    QString command;
    QStringList params;
    command = "df";
    params << "-PH" << path;
    process.start(command, params);
    process.waitForFinished();
    QString output(process.readAllStandardOutput());
    QStringList it1 = output.split("\n");
    QStringList it2 = QString(it1.at(1)).split(QRegExp("\\s+"));
    //for (int i = 0; i< it2.size(); i++)
    //{
    //    qDebug() << i << " " << it2.at(i);
    //}
    QString status = it2.at(2) + "/" + it2.at(1) + " (" + it2.at(4) + ")";

    return status;
}

void PanelWidget::on_comboBox_currentIndexChanged(int index)
{
    entry = *entryList.at(index);

    model->setIsRoot(true);
    model->setReadOnly(entry.isReadOnly());
    model->setFilter(QDir::NoFilter);
    model->setFilter(entry.getFilterRoot());

    table->setRootIndex(proxy->mapFromSource(model->setRootPath(entry.getMount())));

    currentPath = entry.getMount();
    emit currentItemChanged();

    ui->buttonMode->setText(model->isReadOnly() ? RO : RW);
    ui->panelBox->setTitle(entry.getMount());
    ui->labelFileSystemInfo->setText(getFileSystemInfo(entry.getMount()));

    delay(READDELAY);
    table->selectRow(0);
}

void PanelWidget::on_buttonRoot_clicked()
{
    table->setRootIndex(proxy->mapFromSource(model->setRootPath(entry.getMount())));

    currentPath = entry.getMount();
    emit currentItemChanged();

    model->setFilter(QDir::NoFilter);
    model->setIsRoot(true);
    model->setFilter(entry.getFilterRoot());

    ui->panelBox->setTitle(entry.getMount());

    delay(READDELAY);
    table->selectRow(0);
}

void PanelWidget::on_buttonMode_clicked()
{
    model->setReadOnly(!model->isReadOnly());
    ui->buttonMode->setText(model->isReadOnly() ? RO : RW);
}

void PanelWidget::switchPanel()
{
    table->clearSelection();
    emit focusLost();
}

FileSystemEntry PanelWidget::getEntry() const
{
    return entry;
}
