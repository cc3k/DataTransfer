#ifndef PANELWIDGET_H
#define PANELWIDGET_H

#include <QWidget>
#include <QProcess>
#include <QRegExp>
#include <QShortcut>
#include <QCoreApplication>
#include <QTime>
#include <QEventLoop>
#include <QDir>
#include <QMenu>
#include <QSortFilterProxyModel>

#include <QDebug>

#include "tableview.h"
#include "filesystemmodel.h"
#include "filesystementry.h"
#include "configreader.h"
#include "focuscontroldelegate.h"

namespace Ui
{
class PanelWidget;
}

class PanelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PanelWidget(QWidget *parent = 0);
    ~PanelWidget();

    void updateConfig(QString fileName);
    void updateConfig();

    //для работы с выделеными элементами
    QString getCurrentPath() const;
    QString getCurrentItem() const;
    QStringList getSelection() const;
    void selectItemPath(QString path, Qt::CheckState state);

    void setConfigFile(const QString &value);

    //это для красоты, чтобы убрать выделение со строки
    void resetCurrentPosition();

    FileSystemEntry getEntry() const;

public slots:
    void setFocus();
    void openBox();

private slots:
    void rowCounted(QString item);

    //selecttions
    void selectCurrentItem();
    void selectAll();

    //table operation
    void changeDir(QModelIndex index);
    void changeDirToCurrentIndex();
    void scrollToBottom();
    void scrollToTop();

    void itemChanged(QModelIndex current, QModelIndex previous);

    void on_comboBox_currentIndexChanged(int index);
    void on_buttonRoot_clicked();
    void on_buttonMode_clicked();
    void switchPanel();

signals:
    void focusLost();
    void modelFetched(); //когда полностью текущий каталог загружен
    void currentItemChanged();
    void active(PanelWidget *panel);
    void readError(QString path);

private:
    Ui::PanelWidget *ui;

    //var
    TableView *table;
    FileSystemModel *model;
    QSortFilterProxyModel *proxy;

    QString configFile;
    QList<FileSystemEntry*> entryList;
    FileSystemEntry entry;

    QString currentPath;
    QString currentItem;

    int rowCount;

    //func
    bool isActive();
    void delay(int msec);
    QString getFileSystemInfo(QString path);

};
#endif // PANELWIDGET_H
