#ifndef FILESYSTEMDIRCREATEDIALOG_H
#define FILESYSTEMDIRCREATEDIALOG_H

#include <QDialog>

namespace Ui {
class FileSystemDirCreateDialog;
}

class FileSystemDirCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileSystemDirCreateDialog(QWidget *parent = 0);
    ~FileSystemDirCreateDialog();

    QString getString() const;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::FileSystemDirCreateDialog *ui;
};

#endif // FILESYSTEMDIRCREATEDIALOG_H
