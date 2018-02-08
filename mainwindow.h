#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QCloseEvent>
#include <QShortcut>
#include <QDateTime>
#include <QThread>
#include <QTimer>

#include <QDebug>

#include "filesystem/panelwidget.h"
#include "filesystem/operationcalculator.h"
#include "filesystem/operationcalculatorwidget.h"
#include "filesystem/operationcopydialogwidget.h"
#include "filesystem/operationcopywidget.h"
#include "filesystem/operationcopy.h"

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
    void on_buttonProperties_clicked();
    void on_buttonCopy_clicked();
    void on_buttonMove_clicked();
    void on_buttonCatalogue_clicked();
    void on_buttonDelete_clicked();
    void on_buttonQuit_clicked();
    void on_buttonSession_clicked();

    void showPanelBoxLeft();
    void showPanelBoxRight();

    void setCurrentPanel(PanelWidget *widget);
    void itemChanged();

    void readError(QString path);

private:
    Ui::MainWindow *ui;

    QString sessionId;

    PanelWidget *panelLeft;
    PanelWidget *panelRight;

    PanelWidget *activePanel;
    PanelWidget *passivePanel;

    QString getRandomString(const int length) const;
    QString generateSessionId() const;


protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
