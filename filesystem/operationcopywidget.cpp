#include "operationcopywidget.h"

OperationCopyWidget::OperationCopyWidget(QWidget *parent) : QWidget(parent)
{
    //calc = new OperationCalculator;
    //widget = new OperationCalculatorWidget(this);

    dialog = new OperationCopyDialogWidget(this);
}

void OperationCopyWidget::setList(const QStringList &value)
{
    list = value;
}

void OperationCopyWidget::setDestination(const QString &value)
{
    destination = value;
}

void OperationCopyWidget::open()
{
    dialog->setDestination(destination);

    if(dialog->exec() == QDialog::Accepted)
    {
        OperationCalculatorWidget *widget = new OperationCalculatorWidget(this);
        widget->setButtonOkEnable(false);
        widget->setModal(true);
        widget->setButtonsRemove(true);
        widget->show();

        OperationCalculator *calc = new OperationCalculator(list, QDirIterator::Subdirectories);
        QThread *thread = new QThread(this);

        //connect(widget, &OperationCalculatorWidget::ok, widget, &OperationCalculatorWidget::deleteLater);
        //connect(widget, &OperationCalculatorWidget::canceled, calc, &OperationCalculator::cancel, Qt::DirectConnection); //без директ коннекшн не будет передаваться кенсел, надо бы мьютекс на изкенселед в калькулятор

        connect(calc, &OperationCalculator::progress, widget, &OperationCalculatorWidget::setData);
        connect(calc, &OperationCalculator::done, thread, &QThread::exit);

        connect(thread, &QThread::started, calc, &OperationCalculator::begin);
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
       // connect(thread, &QThread::finished, calc, &OperationCalculator::deleteLater);
       // connect(thread, &QThread::finished, widget, &OperationCalculatorWidget::counted);

        QMetaObject::Connection * const connection = new QMetaObject::Connection;
        *connection = connect(thread, &QThread::finished, [this, widget, connection]()
        {
            widget->setButtonOkEnable(true);
            QObject::disconnect(*connection);
            delete connection;
        });

        calc->moveToThread(thread);
        thread->start();

        int start = QDateTime::currentMSecsSinceEpoch();

        while (thread->isRunning())
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }

        int stop = QDateTime::currentMSecsSinceEpoch();

        qDebug() << "done in " << stop - start << "msec";

        QStringList files = calc->getDirList();
        QStringList dirs = calc->getFileList();

        delete calc;
        delete widget;

    }
}

