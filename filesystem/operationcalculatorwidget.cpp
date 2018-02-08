#include "operationcalculatorwidget.h"

static const int KSIZE = 1024;
static const int MSIZE = KSIZE * KSIZE;

OperationCalculatorWidget::OperationCalculatorWidget(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Обработка файлов и каталогов");

    doubleCancel = false;
    buttonShown = true;

    vBox = new QVBoxLayout;
    hBox1 = new QHBoxLayout;
    hBox2 = new QHBoxLayout;
    hBox3 = new QHBoxLayout;
    hBox4 = new QHBoxLayout;
    hBox5 = new QHBoxLayout;
    hBox6 = new QHBoxLayout;

    bBox = new QDialogButtonBox;
    bBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    lAll = new QLabel("0", this);
    hBox1->addWidget(new QLabel("Всего элементов: ", this));
    hBox1->addStretch(1);
    hBox1->addWidget(lAll);
    //lRoot = new QLabel("/", this);
    //hBox2->addWidget(new QLabel("Корневые: ", this));
    //hBox2->addStretch(1);
    //hBox2->addWidget(lRoot);
    lSubDir = new QLabel("0", this);
    hBox3->addWidget(new QLabel("Индексировано каталогов: ", this));
    hBox3->addStretch(1);
    hBox3->addWidget(lSubDir);
    lFile = new QLabel("0", this);
    hBox4->addWidget(new QLabel("Индексировано файлов: ", this));
    hBox4->addStretch(1);
    hBox4->addWidget(lFile);
    lErr = new QLabel("0", this);
    hBox5->addWidget(new QLabel("Не обработано: ", this));
    hBox5->addStretch(1);
    hBox5->addWidget(lErr);
    lSize = new QLabel("0", this);
    hBox6->addWidget(new QLabel("Размер: ", this));
    hBox6->addStretch(1);
    hBox6->addWidget(lSize);

    vBox->addLayout(hBox1);
    //vBox->addLayout(hBox2);
    vBox->addLayout(hBox3);
    vBox->addLayout(hBox4);
    vBox->addLayout(hBox5);
    vBox->addLayout(hBox6);
    vBox->addWidget(bBox);

    setButtonsRemove(false);
    setLayout(vBox);
}

OperationCalculatorWidget::~OperationCalculatorWidget()
{

}

void OperationCalculatorWidget::setButtonOkEnable(bool enabled)
{
    bBox->button(QDialogButtonBox::Ok)->setEnabled(enabled);
}

void OperationCalculatorWidget::setButtonCancelEnable(bool enabled)
{
    bBox->button(QDialogButtonBox::Cancel)->setEnabled(enabled);
}

//void OperationCalculatorWidget::setItems(QString path)
//{
//    lRoot->setText(path);
//}

void OperationCalculatorWidget::setData(int total, int dir, int file, int err, double size)
{
    lAll->setText(QString::number(total));
    lSubDir->setText(QString::number(dir));
    lFile->setText(QString::number(file));
    lErr->setText(QString::number(err));

    QString humanSize;

    humanSize = QString::number(size) + " байт";

    if (size > (KSIZE))
    {
        humanSize = QString::number(size / (KSIZE), 'f', 2) + " Кбайт";
    }

    if (size > (MSIZE))
    {
        humanSize = QString::number(size / (MSIZE), 'f', 2) + " Мбайт";
    }

    lSize->setText(humanSize);
}

void OperationCalculatorWidget::setButtonsRemove(bool remove)
{
    if(remove && buttonShown)
    {
        bBox->hide();
        buttonShown = false;
    }
    else
    {
        bBox->show();
        connect(bBox, &QDialogButtonBox::accepted, this, &OperationCalculatorWidget::accept);
        connect(bBox, &QDialogButtonBox::rejected, this, &OperationCalculatorWidget::reject);
        buttonShown = true;
    }
}

void OperationCalculatorWidget::accept()
{
    emit ok();
    //QDialog::accept();
}

void OperationCalculatorWidget::reject()
{
    if(!buttonShown)
    {
        return;
    }

    if (!doubleCancel)
    {
        emit canceled();
        doubleCancel = !doubleCancel;
    }
    else
    {
        QDialog::reject();
    }
}

void OperationCalculatorWidget::showEvent(QShowEvent *event)
{
    setFixedWidth(500);
    setFixedHeight(this->height());
    QDialog::showEvent(event);
}

void OperationCalculatorWidget::counted()
{
    doubleCancel = true;
}
