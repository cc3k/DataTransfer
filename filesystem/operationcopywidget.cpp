#include "operationcopywidget.h"

OperationCopyWidget::OperationCopyWidget(QWidget *parent) : QWidget(parent)
{
    calc = new OperationCalculator;
    widget = new OperationCalculatorWidget(this);

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

void OperationCopyWidget::start()
{
    dialog->setDestination(destination);

    if(dialog->exec() == QDialog::Accepted)
    {
      calc->setInputPathList(list);
      calc->begin();
    }
}

