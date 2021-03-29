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
    auto btn = qobject_cast<CustomButton*>(sender());
    clock->startTimer();

    if( btn != NULL ) {
        if(!btn->icon().isNull()){
            return;
        }
        const int index = gridLayout->indexOf(btn);
        int x,y,z;
        gridLayout->getItemPosition(index,&x,&y,&z,&z);
        dfs(x,y);
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
         btn->setStyleSheet("CustomButton {background-color:#c4bbf0;border:3px outset #999;}");

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
    int ctr = 0;
    for (int i = 0; i < gridLayout->count(); ++i){
      auto widget = gridLayout->itemAt(i)->widget();
      if(widget != NULL && widget->isEnabled()){
          ctr++;
      }
    }
    return ctr;
}

void Grid::placeFlags(){
    CustomButton* btn = qobject_cast<CustomButton*>(sender());
    if( btn != NULL ) {
        const int index = gridLayout->indexOf(btn);
        int x,y,_;
        gridLayout->getItemPosition(index,&x,&y,&_,&_);

        if(btn->icon().isNull()){
            visisted[x][y] = true;
            btn->setIcon(*utils.getFlagIcon());
            btn->setIconSize((*utils.getFlagPixmap()).rect().size() / 12);
            flagLcd->decrement();
        }
        else if(!btn->icon().isNull()){
            visisted[x][y] = false;
            btn->setIcon(QIcon());
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
    QMessageBox::about(this, "Hurra!", "You won the game!\nYour time: " + QString::number(clock->getTime()));
    setPlayGround(false);
}

void Grid::setPlayGround(bool isOver){
for (int i = 0; i < gridLayout->count(); ++i){
    auto widget = gridLayout->itemAt(i)->widget();
    if(widget != NULL){
      widget->setEnabled(false);
      auto btn = qobject_cast<CustomButton*>(widget);
      const int index = gridLayout->indexOf(btn);
      int x,y,_;
      gridLayout->getItemPosition(index,&x,&y,&_,&_);
      if(grid[x][y] == 9){
          if(isOver){
              btn->setIcon(*utils.getMineIcon());
              btn->setIconSize((*utils.getMinePixmap()).rect().size() / 20);
              btn->setStyleSheet("CustomButton {background-color:red;}");
          }
          else{
              btn->setIcon(*utils.getFlagIcon());
              btn->setStyleSheet("CustomButton {background-color:green;}");
          }
      }
    }
  }
}

void Grid::generateRandom(){
    int ctr = 1;
    while(true){
        if(ctr > totalBombs){
            break;
        }
        quint32 x = QRandomGenerator::global()->bounded(0, mCols);
        quint32 y = QRandomGenerator::global()->bounded(0, mCols);
        if(grid[x][y] == 0){
            grid[x][y] = 9;
            ctr++;
        }
    }
}

void Grid::dfs(int x, int y){
    if(grid[x][y] == 9){
        qDebug() << "Bomba!" <<"\n";
        emit lostTheGame();
        return;
    }
    else{
        int ctr = countMines(x,y);
        auto item = gridLayout->itemAtPosition(x, y);
        auto widget = item->widget();
        auto button = dynamic_cast<CustomButton*>(widget);
        if(ctr != 0){
            button->setText(QString::number(ctr));
        }
        button->setStyleSheet("CustomButton {border:1px outset #FFF; background-color:#927fbf;"
                            + utils.getColors(ctr) + "}");
        visisted[x][y] = true;
        button->setEnabled(false);

        if(ctr == 0){
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
    int ctr = 0;
    for(int i = 0; i < 8; i++){
        if(isSafe(x + cordX[i], y + cordY[i])){
            if(isMine(x + cordX[i], y + cordY[i])){
                ctr++;
            }
        }
    }
    return ctr;
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

    //setFixedSize(290,340);
    setFixedSize(490,540);
    //setFixedSize(900,540);

    headerLayout = new QHBoxLayout();
    gridLayout = new QGridLayout();
    mainLayout = new QVBoxLayout();

    clock = new DigitalClock();
    clock->setStyleSheet("DigitalClock {color:white; background-color:#927fbf;}");

    restartButton = new QPushButton();
    restartButton->setFixedSize(50,50);
    restartButton->setIcon(*utils.getSmilyeIcon());
    restartButton->setIconSize((*utils.getSmileyPixmap()).rect().size() / 5);
    restartButton->setStyleSheet("QPushButton {background-color:#c4bbf0;}");

    flagLcd = new FlagLCD;
    flagLcd->setValue(totalBombs);
    flagLcd->setStyleSheet("FlagLCD {color:white; background-color:#927fbf;}");

    for(int i = 0; i < mRows; i++){
        for(int j = 0; j < mCols; j++){
            CustomButton*button = new CustomButton();
            button->setFixedSize(30,30);
            button->setFont(font);
            button->setStyleSheet("CustomButton {background-color:#c4bbf0; border:3px outset #999;}");

            gridLayout->addWidget(button, i, j);
            connect(button, SIGNAL(leftClicked()), this, SLOT(gameStatus()));
            connect(button, SIGNAL(rightClicked()), this, SLOT(placeFlags()));
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
    setStyleSheet("Grid {background-color:#4f3b78;}");

    connect(this, SIGNAL(lostTheGame()), this, SLOT(gameOver()));
    connect(this, SIGNAL(wonTheGame()), this, SLOT(gameWon()));
    connect(restartButton, SIGNAL(clicked()), this, SLOT(restartGame()));
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

