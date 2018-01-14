#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("ЮСИЯ.ХХХХХ-01 ФПО ВКС");
    setWindowState(Qt::WindowMaximized);

    emptyFileExplorerLeft = new QGroupBox;
    QVBoxLayout *vboxL = new QVBoxLayout;
    QLabel *labelL = new QLabel;
    QFont fontL;

    fontL.setPointSize(72);
    fontL.setBold(true);
    labelL->setFont(fontL);
    labelL->setText("ПУСТАЯ ФС");
    labelL->setAlignment(Qt::AlignCenter);
    labelL->setDisabled(true);
    vboxL->addWidget(labelL);
    emptyFileExplorerLeft->setTitle("Корень ФС");
    emptyFileExplorerLeft->setLayout(vboxL);
    emptyFileExplorerLeft->setFlat(true);

    emptyFileExplorerRight = new QGroupBox;
    QVBoxLayout *vboxR = new QVBoxLayout;
    QLabel *labelR = new QLabel;
    QFont fontR;

    fontR.setPointSize(72);
    fontR.setBold(true);
    labelR->setFont(fontR);
    labelR->setText("ПУСТАЯ ФС");
    labelR->setAlignment(Qt::AlignCenter);
    labelR->setDisabled(true);
    vboxR->addWidget(labelR);
    emptyFileExplorerRight->setTitle("Корень ФС");
    emptyFileExplorerRight->setLayout(vboxR);
    emptyFileExplorerRight->setFlat(true);



    //load config


    QFileInfoList drives = QDir::drives();

    foreach(QFileInfo drive, drives)
    {
        qDebug() << drive.absoluteFilePath();
        qDebug() << drive.absolutePath();
      }
    //

    modelLeft = new FileSystemWidget("/home");
    modelRight = new FileSystemWidget("/home/projekt");

    ui->layoutFileExplorer->addWidget(modelLeft,1,0);
    ui->layoutFileExplorer->addWidget(modelRight,1,1);

    modelRight->setFocus();

    modelLeft->setupWidget();
    modelRight->setupWidget();

    fileSystemList.append("Домашняя папка");        //0
    fileSystemList.append("Локальная ФС");          //1

    ui->comboBoxExplorerLeft->addItems(fileSystemList);
    ui->comboBoxExplorerRight->addItems(fileSystemList);

    QShortcut *shortcut = new QShortcut(QKeySequence (Qt::Key_F2), this);
    QObject::connect(shortcut, SIGNAL(activated()), ui->buttonQueue, SLOT(click()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonQueue_clicked()
{
    qDebug() << "queue clicked";
}

void MainWindow::on_comboBoxExplorerLeft_currentIndexChanged(int index)
{

}

void MainWindow::on_comboBoxExplorerRight_currentIndexChanged(int index)
{

}
