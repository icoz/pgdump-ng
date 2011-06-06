#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pgdump.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::on_pushButton_clicked()
{
    Pgdump p;
    ui->textEdit->append(p.getDatabases().join("\n"));
    ui->textEdit->append("---------");
    ui->textEdit->append("tables of 'somebase':");
    ui->textEdit->append(p.getTables("somebase").join("\n"));
}//*/

void MainWindow::on_edtPass_returnPressed()
{
    Pgdump p(ui->edtUser->text(),ui->edtPass->text(),
             ui->edtHost->text(),ui->edtPort->text().toInt());
    if (p.tryOpen()){
        ui->lblStatus->setText("Ok!");
    }
    else {
        ui->lblStatus->setText("Bad!");
    }
}
