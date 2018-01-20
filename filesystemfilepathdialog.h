#ifndef FILESYSTEMFILEPATHDIALOG_H
#define FILESYSTEMFILEPATHDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QDialogButtonBox>

namespace Ui {
class FileSystemFilePathDialog;
}

class FileSystemFilePathDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileSystemFilePathDialog(QWidget *parent = 0);
    ~FileSystemFilePathDialog();
    void setPath(QString path);

public slots:
    void updateTextFields(int itemCount, int dirCount, int fileCount, double size);
    void closeDialog();

private slots:
    void on_buttonBox_rejected();

signals:
    void canceled();

private:
    Ui::FileSystemFilePathDialog *ui;
};

#endif // FILESYSTEMFILEPATHDIALOG_H
