#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sessionId = generateSessionId();

    setWindowTitle("ФПО ВКС. Идентификатор сессии:[" + sessionId + "]");
    setWindowState(Qt::WindowMaximized);
    setWindowModality(Qt::ApplicationModal); //чтобы не переходил фокус при поп-апах
    setWindowIcon(QIcon(":/images/transfer.png"));

    //load config
    configXmlReader = new ConfigXmlReader(":/config_tst/stations.xml");
    fileSystemEntryList = configXmlReader->getFileSystemEntryList();

    //qDebug() << QFileInfo("/home/projekt/Workspace").canonicalPath();
    //qDebug() << QDir::homePath();

    //

    modelLeft = new FileSystemWidget("ФС1", "/mount.storage/cc3k_192.168.56.102");
    modelRight = new FileSystemWidget("ФС2","/mount.storage/projekt_192.168.56.102");

    //rsa ключи забрать к себе

    ui->layoutFileExplorer->addWidget(modelLeft,1,0);
    ui->layoutFileExplorer->addWidget(modelRight,1,1);

    modelRight->setFocus();

    modelLeft->setupWidget();
    modelRight->setupWidget();

    fileSystemList.append("Домашняя папка");        //0
    fileSystemList.append("Локальная ФС");          //1

    ui->comboBoxExplorerLeft->addItems(fileSystemList);
    ui->comboBoxExplorerRight->addItems(fileSystemList);

    QShortcut *shortcutF2 = new QShortcut(QKeySequence (Qt::Key_F2), this);
    QObject::connect(shortcutF2, SIGNAL(activated()), ui->buttonQueue, SLOT(click()));

    QShortcut *shortcutF11 = new QShortcut(QKeySequence (Qt::Key_F11), this);
    QObject::connect(shortcutF11, SIGNAL(activated()), ui->buttonSession, SLOT(click()));
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

QString MainWindow::getRandomString(const int length) const
{
    const QString chars("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

    QString randomString;
    for(int i=0; i<length; ++i)
    {
        int index = qrand() % chars.length();
        QChar nextChar = chars.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}

QString MainWindow::generateSessionId() const
{
    QString sessionId = QDateTime::currentDateTime().toString("yyMMdd_HHmmss_") + getRandomString(4);
    return sessionId;
}

void MainWindow::on_buttonSession_clicked()
{
    QMessageBox mBox(QMessageBox::NoIcon
                     ,"Сессия"
                     , "Текущий идентификатор: " + sessionId + "\nСгенерировать новый?."
                     , QMessageBox::Yes | QMessageBox::No);
    mBox.setWindowIcon(QIcon(":/images/dialog-question.png"));
    mBox.setModal(true);
    mBox.setWindowFlags((mBox.windowFlags() | Qt::WindowStaysOnTopHint));
    int ret = mBox.exec();

    if (ret == QMessageBox::Yes)
    {
        sessionId = generateSessionId();
        setWindowTitle("ФПО ВКС. Идентификатор сессии:[" + sessionId + "]");
    }
}
