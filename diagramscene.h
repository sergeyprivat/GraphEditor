#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H


#include "diagramitem.h"

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };

    DiagramScene(QMenu *itemMenu, QObject *parent = 0);

public slots:
    void setMode(Mode mode);
    void setItemType(DiagramItem::DiagramType type);


signals:
    void itemInserted(DiagramItem *item);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    bool isItemChange(int type);

    DiagramItem::DiagramType myItemType;
   QMenu *myItemMenu;
    Mode myMode;
    bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line;

};

#endif // DIAGRAMSCENE_H
