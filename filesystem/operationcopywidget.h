#ifndef OPERATIONCOPYWIDGET_H
#define OPERATIONCOPYWIDGET_H

#include <QDialogButtonBox>
#include <QProgressBar>
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QThread>
#include <QDateTime>
#include <QCoreApplication>

#include "filesystem/operationcalculator.h"
#include "filesystem/operationcalculatorwidget.h"
#include "filesystem/operationcopydialogwidget.h"

class OperationCopyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OperationCopyWidget(QWidget *parent = 0);

    void setList(const QStringList &value);
    void setDestination(const QString &value);

    void open();
private:
    OperationCalculator *calc;
    OperationCalculatorWidget *widget;
    OperationCopyDialogWidget *dialog;

    QStringList list;
    QString destination;

signals:

public slots:

};

#endif // OPERATIONCOPYWIDGET_H
