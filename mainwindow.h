#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "diagramitem.h"

QT_BEGIN_NAMESPACE
class DiagramScene;
class QGraphicsView;
class QToolBox;
class QAction;
class QButtonGroup;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:
    void buttonGroupClicked(int id);
    void deleteItem();
    void about();

private:
    void createActions();
    void createToolBox();
    void createMenus();

    QWidget *createCellWidget(const QString &text,
                                 DiagramItem::DiagramType type);

    void drawShapes();

    QButtonGroup *buttonGroup;

    DiagramScene *scene;
    QGraphicsView *view;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

    QAction *exitAction;
    QAction *deleteAction;
    QAction *aboutAction;

    QToolBox *toolBox;


};

#endif // MAINWINDOW_H
