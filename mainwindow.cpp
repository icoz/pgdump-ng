#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pgdump.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cbxDataOnly->setVisible(false);
    ui->cbxSchemaOnly->setVisible(false);
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

void MainWindow::on_cbxFormat_currentIndexChanged(int index)
{
    bool f = (index)? false:true;
    ui->cbxDataOnly->setEnabled(f);
    ui->cbxSchemaOnly->setEnabled(f);
    ui->cbxNoOwner->setEnabled(f);
    ui->cbxCreateDB->setEnabled(f);
    ui->cbxDelDB->setEnabled(f);
}

void MainWindow::on_btnRunDump_clicked()
{
    QStringList args;
    args << ((ui->cbxFormat->currentIndex())? ("-Ft") : ("-Fp"));
    if (ui->cbxBLOBs->isChecked()) args << "-b";
    if (ui->cbxColumnInserts->isChecked()) args << "--column-inserts";
    args << QString("-E %1").arg(ui->cbxEnc->currentText());
    args << QString("-f %1").arg(ui->edtFileName->text());
    args << QString("-U %1").arg(ui->edtUser->text());
    args << QString("-h %1").arg(ui->edtHost->text());
    args << QString("-p %1").arg(ui->edtPort->text());
    //args << QString("-t %1").arg(ui->edtFileName->text());
    if (ui->cbxFormat->currentIndex() == 0){
//        if (ui->cbxDataOnly->isChecked()) args << "-a";
//        if (ui->cbxSchemaOnly->isChecked()) args << "-s";
        if (ui->cbxNoOwner->isChecked()) args << "-O";
        if (ui->cbxCreateDB->isChecked()) args << "-C";
        if (ui->cbxDelDB->isChecked()) args << "-c";
    }
    QStringList args2;
    for (int i = 0; i < ui->outTables->rowCount(); i++){
        args2.clear();
        QString dbname = ui->outTables->item(i,0)->data(0).toString();
        QString type   = ui->outTables->item(i,1)->data(0).toString();
        QString name   = ui->outTables->item(i,2)->data(0).toString();
        bool    strct  = ui->outTables->item(i,3)->checkState() == Qt::Checked;
        bool    data   = ui->outTables->item(i,4)->checkState() == Qt::Checked;
        if (type == "table"){
            args2 << "-t "+name;
            if (strct & !data) args2 << "-s";
            if (!strct & data) args2 << "-a";
            if (!strct & !data) continue;
        }else{
            args2 << "-n "+name;
            if (strct & !data) args2 << "-s";
            if (!strct & data) args2 << "-a";
            if (!strct & !data) continue;
        }
        QProcess::startDetached("pg_dump", QStringList() << args << args2 << dbname);

    }
}

void MainWindow::on_tbtnBrowse_clicked()
{
    if (ui->cbxFormat->currentIndex() == 0)
    {
        ui->edtFileName->setText(QFileDialog::getSaveFileName(this, tr("Save File"),"", tr("Plain-dump (*.sql)")));
    }else{
        ui->edtFileName->setText(QFileDialog::getSaveFileName(this, tr("Save File"),"", tr("Tar-dump (*.tar)")));
    }
}
