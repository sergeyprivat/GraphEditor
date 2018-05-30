#include "mainwindow.h"
#include "diagramscene.h"
#include "diagramitem.h"

#include <QtWidgets>

MainWindow::MainWindow()

{
    createActions();
    createToolBox();
    createMenus();



    scene = new DiagramScene(itemMenu, this);
    scene->setSceneRect(QRectF(0, 0, 1000, 1000));

    connect(scene, SIGNAL(itemInserted(DiagramItem*)),
                this, SLOT(itemInserted(DiagramItem*)));


    connect(scene, SIGNAL(itemSelected(QGraphicsItem*)),
                this, SLOT(itemSelected(QGraphicsItem*)));

createToolbars();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);

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

void MainWindow::buttonGroupClicked(int id)
{
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
        foreach (QAbstractButton *button, buttons) {
            if (buttonGroup->button(id) != button)
                button->setChecked(false);
        }


            scene->setItemType(DiagramItem::DiagramType(id));
            scene->setMode(DiagramScene::InsertItem);

}

void MainWindow::itemInserted(DiagramItem *item)
{
    pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
        scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
        buttonGroup->button(int(item->diagramType()))->setChecked(false);
}


void MainWindow::itemSelected(QGraphicsItem *item)
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

void MainWindow::createToolbars()
{
    editToolBar = addToolBar(tr("Edit"));
        editToolBar->addAction(deleteAction);


        QToolButton *pointerButton = new QToolButton;
        pointerButton->setCheckable(true);
        pointerButton->setChecked(true);
        pointerButton->setIcon(QIcon(":/Images/pointer.png"));
        QToolButton *linePointerButton = new QToolButton;
        linePointerButton->setCheckable(true);
        linePointerButton->setIcon(QIcon(":/Images/linepointer.png"));

        pointerTypeGroup = new QButtonGroup(this);
        pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
        pointerTypeGroup->addButton(linePointerButton, int(DiagramScene::InsertLine));
        connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
                this, SLOT(pointerGroupClicked(int)));



        pointerToolbar = addToolBar(tr("Pointer type"));
        pointerToolbar->addWidget(pointerButton);
        pointerToolbar->addWidget(linePointerButton);

}

QWidget *MainWindow::createCellWidget(const QString &text, DiagramItem::DiagramType type)
{
    DiagramItem item(type, itemMenu);
    QIcon icon(item.image());

    QToolButton *button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    buttonGroup->addButton(button, int(type));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignHCenter);
    layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

void MainWindow::createActions()
{

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));


    deleteAction = new QAction(QIcon(":/Images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));


    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

}

void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(buttonGroupClicked(int)));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createCellWidget(tr("Conditional"), DiagramItem::Conditional), 0, 0);
    layout->addWidget(createCellWidget(tr("Process"), DiagramItem::Step),0, 1);
    layout->addWidget(createCellWidget(tr("Input/Output"), DiagramItem::Io), 1, 0);
    layout->addWidget(createCellWidget(tr("Circle"),DiagramItem::Circle), 2,0);
    //! [21]

    QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    textButton->setIcon(QIcon(QPixmap(":/Images/textpointer.png")));
    textButton->setIconSize(QSize(50, 50));
    QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
    QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 1, 1);

    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);



    //! [22]
    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tr("Basic Flowchart Shapes"));



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
