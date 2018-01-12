#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("ЮСИЯ.ХХХХХ-01 ФПО ВКС");
    setWindowState(Qt::WindowMaximized);

    emptyFileExplorer = new QGroupBox;
    QVBoxLayout *vbox = new QVBoxLayout;
    QLabel *label = new QLabel;
    QFont font;

    font.setPointSize(72);
    font.setBold(true);
    label->setFont(font);
    label->setText("ПУСТАЯ ФС");
    label->setAlignment(Qt::AlignCenter);
    label->setDisabled(true);
    vbox->addWidget(label);
    emptyFileExplorer->setTitle("Корень ФС");
    emptyFileExplorer->setLayout(vbox);
    emptyFileExplorer->setFlat(true);

    modelLeft = new FileExplorerModelWidget;
    modelRight = new FileExplorerModelWidget;

    ui->layoutFileExplorer->addWidget(modelLeft,1,0);
    ui->layoutFileExplorer->addWidget(modelRight,1,1);


    modelRight->setFocus();

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
