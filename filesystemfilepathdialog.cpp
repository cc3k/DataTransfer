#include "filesystemfilepathdialog.h"
#include "ui_filesystemfilepathdialog.h"

FileSystemFilePathDialog::FileSystemFilePathDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileSystemFilePathDialog)
{
    ui->setupUi(this);
    setWindowTitle("Обработка путей элементов");
    setWindowIcon(QIcon(":/images/drive-harddisk.png"));
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

FileSystemFilePathDialog::~FileSystemFilePathDialog()
{
    delete ui;
}

void FileSystemFilePathDialog::setPath(QString path)
{
    ui->lineEditPath->setText(path);
}

void FileSystemFilePathDialog::updateTextFields(int itemCount, int dirCount, int fileCount, double size)
{
    QString humanSize;

    if (size > (1024*1024))
    {
        humanSize = QString::number(size / (1024 * 1024)) + " MBytes";
    }
    else
    {
        humanSize = QString::number(size) + " bytes";
    }

    ui->lineEditItemCount->setText(QString::number(itemCount));
    ui->lineEditDirCount->setText(QString::number(dirCount));
    ui->lineEditFileCount->setText(QString::number(fileCount));
    ui->lineEditSize->setText(humanSize);
}

void FileSystemFilePathDialog::closeDialog()
{
    this->close();
}

void FileSystemFilePathDialog::on_buttonBox_rejected()
{
    emit canceled();
    this->close();
    deleteLater();
}
