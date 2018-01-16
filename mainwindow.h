#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QShortcut>
#include <QGroupBox>
#include <QFileInfoList>
#include <QDir>

#include "filesystemwidget.h"
#include "filesystementry.h"
#include "configxmlreader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonQueue_clicked();
    void on_comboBoxExplorerLeft_currentIndexChanged(int index);
    void on_comboBoxExplorerRight_currentIndexChanged(int index);

    void on_buttonSession_clicked();

private:
    Ui::MainWindow *ui;

    FileSystemWidget *modelLeft;
    FileSystemWidget *modelRight;

    QStringList fileSystemList;
    QList<FileSystemEntry *> fileSystemEntryList;

    QString sessionId;

    QString getRandomString(const int length) const;
    QString generateSessionId() const;
    ConfigXmlReader *configXmlReader;
};

#endif // MAINWINDOW_H
