#ifndef FILEPARSEPATHDIALOG_H
#define FILEPARSEPATHDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QDialogButtonBox>

namespace Ui {
class FileParsePathDialog;
}

class FileParsePathDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileParsePathDialog(QWidget *parent = 0);
    ~FileParsePathDialog();
    void setPath(QString path);

public slots:
    void updateTextFields(int itemCount, int dirCount, int fileCount, double size);
    void closeDialog();

private slots:
    void on_buttonBox_rejected();

signals:
    void canceled();

private:
    Ui::FileParsePathDialog *ui;
};

#endif // FILEPARSEPATHDIALOG_H
