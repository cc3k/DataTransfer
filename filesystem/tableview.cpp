#include "tableview.h"

TableView::TableView(QWidget *parent) : QTableView(parent)
{

}

TableView::~TableView()
{

}

void TableView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {

    case Qt::Key_A:
        if(event->modifiers() & Qt::ControlModifier)
        {
            emit keyCtrlA();
        }
        break;

    case Qt::Key_Return:
    {
        emit keyEnter();
        break;
    }

    case Qt::Key_Tab:
    {
        emit keyTab();
        break;
    }

    case Qt::Key_Right:
    {
        emit keyRight();
        break;
    }

    case Qt::Key_Left:
    {
        emit keyLeft();
        break;
    }

    case Qt::Key_Plus:
    {
        emit keyPlus();
        break;
    }

    case Qt::Key_Space:
    case Qt::Key_Insert:
    {
        emit keySelect();
        break;
    }

    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_PageUp:
    case Qt::Key_PageDown:
    {
        QTableView::keyPressEvent(event);
        break;
    }

    default:
        break;
    }
}

void TableView::focusInEvent(QFocusEvent *event)
{
    selectRow(currentIndex().row());
    QTableView::focusInEvent(event);
}

void TableView::focusOutEvent(QFocusEvent *event)
{
    //clearSelection();
    QTableView::focusOutEvent(event);
}

void TableView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    selectRow(current.row());
    QTableView::currentChanged(current,previous);
}
