#ifndef CUSTOMDIRMODEL_H
#define CUSTOMDIRMODEL_H

#include <QDirModel>
#include <QWidget>

class CustomDirModel : public QDirModel
{
    Q_OBJECT

public:
    explicit CustomDirModel(QWidget *parent = 0);
    ~CustomDirModel() {}
};

#endif // CUSTOMDIRMODEL_H
