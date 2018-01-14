#ifndef CUSTOMDIRMODEL_H
#define CUSTOMDIRMODEL_H

#include <QDirModel>
#include <QWidget>
#include <QDebug>

class CustomDirModel : public QDirModel
{
    Q_OBJECT

public:
    explicit CustomDirModel(QWidget *parent = 0);
    ~CustomDirModel() {}

private:

protected:
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // CUSTOMDIRMODEL_H
