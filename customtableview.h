#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QTableView>
#include <QKeyEvent>

class CustomTableView : public QTableView
{
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *event);

public:
    explicit CustomTableView(QWidget *parent = 0);
    ~CustomTableView() {}

signals:
    void keyTab();
    void keyEnter();
    void keyLeft();
};

#endif // CUSTOMTABLEVIEW_H
