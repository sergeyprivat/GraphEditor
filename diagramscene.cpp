#include "diagramscene.h"
#include <QGraphicsSceneMouseEvent>

DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent): QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    myMode = MoveItem;
    myItemType = DiagramItem::Step;
    line = 0;

}

void DiagramScene::setMode(DiagramScene::Mode mode)
{
    myMode = mode;
}

void DiagramScene::setItemType(DiagramItem::DiagramType type)
{
    myItemType = type;
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    DiagramItem *item;
    switch (myMode) {
    case InsertItem:
        item = new DiagramItem(myItemType, myItemMenu);
        // item->setBrush(myItemColor);
        addItem(item);
        item->setPos(mouseEvent->scenePos());
        emit itemInserted(item);
        break;
        //! [6] //! [7]
    case InsertLine:
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                            mouseEvent->scenePos()));
        // line->setPen(QPen(myLineColor, 2));
        addItem(line);
        break;
        //! [7] //! [8]
    case InsertText:
        /*
               textItem = new DiagramTextItem();
               textItem->setFont(myFont);
               textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
               textItem->setZValue(1000.0);
               connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
                       this, SLOT(editorLostFocus(DiagramTextItem*)));
               connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
                       this, SIGNAL(itemSelected(QGraphicsItem*)));
               addItem(textItem);
               textItem->setDefaultTextColor(myTextColor);
               textItem->setPos(mouseEvent->scenePos());
               emit textInserted(textItem);
               */
        //! [8] //! [9]
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (line != 0 && myMode == InsertLine) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;


    }

    line = 0;
}

bool DiagramScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
            if (item->type() == type)
                return true;
        }
        return false;
}
