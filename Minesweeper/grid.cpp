#include <utils.h>
#include "grid.h"
#include <QDebug>

int Grid::cordX[] = { -1, 1, 0,  0, -1,  -1, 1, 1 };
int Grid::cordY[] = { 0, 0,  1, -1, 1, -1, 1, -1 };

Grid::Grid(QWidget*parent, int rows, int columns, int bombs)
    :QWidget(parent), mRows(rows), mCols(columns), totalBombs(bombs){

    grid.resize(mRows);
    visisted.resize(mRows);
    for (int i = 0; i < mRows; ++i){
        grid[i].resize(mCols);
        visisted[i].resize(mCols);
    }
    setupUI();
    generateRandom();
    printGrid();
}

void Grid::gameStatus(){
    auto button = qobject_cast<CustomButton*>(sender());
    clock->startTimer();

    if( button != NULL ) {
        if(!button->icon().isNull()){
            return;
        }
        Position position = utils.getCurrentPosition(button, gridLayout);
        dfs(position.x, position.y);
        if(remainedPositions() == totalBombs){
            emit wonTheGame();
        }
    }
}

void Grid::restartGame(){
    restartButton->setIcon(*utils.getSmilyeIcon());

    for(int i = 0; i < mRows; i++){
        for(int j = 0; j < mCols; j++){
            grid[i][j] = 0;
            visisted[i][j] = false;
        }
    }

    generateRandom();

    for (int i = 0; i < gridLayout->count(); ++i){
      auto widget = gridLayout->itemAt(i)->widget();
      auto btn = qobject_cast<CustomButton*>(widget);
      if(btn != NULL){
         btn->setEnabled(true);
         btn->setStyleSheet("CustomButton {background-color:#c4bbf0;border:3px outset #999}");

         if(!btn->icon().isNull()){
            btn->setIcon(QIcon());
         }
         if(!btn->text().isEmpty()){
            btn->setText("");
         }
      }
    }

    flagLcd->setValue(totalBombs);
    clock->resetTimer();
    printGrid();
}

int Grid::remainedPositions(){
    int counter = 0;
    for (int i = 0; i < gridLayout->count(); ++i){
        auto widget = gridLayout->itemAt(i)->widget();
        if(widget != NULL && widget->isEnabled()){
              counter++;
        }
    }
    return counter;
}

void Grid::placeFlags(){
    CustomButton* button = qobject_cast<CustomButton*>(sender());
    if( button != NULL ) {
        Position position = utils.getCurrentPosition(button, gridLayout);

        if(button->icon().isNull()){
            visisted[position.x][position.y] = true;
            button->setIcon(*utils.getFlagIcon());
            button->setIconSize((*utils.getFlagPixmap()).rect().size() / 12);
            flagLcd->decrement();
        }
        else if(!button->icon().isNull()){
            visisted[position.x][position.y] = false;
            button->setIcon(QIcon());
            flagLcd->increment();
        }
    }
}

void Grid::gameOver(){
    clock->stopTimer();
    restartButton->setIcon(*utils.getInjuredIcon());
    setPlayGround(true);
}

void Grid::gameWon(){
    clock->stopTimer();
    setPlayGround(false);
    restartButton->setIcon(*utils.getSunglassIcon());
}

void Grid::setPlayGround(bool isOver){
    for (int i = 0; i < gridLayout->count(); ++i){
        auto widget = gridLayout->itemAt(i)->widget();
        if(widget != NULL){
            widget->setEnabled(false);
            auto button = qobject_cast<CustomButton*>(widget);
            Position position = utils.getCurrentPosition(button, gridLayout);
            if(grid[position.x][position.y] == 9){
                if(isOver){
                    button->setIcon(*utils.getMineIcon());
                    button->setIconSize((*utils.getMinePixmap()).rect().size() / 20);
                    button->setStyleSheet("CustomButton {background-color:red}");
                }
                else{
                    button->setIcon(*utils.getFlagIcon());
                    button->setStyleSheet("CustomButton {background-color:green}");
                }
            }
        }
    }
}

void Grid::generateRandom(){
    srand((unsigned)time(0));

    int ctr = 1;
    while(true){
        if(ctr > totalBombs){
            break;
        }
        int x = rand() % mRows;
        int y = rand() % mCols;
        if(grid[x][y] == 0){
            grid[x][y] = 9;
            ctr++;
        }
    }
}

void Grid::dfs(int x, int y){
    if(grid[x][y] == 9){
        emit lostTheGame();
        return;
    }
    else{
        int mines = countMines(x,y);
        auto item = gridLayout->itemAtPosition(x, y);
        auto widget = item->widget();
        auto button = dynamic_cast<CustomButton*>(widget);
        if(mines != 0){
            button->setText(QString::number(mines));
        }
        button->setStyleSheet("CustomButton {border:1px outset #FFF; background-color:#927fbf;"
                            + utils.getColors(mines));
        visisted[x][y] = true;
        button->setEnabled(false);

        if(mines == 0){
            for(int i = 0; i < 8; i++){
                if(isSafe(x + cordX[i], y + cordY[i]) && !visisted[x + cordX[i]][y + cordY[i]]){
                    if(!isMine(x + cordX[i], y + cordY[i])){
                        dfs(x + cordX[i], y + cordY[i]);
                    }
                }
            }
        }
        return;
    }
}

int Grid::countMines(int x, int y){
    int counter = 0;
    for(int i = 0; i < 8; i++){
        if(isSafe(x + cordX[i], y + cordY[i])){
            if(isMine(x + cordX[i], y + cordY[i])){
                counter++;
            }
        }
    }
    return counter;
}

bool Grid::isSafe(int x, int y){
    return (x >= 0) && (x < mRows) && (y >= 0) && (y < mCols);
}

bool Grid::isMine(int x, int y){
    return grid[x][y] == 9;
}

void Grid::setupUI(){
    QFont font;
    font.setWeight(QFont::ExtraBold);
    font.setPixelSize(23);

    headerLayout = new QHBoxLayout;
    gridLayout = new QGridLayout;
    mainLayout = new QVBoxLayout;

    clock = new DigitalClock;
    clock->setStyleSheet("DigitalClock {color:white; background-color:#927fbf}");

    restartButton = new QPushButton;
    restartButton->setFixedSize(50,50);
    restartButton->setIcon(*utils.getSmilyeIcon());
    restartButton->setIconSize((*utils.getSmileyPixmap()).rect().size() / 5);
    restartButton->setStyleSheet("QPushButton {background-color:#c4bbf0;}");

    flagLcd = new FlagLCD;
    flagLcd->setValue(totalBombs);
    flagLcd->setStyleSheet("FlagLCD {color:white; background-color:#927fbf}");

    for(int i = 0; i < mRows; i++){
        for(int j = 0; j < mCols; j++){
            CustomButton*button = new CustomButton;
            button->setFixedSize(30,30);
            button->setFont(font);
            button->setStyleSheet("CustomButton {background-color:#c4bbf0; border:3px outset #999}");

            gridLayout->addWidget(button, i, j);
            connect(button, &CustomButton::leftClicked, this, &Grid::gameStatus);
            connect(button, &CustomButton::rightClicked, this, &Grid::placeFlags);
            grid[i][j] = 0;
            visisted[i][j] = false;
        }
    }

    headerLayout->addWidget(flagLcd);
    headerLayout->addWidget(restartButton);
    headerLayout->addWidget(clock);

    gridLayout->setSpacing(0);
    mainLayout->addLayout(headerLayout);
    mainLayout->addLayout(gridLayout);
    setLayout(mainLayout);
    setStyleSheet("Grid {background-color:#4f3b78}");

    connect(this, &Grid::lostTheGame, this, &Grid::gameOver);
    connect(this, &Grid::wonTheGame, this, &Grid::gameWon);
    connect(restartButton, &QPushButton::clicked, this, &Grid::restartGame);
}

void Grid::printGrid(){
    QDebug dbg(QtDebugMsg);
    for(int i = 0; i < mRows; i++){
        for(int j = 0; j < mCols; j++){
           dbg << grid[i][j];
        }
        dbg << "\n";
    }
}

