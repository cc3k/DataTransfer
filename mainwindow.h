#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QShortcut>
#include <QGroupBox>
#include "fileexplorermodelwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonQueue_clicked();
    void on_comboBoxExplorerLeft_currentIndexChanged(int index);
    void on_comboBoxExplorerRight_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    FileExplorerModelWidget *modelLeft;
    FileExplorerModelWidget *modelRight;
    QGroupBox *emptyFileExplorer;

    QList<FileExplorerModelWidget*> fileExplorerList;
};

#endif // MAINWINDOW_H
