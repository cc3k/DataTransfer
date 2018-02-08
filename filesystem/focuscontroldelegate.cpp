#include "focuscontroldelegate.h"

FocusControlDelegate::FocusControlDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    f_focus_border_enabled = false;
}

FocusControlDelegate::~FocusControlDelegate()
{

}

void FocusControlDelegate::setFocusBorderEnabled(bool enabled)
{
    f_focus_border_enabled = enabled;
}

void FocusControlDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);
    if(!f_focus_border_enabled && option->state & QStyle::State_HasFocus)
        option->state = option->state & ~QStyle::State_HasFocus;
}
