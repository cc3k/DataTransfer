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

    model1 = new FileSystemWidget("ФС1", "/home/projekt");
    model2 = new FileSystemWidget("ФС2", "/home/projekt");

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
    qDebug() << "queue clicked";

    QString path = "/usr";
    //    QMessageBox mBox(QMessageBox::NoIcon
    //                     ,"Обработка " + path
    //                     , "path"
    //                     , QMessageBox::Cancel);
    //    mBox.setWindowIcon(QIcon(":/images/dialog-information.png"));
    //    mBox.setModal(true);
    //    mBox.setWindowFlags((mBox.windowFlags() | Qt::WindowStaysOnTopHint));

    //    QThread *pT = new QThread(this);

    //    PathParse *p = new PathParse(path);
    //    p->moveToThread(pT);
    //    pT->start();
    //    p->begin();

    //    connect(p, SIGNAL(progressChanged()), this, SLOT(tst()));
    //    int ret = mBox.exec();

    //    if (ret == QMessageBox::Cancel)
    //    {
    //        qDebug() << "cancel";
    //        p->cancel();
    //    }
    FileSystemFilePathDialog *pathParserDialog = new FileSystemFilePathDialog;
    pathParserDialog->setModal(true);
    pathParserDialog->setWindowFlags((pathParserDialog->windowFlags() | Qt::WindowStaysOnTopHint));
    pathParserDialog->show();
    pathParserDialog->setPath(path);

    FileSystemFilePath *pathParse = new FileSystemFilePath(path);
    QThread *pathParseThread = new QThread(this);
    pathParse->moveToThread(pathParseThread);

    connect(pathParserDialog, SIGNAL(canceled()), pathParse, SLOT(cancel()));
    connect(pathParse, SIGNAL(progressChanged(int,int,int,double)), pathParserDialog, SLOT(updateTextFields(int,int,int,double)));
    connect(pathParse, SIGNAL(data(QStringList)), this, SLOT(getData(QStringList)));
    connect(pathParse, SIGNAL(done()), pathParserDialog, SLOT(on_buttonBox_rejected()));

    connect(pathParseThread, SIGNAL(started()), pathParse, SLOT(begin()));
    connect(pathParse, SIGNAL(done()), pathParseThread, SLOT(quit()));
    connect(pathParse, SIGNAL(done()), pathParse, SLOT(deleteLater()));
    connect(pathParseThread, SIGNAL(finished()), pathParseThread, SLOT(deleteLater()));

    pathParseThread->start(QThread::LowPriority);
    //pathParse->begin();


    qDebug() << pathParse->getPathList();
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
