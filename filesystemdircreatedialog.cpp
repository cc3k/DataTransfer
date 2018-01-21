#include "filesystemdircreatedialog.h"
#include "ui_filesystemdircreatedialog.h"

FileSystemDirCreateDialog::FileSystemDirCreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileSystemDirCreateDialog)
{
    ui->setupUi(this);

    setModal(true);
    setWindowTitle("Файловая система");
}

FileSystemDirCreateDialog::~FileSystemDirCreateDialog()
{
    delete ui;
}

QString FileSystemDirCreateDialog::getString() const
{
    return ui->lineEditDirName->text();
}

void FileSystemDirCreateDialog::on_buttonBox_accepted()
{

}

void FileSystemDirCreateDialog::on_buttonBox_rejected()
{

}
