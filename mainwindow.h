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

    QMessageBox *creatinghiringMsgBox;

    void update_combobox();

private slots:

    void on_createHire_clicked();

    void on_comboBox_existed_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
