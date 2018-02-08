#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include <QKeyEvent>
#include <QDir>
#include <QFocusEvent>
#include <QItemSelectionModel>
#include <QModelIndex>

#include <QDebug>

class TableView : public QTableView
{
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

protected slots:
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);

public:
    explicit TableView(QWidget *parent = 0);
    ~TableView();

private:

signals:
    void keyEnter();
    void keyTab();
    void keySelect();
    void keyCtrlA();
    void keyLeft();
    void keyRight();
    void keyPlus();
};

#endif // TABLEVIEW_H
