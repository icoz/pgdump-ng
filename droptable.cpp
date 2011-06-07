#include "droptable.h"
#include <QDragMoveEvent>

DropTable::DropTable(QWidget *parent) :
    QTableWidget(parent)
{
    this->setAcceptDrops(true);
    this->setDragDropMode(QAbstractItemView::DropOnly);
    this->setColumnCount(6);
    this->setColumnHidden(5,true); // for save flag "ALL" tables
    //this->setHorizontalHeaderLabels();
//this->setItemDelegateForColumn();
}

void DropTable::dropEvent(QDropEvent *event)
{
    if (event->source() == this && event->possibleActions())
        return;
    if (event->proposedAction() == Qt::CopyAction){
        event->acceptProposedAction();
    }else return;
    if (event->mimeData()->hasText()){
        if (this->columnCount() != 5) return;
        QString d = event->mimeData()->text();
        QStringList sl = d.split(":");
        if (sl.at(0) == "1"){
            //1:db_name:table:table_name
            //1:db_name:schema:sch_name
            QTableWidgetItem *it;
            QString db   = sl.at(1),
                    type = sl.at(2),
                    name = sl.at(3);
            int r = this->rowCount();
            this->setRowCount(r+1);

            it = new QTableWidgetItem(db);
            it->setFlags(Qt::ItemIsEnabled);
            this->setItem(r,0,it);

            it = new QTableWidgetItem(type);
            it->setFlags(Qt::ItemIsEnabled);
            this->setItem(r,1,it);

            it = new QTableWidgetItem(name);
            it->setFlags(Qt::ItemIsEnabled);
            this->setItem(r,2,it);

            it = new QTableWidgetItem();
            it->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
            it->setCheckState(Qt::Checked);
            this->setItem(r,3, it);

            it = new QTableWidgetItem();
            it->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
            it->setCheckState(Qt::Checked);
            this->setItem(r,4, it);
        //for hidden
            if (this->columnCount() == 6){
                it = new QTableWidgetItem();
                it->setFlags(Qt::NoItemFlags);
                this->setItem(r,5, it);
            }
        }else if (sl.at(0) == "2"){
            //2:db_name:schema
            //2:db_name:table
            qDebug("drop type 2");
            QTableWidgetItem *it;
            QString db   = sl.at(1),
                    type = sl.at(2);
                    //name = sl.at(3);
            int r = this->rowCount();
            this->setRowCount(r+1);

            it = new QTableWidgetItem(db);
            it->setFlags(Qt::ItemIsEnabled);
            this->setItem(r,0,it);

            it = new QTableWidgetItem(type);
            it->setFlags(Qt::ItemIsEnabled);
            this->setItem(r,1,it);

            it = new QTableWidgetItem("ALL");
            it->setFlags(Qt::ItemIsEnabled);
            this->setItem(r,2,it);

            it = new QTableWidgetItem();
            it->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
            it->setCheckState(Qt::Checked);
            this->setItem(r,3, it);

            it = new QTableWidgetItem();
            it->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
            it->setCheckState(Qt::Checked);
            this->setItem(r,4, it);
        //for hidden
            if (this->columnCount() == 6){
                it = new QTableWidgetItem("all");
                it->setFlags(Qt::NoItemFlags);
                this->setItem(r,5, it);
            }
        }
    }
    event->acceptProposedAction();
}

void DropTable::dragEnterEvent(QDragEnterEvent *event)
{
    //qDebug("table - dragEnterEvent");
    if (event->mimeData()->hasText())
        event->acceptProposedAction();
}

void DropTable::dragMoveEvent(QDragMoveEvent *event)
{
    //qDebug("table - dragMoveEvent");
    if (event->mimeData()->hasText())
        event->acceptProposedAction();
}
