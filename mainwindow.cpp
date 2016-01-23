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
    update = new QSqlQuery(connection);

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

void MainWindow::bind_values()
{
    creatinghiring->bindValue(":fn",ui->lineEdit_fullName->text());
    creatinghiring->bindValue(":agee",ui->lineEdit_age->text());
    creatinghiring->bindValue(":resi",ui->lineEdit_residence->text());
    creatinghiring->bindValue(":sal",ui->lineEdit_salary->text());
    creatinghiring->bindValue(":bon",ui->lineEdit_bonuses->text());
    creatinghiring->bindValue(":ins",ui->lineEdit_insurance->text());
    creatinghiring->bindValue(":vac",ui->lineEdit_vacation->text());
    creatinghiring->bindValue(":urg",ui->lineEdit_urgentdays->text());
}

void MainWindow::on_createHire_clicked()
{

    creatinghiring->prepare("INSERT INTO employees (fullname, age, residence, salary, bonuses, insurance, vacation, urgentdays) VALUES (:fn,:agee,:resi,:sal,:bon,:ins,:vac,:urg)");

    bind_values();

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
    QString selected;
    selected = ui->comboBox_existed->currentText();
    loademployees->prepare("SELECT * from employees WHERE fullname='"+selected+"' ");

    loademployees->exec();
    if(loademployees->exec()){
        while(loademployees->next()){
                ui->lineEdit_ID->setText(loademployees->value(0).toString());
                ui->lineEdit_fullName->setText(loademployees->value(1).toString());
                ui->lineEdit_age->setText(loademployees->value(2).toString());
                ui->lineEdit_residence->setText(loademployees->value(3).toString());
                ui->lineEdit_salary->setText(loademployees->value(4).toString());
                ui->lineEdit_bonuses->setText(loademployees->value(5).toString());
                ui->lineEdit_insurance->setText(loademployees->value(6).toString());
                ui->lineEdit_vacation->setText(loademployees->value(7).toString());
                ui->lineEdit_urgentdays->setText(loademployees->value(8).toString());
        }
    }else{
        loadMsgBox = new QMessageBox;
        loadMsgBox->setText("Could not Load employee data.");
        loadMsgBox->exec();
        qDebug() << "loading error:" <<loademployees->lastError();
    }
}

void MainWindow::on_pushButton_update_clicked()
{

    updateMsgBox = new QMessageBox;
    selected = ui->comboBox_existed->currentText();

    update->prepare("UPDATE employees SET fullname=:fn, age=:agee, residence=:resi, salary=:sal, bonuses=:bon, insurance=:ins, vacation=:vac, urgentdays=:urg where fullname='"+selected+"' ");
    update->bindValue(":fn",ui->lineEdit_fullName->text());
    update->bindValue(":agee",ui->lineEdit_age->text());
    update->bindValue(":resi",ui->lineEdit_residence->text());
    update->bindValue(":sal",ui->lineEdit_salary->text());
    update->bindValue(":bon",ui->lineEdit_bonuses->text());
    update->bindValue(":ins",ui->lineEdit_insurance->text());
    update->bindValue(":vac",ui->lineEdit_vacation->text());
    update->bindValue(":urg",ui->lineEdit_urgentdays->text());
    if(update->exec()){
        updateMsgBox->setText("Employee data updated successfully!");
        updateMsgBox->exec();
        update_combobox();
    }else{
        updateMsgBox->setText("Employee data Could not be updated because of an error.");
        updateMsgBox->exec();
        qDebug() << "update error: " << update->lastError();
    }

}



void MainWindow::on_pushButton_remove_clicked()
{
    removeMsgBox = new QMessageBox;
    deleting = new QSqlQuery;
    selected = ui->comboBox_existed->currentText();
    deleting->prepare("DELETE FROM employees WHERE fullname = '"+selected+"' ");


        QMessageBox::StandardButton reply;
        removeMsgBox->setWindowTitle("Delete Validation question");
        reply = QMessageBox::question(this, "Delete confirmation", "Are you sure you want to delete selected employee?", QMessageBox::Yes|QMessageBox::No);

        if(reply==QMessageBox::Yes){
            removeMsgBox->setText("Employee deleted successfully!");
            removeMsgBox->exec();
            deleting->exec();
            update_combobox();
        }else{
            removeMsgBox->close();
        }


}
