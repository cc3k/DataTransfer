#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sessionId = generateSessionId();

    setWindowTitle("ФПО ВКС. Идентификатор сессии: [" + sessionId + "]");
    setWindowState(Qt::WindowMaximized);
    setWindowIcon(QIcon(":/images/transfer.png"));

    QShortcut *shortcutF2 = new QShortcut(QKeySequence (Qt::Key_F2), this);
    QObject::connect(shortcutF2, SIGNAL(activated()), ui->buttonProperties, SLOT(click()));

    QShortcut *shortcutF5 = new QShortcut(QKeySequence (Qt::Key_F5), this);
    QObject::connect(shortcutF5, SIGNAL(activated()), ui->buttonCopy, SLOT(click()));

    QShortcut *shortcutF6 = new QShortcut(QKeySequence (Qt::Key_F6), this);
    QObject::connect(shortcutF6, SIGNAL(activated()), ui->buttonMove, SLOT(click()));

    QShortcut *shortcutF7 = new QShortcut(QKeySequence (Qt::Key_F7), this);
    QObject::connect(shortcutF7, SIGNAL(activated()), ui->buttonCatalogue, SLOT(click()));

    QShortcut *shortcutF8 = new QShortcut(QKeySequence (Qt::Key_F8), this);
    QObject::connect(shortcutF8, SIGNAL(activated()), ui->buttonDelete, SLOT(click()));

    QShortcut *shortcutF10 = new QShortcut(QKeySequence (Qt::Key_F10), this);
    QObject::connect(shortcutF10, SIGNAL(activated()), ui->buttonQuit, SLOT(click()));

    QShortcut *shortcutF11 = new QShortcut(QKeySequence (Qt::Key_F11), this);
    QObject::connect(shortcutF11, SIGNAL(activated()), ui->buttonSession, SLOT(click()));

    QShortcut *shortcutALT1 = new QShortcut(QKeySequence (Qt::ALT + Qt::Key_1), this);
    QObject::connect(shortcutALT1, &QShortcut::activated, this, &MainWindow::showPanelBoxLeft);

    QShortcut *shortcutALT2 = new QShortcut(QKeySequence (Qt::ALT + Qt::Key_2), this);
    QObject::connect(shortcutALT2, &QShortcut::activated, this, &MainWindow::showPanelBoxRight);

    panelLeft = new PanelWidget(this);
    panelLeft->updateConfig(":/config/stations.xml");

    panelRight = new PanelWidget(this);
    panelRight->updateConfig(":/config/stations.xml");

    //передача фокуса по табу
    connect(panelLeft, &PanelWidget::focusLost, panelRight, &PanelWidget::setFocus);
    connect(panelRight, &PanelWidget::focusLost, panelLeft, &PanelWidget::setFocus);

    //получение текущей директории и активной панели
    connect(panelLeft, &PanelWidget::active, this, &MainWindow::setCurrentPanel);
    connect(panelRight, &PanelWidget::active, this, &MainWindow::setCurrentPanel);
    connect(panelLeft, &PanelWidget::currentItemChanged, this, &MainWindow::itemChanged);
    connect(panelRight, &PanelWidget::currentItemChanged, this, &MainWindow::itemChanged);

    //ошибки чтения и доступа
    connect(panelLeft, &PanelWidget::readError, this, &MainWindow::readError);
    connect(panelRight, &PanelWidget::readError, this, &MainWindow::readError);

    ui->panelLayout->addWidget(panelLeft);
    ui->panelLayout->addWidget(panelRight);

    panelLeft->resetCurrentPosition();
    panelRight->setFocus();
    setCurrentPanel(panelRight);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete activePanel;
}

QString MainWindow::getRandomString(const int length) const
{
    const QString chars("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

    QString randomString;
    QTime stamp = QTime::currentTime();
    qsrand(stamp.msec());

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
    QString sessionId = QDateTime::currentDateTime().toString("yyMMdd_HHmmss_")
            + getRandomString(4);
    return sessionId;
}

void MainWindow::on_buttonSession_clicked()
{
    QMessageBox *box = new QMessageBox(this);
    box->setWindowTitle("Сессия");
    box->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box->setText("Текущий идентификатор: " + sessionId + "\nСгенерировать новый?");
    box->setIcon(QMessageBox::Question);

    if (box->exec() == QMessageBox::Yes)
    {
        sessionId = generateSessionId();
        setWindowTitle("ФПО ВКС. Идентификатор сессии : [" + sessionId + "]");
    }
    delete box;
}

void MainWindow::showPanelBoxLeft()
{
    panelLeft->openBox();
}

void MainWindow::showPanelBoxRight()
{
    panelRight->openBox();
}

void MainWindow::setCurrentPanel(PanelWidget *widget)
{
    activePanel = widget;

    if (activePanel == panelRight)
    {
        passivePanel = panelLeft;
    }

    if (activePanel == panelLeft)
    {
        passivePanel = panelRight;
    }
}

void MainWindow::itemChanged()
{
    //qDebug() << "panel state changed";
}

void MainWindow::readError(QString path)
{
    QMessageBox::critical(this, "Ошибка", "Отказано в доступе: " + path);
}

void MainWindow::on_buttonQuit_clicked()
{
    QMessageBox *box = new QMessageBox(this);
    box->setModal(true);
    box->setWindowTitle("Выход");
    box->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box->setText("Завершить сеанс и выйти из приложения?");
    box->setIcon(QMessageBox::Question);

    if (box->exec() == QMessageBox::Yes)
    {
        qApp->quit();
    }

    delete box;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox *box = new QMessageBox(this);
    box->setModal(true);
    box->setWindowTitle("Выход");
    box->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box->setText("Завершить сеанс и выйти из приложения?");
    box->setIcon(QMessageBox::Question);

    if (box->exec() == QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }

    delete box;
}

void MainWindow::on_buttonProperties_clicked()
{
    QStringList list;

    OperationCalculatorWidget *widget = new OperationCalculatorWidget(this);
    widget->setModal(true);
    widget->setButtonOkEnable(false);
    widget->show();

    if(activePanel->getSelection().size() == 0)
    {
        widget->setItems(activePanel->getCurrentItem());
        list << activePanel->getCurrentItem();
    }

    if(activePanel->getSelection().size() == 1)
    {
        widget->setItems(activePanel->getSelection().first());
        list = activePanel->getSelection();
    }

    if(activePanel->getSelection().size() > 1)
    {
        widget->setItems(QString::number(activePanel->getSelection().size()));
        list = activePanel->getSelection();
    }

    OperationCalculator *calc = new OperationCalculator(list, QDirIterator::Subdirectories);
    QThread *thread = new QThread(this);

    connect(widget, &OperationCalculatorWidget::ok, widget, &OperationCalculatorWidget::deleteLater);
    connect(widget, &OperationCalculatorWidget::canceled, calc, &OperationCalculator::cancel, Qt::DirectConnection); //без директ коннекшн не будет передаваться кенсел, надо бы мьютекс на изкенселед в калькулятор

    connect(calc, &OperationCalculator::progress, widget, &OperationCalculatorWidget::setData);
    connect(calc, &OperationCalculator::done, thread, &QThread::exit);

    connect(thread, &QThread::started, calc, &OperationCalculator::begin);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(thread, &QThread::finished, calc, &OperationCalculator::deleteLater);

    QMetaObject::Connection * const connection = new QMetaObject::Connection;
    *connection = connect(thread, &QThread::finished, [this, widget, connection]()
    {
        widget->setButtonOkEnable(true);
        widget->setButtonCancelEnable(false);
        QObject::disconnect(*connection);
        delete connection;
    });

    calc->moveToThread(thread);
    thread->start();

    //считает и переключает кнопки как надо
    //connection = connect(thread, &QThread::finished, !!this!!,[this, widget, connection](){ не работает!!!
}

void MainWindow::on_buttonCopy_clicked()
{
//    OperationCopyDialogWidget *dialog = new OperationCopyDialogWidget(this);
//    dialog->setModal(true);
//    QStringList list;
//    QString filter;
//    qint64 totalSize = 0;
//    QString destination = passivePanel->getCurrentPath();
//    dialog->setDestination(destination);

//    if (activePanel->getSelection().size() != 0)
//    {
//        dialog->setItemText("Копировать выбранные файлы/каталоги (" + QString::number(activePanel->getSelection().size()) + " шт.)");

//        if(dialog->exec() == QDialog::Accepted)
//        {
//            list = activePanel->getSelection();
//            destination = dialog->getDestination();
//            filter = dialog->getFilter();
//        }
//    }
//    else
//    {
//        activePanel->selectItemPath(activePanel->getCurrentItem(), Qt::Checked);

//        QFileInfo item(activePanel->getCurrentItem());

//        if (item.isFile())
//        {
//            dialog->setItemText("Копировать выбранный файл " + item.fileName());
//            dialog->setFilterEnabled(false);
//        }

//        if (item.isDir())
//        {
//            dialog->setItemText("Копировать выбранный каталог " + activePanel->getCurrentItem());
//        }

//        if(dialog->exec() == QDialog::Accepted)
//        {
//            list = activePanel->getSelection();
//            destination = dialog->getDestination();
//            filter = dialog->getFilter();
//        }
//        else
//        {
//            activePanel->selectItemPath(activePanel->getCurrentItem(), Qt::Unchecked);
//        }
//    }

//    delete dialog;

//    OperationCalculatorWidget *widget = new OperationCalculatorWidget(this);
//    widget->setItems("Выделенные файлы/каталоги (" +
//                     QString::number(activePanel->getSelection().size()) +
//                     "шт.)");
//    widget->setModal(true);
//    widget->setButtonOkEnable(false);
//    widget->setButtonCancelEnable(false);

//    OperationCalculator *calc = new OperationCalculator(list, QDirIterator::Subdirectories);
//    QThread *thread = new QThread(this);

//    connect(widget, &OperationCalculatorWidget::canceled, calc, &OperationCalculator::cancel, Qt::DirectConnection);
//    connect(calc, &OperationCalculator::progress, widget, &OperationCalculatorWidget::setData, Qt::DirectConnection);

//    connect(thread, &QThread::started, calc, &OperationCalculator::begin);
//    connect(calc, &OperationCalculator::done, thread, &QThread::exit);
//    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
//    connect(thread, &QThread::finished, widget, &OperationCalculatorWidget::deleteLater);

//    QMetaObject::Connection * const connection = new QMetaObject::Connection;
//    *connection = connect(thread, &QThread::finished, [this, widget, connection]()
//    {
//        //widget->setButtonOkEnable(true);
//        //widget->setButtonCancelEnable(false);
//        widget->hide();

//        QObject::disconnect(*connection);
//        delete connection;
//    });

//    calc->moveToThread(thread);
//    thread->start();

//    widget->exec();

//    totalSize = calc->getSize();

//    qDebug() << list.size();
//    qDebug() << destination;
//    qDebug() << filter;
//    qDebug() << totalSize;

    OperationCopyWidget *widget = new OperationCopyWidget(this);
    widget->setDestination(passivePanel->getCurrentPath());

    if(activePanel->getSelection().size() == 0)
    {
        widget->setList(QStringList() << activePanel->getCurrentItem());
    }
    else
    {
        widget->setList(activePanel->getSelection());
    }

    widget->start();

}

void MainWindow::on_buttonMove_clicked()
{
    //    QMessageBox *mbox = new QMessageBox;
    //    mbox->setWindowTitle(tr("Modem Shutting Down..."));
    //    mbox->setText("Please wait while the Modem shuts down...");
    //    mbox->show();
    //    mbox->setStandardButtons(0);
    //    QTimer::singleShot(5000, mbox, SLOT(hide()));

}

void MainWindow::on_buttonCatalogue_clicked()
{
    QDialog *dialog = new QDialog(this);
    QVBoxLayout *vBox = new QVBoxLayout(dialog);
    QLabel *label = new QLabel(dialog);
    QLineEdit *lineEdit = new QLineEdit(dialog);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(dialog);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    label->setText("Веедите имя каталога:");

    vBox->addWidget(label);
    vBox->addWidget(lineEdit);
    vBox->addWidget(buttonBox);
    dialog->setLayout(vBox);

    dialog->setWindowTitle("Создание каталога");
    dialog->setMinimumWidth(350);

    connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);

    if(dialog->exec() == QDialog::Accepted)
    {
        if(lineEdit->text().size() != 0)
        {
            QDir dir(activePanel->getCurrentPath() + "/" + lineEdit->text());
            QFile file(activePanel->getCurrentPath() + "/" + lineEdit->text());
            if(!dir.exists() && !file.exists())
            {
                if(!dir.mkdir(dir.absolutePath()))
                {
                    QMessageBox::critical(this, "Ошибка", "Ошибка создания каталога");
                }
            }
            else
            {
                QMessageBox::critical(this, "Ошибка", "Элемент с этим именем уже существует");
            }
        }
    }
    dialog->deleteLater();
}

void MainWindow::on_buttonDelete_clicked()
{
    QString message = "Вы действительно хотите удалить\n";

    if (activePanel->getSelection().size() != 0)
    {
        QMessageBox *box;
        box = new QMessageBox(this);
        box->setWindowTitle("Удаление");
        box->setText(message + "Выбранные файлы/каталоги (" + QString::number(activePanel->getSelection().size()) + " шт.)?");
        box->setIcon(QMessageBox::Question);
        box->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        box->setMinimumWidth(350);

        if(box->exec() == QMessageBox::Ok)
        {
            QStringList list = activePanel->getSelection();
            int selection = list.size();

            for (int i = 0; i < selection; i++)
            {
                QFileInfo item(list.at(i));
                if (item.isFile())
                {
                    QFile file(item.absoluteFilePath());
                    if(!file.remove())
                    {
                        QMessageBox::critical(this, "Ошибка", "Ошибка удаления файла: " + item.absoluteFilePath());
                    }
                }

                if (item.isDir())
                {
                    QDir dir(item.absoluteFilePath());
                    if(!dir.removeRecursively())
                    {
                        QMessageBox::critical(this, "Ошибка", "Ошибка удаления каталога: " + item.absoluteFilePath());
                    }
                }
            }
        }
        delete box;
    }
    else
    {
        activePanel->selectItemPath(activePanel->getCurrentItem(), Qt::Checked);
        QFileInfo item(activePanel->getCurrentItem());

        QMessageBox *box;
        box = new QMessageBox(this);
        box->setWindowTitle("Удаление");
        box->setIcon(QMessageBox::Question);
        box->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        box->setMinimumWidth(350);

        if (item.isFile())
        {
            box->setText(message + "выбранный файл " + item.fileName() + "?");
        }

        if (item.isDir())
        {
            box->setText(message + "выбранный каталог " + activePanel->getCurrentItem() + "?");
        }

        if(box->exec() == QMessageBox::Ok)
        {
            if (item.isFile())
            {
                QFile file(item.absoluteFilePath());
                if(!file.remove())
                {
                    QMessageBox::critical(this, "Ошибка", "Ошибка удаления файла: " + item.absoluteFilePath());
                }
            }

            if (item.isDir())
            {
                QDir dir(item.absoluteFilePath());
                if(!dir.removeRecursively())
                {
                    QMessageBox::critical(this, "Ошибка", "Ошибка удаления каталога: " + item.absoluteFilePath());
                }
            }
        }
        else
        {
            activePanel->selectItemPath(activePanel->getCurrentItem(), Qt::Unchecked);
        }
        delete box;
    }
}
