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
    }
    case Qt::Key_Right:
    case Qt::Key_Return:
    {
        emit keyEnter();
        break;
    }
    case Qt::Key_Left:
    {
        emit keyLeft();
        break;
    }
    case Qt::Key_Space:
    case Qt::Key_Insert:
    {
        selectionModel()->setCurrentIndex(currentIndex(), QItemSelectionModel::Toggle);
        selectRow(currentIndex().row() + 1);

        break;
    }
    default:
        QTableView::keyPressEvent(event);
        break;
    }

}
