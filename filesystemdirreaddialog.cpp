#include "filesystemdirreaddialog.h"
#include "ui_filesystemdirreaddialog.h"

FileSystemDirReadDialog::FileSystemDirReadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileSystemDirReadDialog)
{
    ui->setupUi(this);
    setModal(true);
    setWindowTitle("Обработка путей элементов");
    //setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowTitleHint| Qt::WindowStaysOnTopHint);
    //setWindowIcon(QIcon(":/images/drive-harddisk.png"));
}

FileSystemDirReadDialog::~FileSystemDirReadDialog()
{
    delete ui;
}

void FileSystemDirReadDialog::setPath(QString path)
{
    ui->lineEditPath->setText(path);
}

void FileSystemDirReadDialog::updateTextFields(int itemCount, int dirCount, int fileCount, double size)
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

void FileSystemDirReadDialog::closeDialog()
{
    this->close();
}

void FileSystemDirReadDialog::on_buttonBox_rejected()
{
    qDebug() << "rejected_pressed";
    emit canceled();
    this->close();
    deleteLater();
}
