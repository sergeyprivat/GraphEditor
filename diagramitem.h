#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPixmapItem>
#include <QList>

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsItem;
class QGraphicsScene;
class QWidget;
class QPolygonF;
QT_END_NAMESPACE


class DiagramItem : public QGraphicsPolygonItem
{
public:
     enum DiagramType { Step, Conditional, StartEnd, Io, Circle};
    DiagramItem(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent = 0);

     DiagramType diagramType() const { return myDiagramType; }

     QPixmap image() const;


private:
     DiagramType myDiagramType;
        QPolygonF myPolygon;
        QMenu *myContextMenu;
};

#endif // DIAGRAMITEM_H
