#ifndef FILEEXPLORERMODELWIDGET_H
#define FILEEXPLORERMODELWIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QDirModel>
#include <QFileSystemModel>

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

private:
    Ui::FileExplorerModelWidget *ui;

    QDirModel *dirModel;
    QFileSystemModel *fileSystemModel;
    QSortFilterProxyModel *proxyFileSystemModel;
    QModelIndex index;

    QString rootDir;
    QString header;
    bool isReadOnly;

    void updateModel();

    void updateRootDir();
    void updateDirMode();

};

#endif // FILEEXPLORERMODELWIDGET_H
