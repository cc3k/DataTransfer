#include "fileparsepathdialog.h"
#include "ui_fileparsepathdialog.h"

FileParsePathDialog::FileParsePathDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileParsePathDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

FileParsePathDialog::~FileParsePathDialog()
{
    delete ui;
}

void FileParsePathDialog::setPath(QString path)
{
    ui->lineEditPath->setText(path);
}

void FileParsePathDialog::updateTextFields(int itemCount, int dirCount, int fileCount, double size)
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

void FileParsePathDialog::closeDialog()
{
    this->close();
}

void FileParsePathDialog::on_buttonBox_rejected()
{
    emit canceled();
    this->close();
    deleteLater();
}
