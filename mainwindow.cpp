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
    ConfigXmlReader *configXmlReader = new ConfigXmlReader(":/config_tst/stations.xml");
    fileSystemEntryList = configXmlReader->getFileSystemEntryList();
    configXmlReader->deleteLater();

    model1 = new FileSystemWidget("ФС1", "/home/projekt", false);
    model2 = new FileSystemWidget("ФС2", "/home/projekt", false);

    connect(model1, SIGNAL(looseFocus()), model2, SLOT(setFocus()));
    connect(model2, SIGNAL(looseFocus()), model1, SLOT(setFocus()));
    //rsa ключи забрать к себе

    ui->layoutFileExplorer->addWidget(model1,1,0);
    ui->layoutFileExplorer->addWidget(model2,1,1);

    model2->setFocus();

    model1->setupWidget();
    model2->setupWidget();

    for (int i = 0; i < fileSystemEntryList.size(); i++)
    {
        ui->comboBoxExplorer1->addItem(fileSystemEntryList.at(i)->getName());
        ui->comboBoxExplorer2->addItem(fileSystemEntryList.at(i)->getName());
    }

    QShortcut *shortcutF2 = new QShortcut(QKeySequence (Qt::Key_F2), this);
    QObject::connect(shortcutF2, SIGNAL(activated()), ui->buttonQueue, SLOT(click()));

    QShortcut *shortcutF5 = new QShortcut(QKeySequence (Qt::Key_F5), this);
    QObject::connect(shortcutF5, SIGNAL(activated()), ui->buttonCopy, SLOT(click()));

    QShortcut *shortcutF6 = new QShortcut(QKeySequence (Qt::Key_F6), this);
    QObject::connect(shortcutF6, SIGNAL(activated()), ui->buttonMove, SLOT(click()));

    QShortcut *shortcutF7 = new QShortcut(QKeySequence (Qt::Key_F7), this);
    QObject::connect(shortcutF7, SIGNAL(activated()), model1, SLOT(createItem()));
    QObject::connect(shortcutF7, SIGNAL(activated()), model2, SLOT(createItem()));

    QShortcut *shortcutF8 = new QShortcut(QKeySequence (Qt::Key_F8), this);
    QObject::connect(shortcutF8, SIGNAL(activated()), model1, SLOT(deleteItem()));
    QObject::connect(shortcutF8, SIGNAL(activated()), model2, SLOT(deleteItem()));

    QShortcut *shortcutF10 = new QShortcut(QKeySequence (Qt::Key_F10), this);
    QObject::connect(shortcutF10, SIGNAL(activated()), ui->buttonQuit, SLOT(click()));

    QShortcut *shortcutF11 = new QShortcut(QKeySequence (Qt::Key_F11), this);
    QObject::connect(shortcutF11, SIGNAL(activated()), ui->buttonSession, SLOT(click()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonQueue_clicked()
{
    QString path = "/usr";

    FileSystemDirReadDialog *dirReadDialog = new FileSystemDirReadDialog(this);
    dirReadDialog->show();
    dirReadDialog->setPath(path);

    FileSystemDirRead *dirRead = new FileSystemDirRead(path, QDirIterator::Subdirectories);
    QThread *dirReadThread = new QThread(this);
    dirRead->moveToThread(dirReadThread);

    connect(dirReadDialog, SIGNAL(canceled()), dirRead, SLOT(cancel()));
    connect(dirRead, SIGNAL(progressChanged(int,int,int,double)), dirReadDialog, SLOT(updateTextFields(int,int,int,double)));
    connect(dirRead, SIGNAL(data(QStringList)), this, SLOT(getData(QStringList)));
    connect(dirRead, SIGNAL(done()), dirReadDialog, SLOT(on_buttonBox_rejected()));

    connect(dirReadThread, SIGNAL(started()), dirRead, SLOT(begin()));
    connect(dirRead, SIGNAL(done()), dirReadThread, SLOT(quit()));
    connect(dirRead, SIGNAL(done()), dirRead, SLOT(deleteLater()));
    connect(dirRead, SIGNAL(done()), dirReadDialog, SLOT(deleteLater()));
    connect(dirReadThread, SIGNAL(finished()), dirReadThread, SLOT(deleteLater()));

    dirReadThread->start(QThread::LowPriority);
}

void MainWindow::on_comboBoxExplorer1_currentIndexChanged(int index)
{

}

void MainWindow::on_comboBoxExplorer2_currentIndexChanged(int index)
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

void MainWindow::getData(QStringList data)
{
    qDebug() << "got " << data.size() << " items";
}

void MainWindow::tst()
{

    qDebug() << "tst";
}

void MainWindow::on_buttonQuit_clicked()
{
    QMessageBox mBox(QMessageBox::NoIcon
                     ,"Выход"
                     , "Завершить сеанс и выйти из приложения?"
                     , QMessageBox::Yes | QMessageBox::No);
    mBox.setWindowIcon(QIcon(":/images/dialog-question.png"));
    mBox.setModal(true);
    mBox.setWindowFlags((mBox.windowFlags() | Qt::WindowStaysOnTopHint));
    int ret = mBox.exec();

    if (ret == QMessageBox::Yes)
    {
        qApp->quit();
    }
    else
    {
        return;
    }
}

void MainWindow::on_buttonCopy_clicked()
{

}

void MainWindow::on_buttonMove_clicked()
{

}

void MainWindow::on_buttonCatalogue_clicked()
{

}

void MainWindow::on_buttonDelete_clicked()
{

}
