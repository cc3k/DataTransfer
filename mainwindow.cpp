#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    model1 = new FileExplorerModelWidget;
    model2 = new FileExplorerModelWidget;


    ui->layoutFileExplorer->addWidget(model1);
    ui->layoutFileExplorer->addWidget(model2);

    model1->show();
    model2->show();


}

MainWindow::~MainWindow()
{
    delete ui;
}
