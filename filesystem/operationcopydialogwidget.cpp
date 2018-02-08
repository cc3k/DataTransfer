#include "operationcopydialogwidget.h"
#include "ui_operationcopydialogwidget.h"

OperationCopyDialogWidget::OperationCopyDialogWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperationCopyDialogWidget)
{
    ui->setupUi(this);
    ui->buttonBox->setFocus();
}

OperationCopyDialogWidget::~OperationCopyDialogWidget()
{
    delete ui;
}

void OperationCopyDialogWidget::setItemText(const QString value)
{
    ui->labelElements->setText(value);
}

QString OperationCopyDialogWidget::getFilter() const
{
    return ui->lineFilter->text();
}

void OperationCopyDialogWidget::setDestination(const QString value)
{
    ui->lineDestination->setText(value);
}

QString OperationCopyDialogWidget::getDestination() const
{
    return ui->lineDestination->text();
}

void OperationCopyDialogWidget::setFilterEnabled(bool enabled)
{
    ui->lineFilter->setEnabled(enabled);
}
