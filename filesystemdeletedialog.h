#ifndef FILESYSTEMDELETEDIALOG_H
#define FILESYSTEMDELETEDIALOG_H

#include <QDialog>

namespace Ui {
class FileSystemDeleteDialog;
}

class FileSystemDeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileSystemDeleteDialog(QWidget *parent = 0);
    ~FileSystemDeleteDialog();

    void setText(QString text) const;
    void clearText();

private:
    Ui::FileSystemDeleteDialog *ui;
};

#endif // FILESYSTEMDELETEDIALOG_H
