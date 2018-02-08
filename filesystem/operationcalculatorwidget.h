#ifndef OPERATIONCALCULATORWIDGET_H
#define OPERATIONCALCULATORWIDGET_H

#include <QDialog>
#include <QDebug>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QShowEvent>
#include <QCloseEvent>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class OperationCalculatorWidget : public QDialog
{
    Q_OBJECT
public:
    explicit OperationCalculatorWidget(QWidget *parent = 0);
    ~OperationCalculatorWidget();
    void setButtonOkEnable(bool enabled);
    void setButtonCancelEnable(bool enabled);

public slots:
    //void setItems(QString path);
    void setData(int total, int dir, int file, int err, double size);
    void setButtonsRemove(bool remove);

protected slots:
    void accept();
    void reject();


private:
    QVBoxLayout *vBox;
    QHBoxLayout *hBox1;
    QHBoxLayout *hBox2;
    QHBoxLayout *hBox3;
    QHBoxLayout *hBox4;
    QHBoxLayout *hBox5;
    QHBoxLayout *hBox6;

    QLabel *lRoot;
    QLabel *lAll;
    QLabel *lSubDir;
    QLabel *lFile;
    QLabel *lErr;
    QLabel *lSize;
    QDialogButtonBox *bBox;

    bool doubleCancel;
    bool buttonShown;

    void showEvent(QShowEvent *event);

signals:
    void canceled();
    void ok();

public slots:
    void counted();
};

#endif // OPERATIONCALCULATORWIDGET_H
