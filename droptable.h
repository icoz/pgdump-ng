#ifndef DROPTABLE_H
#define DROPTABLE_H

#include <QTableWidget>

class DropTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit DropTable(QWidget *parent = 0);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
signals:

public slots:

};

#endif // DROPTABLE_H
