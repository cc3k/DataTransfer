#include "customtableview.h"

CustomTableView::CustomTableView(QWidget *parent) : QTableView(parent)
{

}

void CustomTableView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Tab:
    {
        emit keyTab();
        break;

    case Qt::Key_Return:
        {
            emit keyEnter();
            break;
        }
        default:
            QTableView::keyPressEvent(event);
            break;
        }
    }
}
