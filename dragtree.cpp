#include "dragtree.h"
#include <QDragMoveEvent>
#include <QApplication>

DragTree::DragTree(QWidget *parent) :
    QTreeWidget(parent)
{
    qDebug("DragTree started");
    this->setDragEnabled(true);
    //this->setAcceptDrops(true);
    this->setDragDropMode(QAbstractItemView::DragOnly);
}

void DragTree::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;

    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance())
      return;
    QTreeWidgetItem *item = this->itemAt(event->pos());
    QString data;
    if (item->parent()){ //if we have at least one parent
        if (item->parent()->parent()){ //we have 2 parent - it's table or schema
            //1:db_name:table:table_name
            //1:db_name:schema:sch_name
            data = "1:"+item->parent()->parent()->text(0)+":";
            data += item->parent()->text(0) +":"+ item->text(0);
        } else { //if we have 1 parent, then we should copy all tables or schemes
            //2:db_name:schema
            //2:db_name:table
            data = "2:"+item->parent()->text(0) +":"+ item->text(0);
        }
    } else {// if we have no parents then user tries to drag db!
        return;
    }

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(data);
    drag->setMimeData(mimeData);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction); // | Qt::MoveAction);
    //qDebug("mouseMoveEvent drag!");

}

void DragTree::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
             dragStartPosition = event->pos();
    QTreeWidget::mousePressEvent(event);
}
