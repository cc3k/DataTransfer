#ifndef FILESYSTEMDIRREADDIALOG_H
#define FILESYSTEMDIRREADDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QDialogButtonBox>

namespace Ui {
class FileSystemDirReadDialog;
}

class FileSystemDirReadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileSystemDirReadDialog(QWidget *parent = 0);
    ~FileSystemDirReadDialog();
    void setPath(QString path);

public slots:
    void updateTextFields(int itemCount, int dirCount, int fileCount, double size);
    void closeDialog();

private slots:
    void on_buttonBox_rejected();

signals:
    void canceled();

private:
    Ui::FileSystemDirReadDialog *ui;
};

#endif // FILESYSTEMDIREADDIALOG_H
