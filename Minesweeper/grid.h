#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGenericMatrix>
#include <QPushButton>
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QMap>
#include <QMessageBox>
#include "custombutton.h"
#include "digitalclock.h"
#include "flaglcd.h"
#include "utils.h"
#include <vector>
#include <cstdlib>
#include <ctime>

class Grid : public QWidget
{
    Q_OBJECT
public:
    Grid(QWidget*parent = nullptr, int rows = 9, int columns = 9, int bombs = 10);

public slots:
    void gameStatus();
    void restartGame();
    void gameOver();
    void gameWon();
    int remainedPositions();
    void placeFlags();

signals:
    void lostTheGame();
    void wonTheGame();

private:
    void setupUI();
    void generateRandom();
    void dfs(int x, int y);
    int countMines(int x, int y);
    bool isSafe(int x, int y);
    bool isMine(int x, int y);
    void printGrid();
    void setPlayGround(bool isOver);

    std::vector<std::vector<int>> grid;
    std::vector<std::vector<int>> visisted;
    int mRows;
    int mCols;
    int totalBombs;

    static int cordX[];
    static int cordY[];

    QHBoxLayout * headerLayout;
    QGridLayout * gridLayout;
    QVBoxLayout * mainLayout;
    DigitalClock * clock;
    QPushButton * restartButton;
    FlagLCD * flagLcd;
    Utils utils;
};

#endif // GRID_H
