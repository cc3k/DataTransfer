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

#include "copyfile.h"
#include "filesystemdirread.h"
#include "filesystemdirreaddialog.h"
#include "filesystemdircreatedialog.h"


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
    void on_comboBoxExplorer1_currentIndexChanged(int index);
    void on_comboBoxExplorer2_currentIndexChanged(int index);

    void on_buttonCopy_clicked();
    void on_buttonMove_clicked();
    void on_buttonCatalogue_clicked();
    void on_buttonDelete_clicked();
    void on_buttonQuit_clicked();
    void on_buttonSession_clicked();

    //фуфло, отсюда убрать
    void getData(QStringList data);
    void tst();

private:
    Ui::MainWindow *ui;

    FileSystemWidget *model1;
    FileSystemWidget *model2;

    QList<FileSystemEntry *> fileSystemEntryList;

    QString sessionId;

    QString getRandomString(const int length) const;
    QString generateSessionId() const;

};

#endif // MAINWINDOW_H
