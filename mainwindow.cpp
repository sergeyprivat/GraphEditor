#include "mainwindow.h"
#include "diagramscene.h"

#include <QtWidgets>

MainWindow::MainWindow()

{
    createActions();
    createMenus();


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

void MainWindow::deleteItem()
{

}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Diagram Scene"),
                       tr("The <b>Diagram Scene</b> example shows "
                          "use of the graphics framework."));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction(deleteAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::createActions()
{

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));


    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));


    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));



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
