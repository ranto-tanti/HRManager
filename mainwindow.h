#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QString>
#include <QSqlQueryModel>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSqlDatabase connection;

    QSqlQuery *creation;
    QSqlQuery *creatinghiring;
    QSqlQuery *loademployees;
    QSqlQueryModel *modal;
    QSqlQuery *bringdata;
    QSqlQuery *update;
    QSqlQuery *deleting;

    QSqlQuery *counter;
    QSqlQuery *totalsalary;
    QSqlQuery *totalinsurance;
    QSqlQuery *totalbonuses;

    QString selected;
    QString selectedPresence;

    QMessageBox *creatinghiringMsgBox;
    QMessageBox *updateMsgBox;
    QMessageBox *loadMsgBox;
    QMessageBox *removeMsgBox;

    void update_combobox();
    void bind_values();
    void clear_entries();

private slots:

    void on_createHire_clicked();

    void on_comboBox_existed_currentIndexChanged(const QString &arg1);

    void on_pushButton_update_clicked();

    void on_pushButton_remove_clicked();

    void on_clearEntries_clicked();

    void on_comboBox_existed_presence_currentIndexChanged(const QString &arg1);

    void on_actionClose_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
