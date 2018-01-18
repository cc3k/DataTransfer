#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QDirModel>
#include <QFileSystemWatcher>
#include <QMessageBox>
#include <QDebug>

#include "customtableview.h"
#include "customdirmodel.h"


namespace Ui {
class FileSystemWidget;
}

class FileSystemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileSystemWidget(QString name, QString root, bool isReadOnly = true, QWidget *parent = 0);
    ~FileSystemWidget();

   void setupWidget();

public slots:
    void setFocus();
    void setFileSystemRW(bool mode);
    void setShowHidden(bool mode);

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
    Ui::FileSystemWidget *ui;

    CustomDirModel *dirModel;
    QFileSystemWatcher *watcher;
    QModelIndex index;
    CustomTableView *tableView;
    int parentRow;
    QModelIndex parentIndex;

    QString root;
    QString header;
    bool isReadOnly;

    int dirCount;
    int fileCount;

    QString name;

    void updateModel();

    void updateRootDir();
    void updateDirMode();

signals:
    void error();
};

#endif // FILESYSTEMWIDGET_H
