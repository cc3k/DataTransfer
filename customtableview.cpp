#include "customtableview.h"

CustomTableView::CustomTableView(QWidget *parent) : QTableView(parent)
{
    setFocusPolicy(Qt::NoFocus);
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

        //    case Qt::Key_Space:
        //    case Qt::Key_Insert:
        //    {
        //selectionModel()->setCurrentIndex(currentIndex(), QItemSelectionModel::Toggle);
        //selectRow(currentIndex().row() + 1);

        //selectRow(currentIndex().row());
        //selectRow(currentIndex().row() + 1);
        //selectionModel()->setCurrentIndex(currentIndex(), QItemSelectionModel::Deselect);

        //moveCursor() !!!!!

        //        break;
        //    }

    case Qt::Key_Space:
    case Qt::Key_Insert:
    {
        emit keySpace();
        //selectionModel()->setCurrentIndex(currentIndex(), QItemSelectionModel::Toggle);

        //selectRow(currentIndex().row() + 1);

     //   moveCursor() !!!!!

                break;
    }

    default:
        QTableView::keyPressEvent(event);
        break;
    }

}

void CustomTableView::focusInEvent(QFocusEvent *event)
{

    isFocused = true;
    selectRow(0);
    emit getFocus();
}

void CustomTableView::focusOutEvent(QFocusEvent *event)
{
    isFocused = false;
    clearSelection();
    emit looseFocus();
}

bool CustomTableView::getIsFocused() const
{
    return isFocused;
}
