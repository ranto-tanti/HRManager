#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDialog>
#include <QString>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connection = QSqlDatabase::addDatabase("QSQLITE");
    connection.setDatabaseName("D:/Qt/Projects/HRManager/Database");
    bool db_ok = connection.open();

    creation = new QSqlQuery(connection);
    creatinghiring = new QSqlQuery(connection);
    loademployees = new QSqlQuery(connection);
    bringdata = new QSqlQuery(connection);

    creation->exec("CREATE TABLE IF NOT EXISTS employees"
                   "(id integer primary key AUTOINCREMENT,"
                   "fullname varchar(80) DEFAULT NULL,"
                   "age integer DEFAULT NULL,"
                   "residence varchar(100) DEFAULT NULL,"
                   "salary integer DEFAULT NULL,"
                   "bonuses integer DEFAULT NULL,"
                   "insurance integer DEFAULT NULL,"
                   "vacation integer DEFAULT NULL,"
                   "urgentdays integer DEFAULT NULL)");

    if(db_ok){
        ui->label->setText("sundethika");
    }
    if(db_ok){

        ui->label_2->setText("einai akoma anoixto");
    }
    else{ ui->label_2->setText("ekleise ok !");}


    update_combobox();

}

MainWindow::~MainWindow()
{
    delete ui;
    connection.close();
}

void MainWindow::update_combobox()
{
    QSqlQueryModel *loader = new QSqlQueryModel;
    QSqlQuery *loading = new QSqlQuery(connection);
    loading->prepare("SELECT fullname FROM employees");
    loading->exec();
    loader->setQuery(*loading);
    ui->comboBox_existed->setModel(loader);
}

void MainWindow::on_createHire_clicked()
{

    creatinghiring->prepare("INSERT INTO employees (fullname, age, residence, salary, bonuses, insurance, vacation, urgentdays) VALUES (:fn,:agee,:resi,:sal,:bon,:ins,:vac,:urg)");

    creatinghiring->bindValue(":fn",ui->lineEdit_fullName->text());
    creatinghiring->bindValue(":agee",ui->lineEdit_age->text());
    creatinghiring->bindValue(":resi",ui->lineEdit_residence->text());
    creatinghiring->bindValue(":sal",ui->lineEdit_salary->text());
    creatinghiring->bindValue(":bon",ui->lineEdit_bonuses->text());
    creatinghiring->bindValue(":ins",ui->lineEdit_insurance->text());
    creatinghiring->bindValue(":vac",ui->lineEdit_vacation->text());
    creatinghiring->bindValue(":urg",ui->lineEdit_urgentdays->text());

    creatinghiringMsgBox = new QMessageBox;
    creatinghiringMsgBox->setWindowTitle("Creation problem");
    creatinghiringMsgBox->setStandardButtons(QMessageBox::Ok);

    if(!ui->lineEdit_fullName->text().isEmpty() &&
            !ui->lineEdit_age->text().isEmpty() &&
            !ui->lineEdit_residence->text().isEmpty() &&
            creatinghiring->exec()  ){

        creatinghiringMsgBox->setText("New employee is hired and added to our database!");
        creatinghiringMsgBox->exec();
        ui->lineEdit_fullName->clear();
        ui->lineEdit_age->clear();
        ui->lineEdit_residence->clear();
        ui->lineEdit_salary->clear();
        ui->lineEdit_bonuses->clear();
        ui->lineEdit_insurance->clear();
        ui->lineEdit_vacation->clear();
        ui->lineEdit_urgentdays->clear();

        update_combobox();

    } else {

        qDebug() <<"creating | hiring error"<< creatinghiring->lastError();
        creatinghiringMsgBox->setText("Could not create new employee in database. Please fill the required fealds to create new employee instance.");
        creatinghiringMsgBox->exec();
    }

}


void MainWindow::on_comboBox_existed_currentIndexChanged(const QString &arg1)
{
    QString selectedemployee=ui->comboBox_existed->currentText();
    bringdata->exec("SELECT * FROM employees WHERE fullname='"+selectedemployee+"' ");
}

