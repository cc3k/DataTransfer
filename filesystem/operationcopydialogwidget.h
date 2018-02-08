#ifndef OPERATIONCOPYDIALOGWIDGET_H
#define OPERATIONCOPYDIALOGWIDGET_H

#include <QDialog>

namespace Ui {
class OperationCopyDialogWidget;
}

class OperationCopyDialogWidget : public QDialog
{
    Q_OBJECT

public:
    explicit OperationCopyDialogWidget(QWidget *parent = 0);
    ~OperationCopyDialogWidget();

    void setItemText(const QString value);
    QString getFilter() const;

    void setDestination(const QString value);
    QString getDestination() const;

    void setFilterEnabled(bool enabled);

private:
    Ui::OperationCopyDialogWidget *ui;

};

#endif // OPERATIONCOPYDIALOGWIDGET_H
