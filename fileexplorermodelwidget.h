#ifndef FILEEXPLORERMODELWIDGET_H
#define FILEEXPLORERMODELWIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QDirModel>
#include <QFileSystemWatcher>

#include "customtableview.h"

#include <QTableView>

#include <QDebug>


namespace Ui {
class FileExplorerModelWidget;
}

class FileExplorerModelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileExplorerModelWidget(QWidget *parent = 0);
    ~FileExplorerModelWidget();

    void setRoot(QString rootDir);
    const QString getRootDir();

public slots:
    void setFocus();

private slots:
    void on_buttonDirMode_clicked();
    void on_buttonRoot_clicked();
    void enter_pressed();
    void tableView_doubleClicked(const QModelIndex &index);
    void tableView_clicked(const QModelIndex &index);
    void dirUpdate(const QString &string);
    void dirChange(QModelIndex index);
    void dirUp();

private:
    Ui::FileExplorerModelWidget *ui;

    QDirModel *dirModel;
    QFileSystemWatcher *watcher;
    QModelIndex index;
    CustomTableView *tableView;

    QString rootDir;
    QString header;
    bool isReadOnly;

    int dirCount;
    int fileCount;

    void updateModel();

    void updateRootDir();
    void updateDirMode();
};

#endif // FILEEXPLORERMODELWIDGET_H
