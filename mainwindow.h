#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class DiagramScene;
class QGraphicsView;
class QAction;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:
    void deleteItem();
    void about();

private:
    void createMenus();
    void createActions();

    void drawShapes();


    DiagramScene *scene;
    QGraphicsView *view;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

    QAction *exitAction;
    QAction *deleteAction;
    QAction *aboutAction;


};

#endif // MAINWINDOW_H
