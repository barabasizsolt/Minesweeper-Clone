#include "maingame.h"

MainGame::MainGame(QWidget * parent):
    QMainWindow(parent){

    setFixedSize(310,380);

    game = new Grid;
    widget = new QWidget;
    setCentralWidget(widget);

    layout = new QVBoxLayout;
    layout->addWidget(game);

    widget->setLayout(layout);
    widget->setStyleSheet("background-color:#4f3b78");

    createActions();
    createMenu();
}

void MainGame::createActions(){
    beginner = new QAction(tr("&Beginner"), this);
    intermediate = new QAction(tr("&Intermediate"), this);
    expert = new QAction(tr("&Expert"), this);

    connect(beginner, &QAction::triggered, this, &MainGame::bGame);
    connect(intermediate, &QAction::triggered, this, &MainGame::iGame);
    connect(expert, &QAction::triggered, this, &MainGame::eGame);
}

void MainGame::createMenu(){
    gameMenu = menuBar()->addMenu(tr("&Difficulty Level"));
    gameMenu->addAction(beginner);
    gameMenu->addAction(intermediate);
    gameMenu->addAction(expert);
}

void MainGame::bGame(){
    layout->removeWidget(game);
    delete game;
    game = new Grid;
    layout->addWidget(game);
    setFixedSize(310,380);
}

void MainGame::iGame(){
    layout->removeWidget(game);
    delete game;
    game = new Grid(this, 16, 16, 40);
    layout->addWidget(game);
    setFixedSize(510,580);
}

void MainGame::eGame(){
    layout->removeWidget(game);
    delete game;
    game = new Grid(this, 16, 30, 90);
    layout->addWidget(game);
    setFixedSize(920,580);
}
