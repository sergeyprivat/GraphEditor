#include "mainwindow.h"
#include "diagramscene.h"

#include <QtWidgets>

MainWindow::MainWindow()

{

    scene = new DiagramScene(this);
    scene->setSceneRect(QRectF(0, 0, 1000, 1000));

    QHBoxLayout *layout = new QHBoxLayout;

    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("Diagramscene"));
    setUnifiedTitleAndToolBarOnMac(true);

drawShapes();
}

MainWindow::~MainWindow()
{

}

void MainWindow::drawShapes()
{
    Qt::PenStyle style = Qt::PenStyle(2);

   QGraphicsLineItem * line = new QGraphicsLineItem(20, 20,
                                            500, 500);
              line->setPen(QPen(Qt::blue, 5, style ));

                scene->addItem(line);

                QGraphicsEllipseItem * ellipse = new QGraphicsEllipseItem(200, 200, 50, 50);
                 scene->addItem(ellipse);

}
