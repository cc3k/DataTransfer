#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QTableView>
#include <QKeyEvent>

class CustomTableView : public QTableView
{
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

    bool isFocused;

public:
    explicit CustomTableView(QWidget *parent = 0);
    ~CustomTableView() {}

    bool getIsFocused() const;

signals:
    void keyTab();
    void keyEnter();
    void keyLeft();
    void keySpace();

    void looseFocus();
    void getFocus();
};

#endif // CUSTOMTABLEVIEW_H
