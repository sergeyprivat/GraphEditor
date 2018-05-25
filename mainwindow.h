#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DiagramScene;
class QGraphicsView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    DiagramScene *scene;
    QGraphicsView *view;

};

#endif // MAINWINDOW_H
