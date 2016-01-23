#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qtsql>
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

    QString selected;

    QMessageBox *creatinghiringMsgBox;
    QMessageBox *updateMsgBox;
    QMessageBox *loadMsgBox;
    QMessageBox *removeMsgBox;

    void update_combobox();
    void bind_values();

private slots:

    void on_createHire_clicked();

    void on_comboBox_existed_currentIndexChanged(const QString &arg1);

    void on_pushButton_update_clicked();


    void on_pushButton_remove_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
