#include "filesystemdeletedialog.h"
#include "ui_filesystemdeletedialog.h"

FileSystemDeleteDialog::FileSystemDeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileSystemDeleteDialog)
{
    ui->setupUi(this);

    setModal(true);
    setWindowTitle("Удаление");
}

FileSystemDeleteDialog::~FileSystemDeleteDialog()
{
    delete ui;
}

void FileSystemDeleteDialog::setText(QString text) const
{
    ui->listWidget->addItem(text);
}

void FileSystemDeleteDialog::clearText()
{
    ui->listWidget->clear();
}
