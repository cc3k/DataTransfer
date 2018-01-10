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


private slots:
    void on_buttonDirMode_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_buttonRoot_clicked();
    void on_enter_pressed();

private:
    Ui::FileExplorerModelWidget *ui;

    QDirModel *dirModel;
    QFileSystemWatcher *watcher;
    QModelIndex index;
    //QTableView *tableView;

    CustomTableView *tableView;

    QString rootDir;
    QString header;
    bool isReadOnly;

    void updateModel();

    void updateRootDir();
    void updateDirMode();

private slots:
    void updateCurrentDir(const QString &string);

};

#endif // FILEEXPLORERMODELWIDGET_H
