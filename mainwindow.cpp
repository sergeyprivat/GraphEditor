#include "mainwindow.h"
#include "diagramscene.h"

#include <QtWidgets>

MainWindow::MainWindow()

{

    scene = new DiagramScene(this);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));

    QHBoxLayout *layout = new QHBoxLayout;

    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("Diagramscene"));
    setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow()
{

}
