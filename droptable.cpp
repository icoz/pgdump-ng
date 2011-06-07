#include "droptable.h"
#include <QDragMoveEvent>

DropTable::DropTable(QWidget *parent) :
    QTableWidget(parent)
{
    this->setAcceptDrops(true);
    this->setDragDropMode(QAbstractItemView::DropOnly);
}

void DropTable::dropEvent(QDropEvent *event)
{
    qDebug("table - dropEvent");
    if (event->source() == this && event->possibleActions())
        return;
    qDebug("table - dropEvent 1");
    if (event->proposedAction() == Qt::CopyAction){
        event->acceptProposedAction();
    }else return;
    qDebug("table - dropEvent 2");
    if (event->mimeData()->hasText()){
        QString d = event->mimeData()->text();
        qDebug(d.toAscii().data());
    }
    event->acceptProposedAction();
}

void DropTable::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug("table - dragEnterEvent");
    if (event->mimeData()->hasText())
        event->acceptProposedAction();
}

void DropTable::dragMoveEvent(QDragMoveEvent *event)
{
    //qDebug("table - dragMoveEvent");
    //event->acceptProposedAction();
}
