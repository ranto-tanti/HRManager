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

    QSqlDatabase connection;

    QSqlQuery *creation;
    QSqlQuery *creatinghiring;
    QSqlQuery *loademployees;
    QSqlQueryModel *modal;
    QSqlQuery *bringdata;


   QMessageBox *creatinghiringMsgBox;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_createHire_clicked();

    void on_refreshExistedButton_clicked();

    void on_comboBox_existed_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
