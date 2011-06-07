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
        ui->lblStatus->setText("<span style=\" color:#00ff00;\">Ok!</span>");
    }
    else {
        ui->lblStatus->setText("<span style=\" color:#ff0000;\">Bad!</span>");
//                               ui->lblStatus->setText("<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;">\n<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;"><span style=" color:#ff0000;">Bad!</span></p></body></html>");
    }
}

void MainWindow::on_btnNext_Table_clicked()
{
    Pgdump p(ui->edtUser->text(),ui->edtPass->text(),
             ui->edtHost->text(),ui->edtPort->text().toInt());
    QStringList dbs = p.getDatabases();
    foreach (QString db_s, dbs){
        QTreeWidgetItem *db = new QTreeWidgetItem(ui->tree);
        QTreeWidgetItem *sch = new QTreeWidgetItem(db);
        QTreeWidgetItem *tab = new QTreeWidgetItem(db);
        db->setText(0,db_s);
        sch->setText(0,tr("schema"));
        tab->setText(0,tr("table"));
        QStringList tbls = p.getTables(db_s);
        foreach (QString tbl_s, tbls){
            QTreeWidgetItem *tree = new QTreeWidgetItem(tab);
            tree->setText(0,tbl_s);
        }
        QStringList schs = p.getSchemas(db_s);
        foreach (QString sch_s, schs){
            QTreeWidgetItem *tree = new QTreeWidgetItem(sch);
            tree->setText(0,sch_s);
        }
    }
    ui->tabs->setCurrentIndex(1);
    ui->tree->setFocus();
}
