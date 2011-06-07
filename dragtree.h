#ifndef DRAGTREE_H
#define DRAGTREE_H

#include <QTreeWidget>

class DragTree : public QTreeWidget
{
    Q_OBJECT
public:
    explicit DragTree(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:

public slots:
private:
    QPoint dragStartPosition;
};

#endif // DRAGTREE_H
