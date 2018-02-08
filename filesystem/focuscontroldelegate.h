#ifndef FOCUSCONTROLDELEGATE_H
#define FOCUSCONTROLDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class FocusControlDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
     explicit FocusControlDelegate(QObject *parent = 0);
    ~FocusControlDelegate();

    virtual void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const;
    void setFocusBorderEnabled(bool enabled);

protected:
    bool f_focus_border_enabled;

};

#endif // FOCUSCONTROLDELEGATE_H
