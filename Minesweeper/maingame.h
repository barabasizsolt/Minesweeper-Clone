#ifndef MAINGAME_H
#define MAINGAME_H

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QContextMenuEvent>
#include "grid.h"

class MainGame : public QMainWindow
{
    Q_OBJECT
public:
    MainGame(QWidget * parent = nullptr);
    void createActions();
    void createMenu();

private slots:
    void bGame();
    void iGame();
    void eGame();

private:
    QMenu * gameMenu;
    QAction * beginner;
    QAction * intermediate;
    QAction * expert;
    Grid * game;
    QWidget * widget;
    QVBoxLayout *layout;
};

#endif // MAINGAME_H
