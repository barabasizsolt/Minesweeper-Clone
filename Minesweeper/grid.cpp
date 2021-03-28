#include "grid.h"
#include <QDebug>

int Grid::cordX[] = { -1, 1, 0,  0, -1,  -1, 1, 1 };
int Grid::cordY[] = { 0, 0,  1, -1, 1, -1, 1, -1 };

Grid::Grid(QWidget*parent, int rows, int columns, int bombs)
    :QWidget(parent)
{
    mRows = rows;
    mCols = columns;
    totalBombs = bombs;

    grid = new int*[mRows];
    visisted = new bool*[mRows];
    for(int i = 0; i < mRows; i++){
        grid[i] = new int[mCols];
        visisted[i] = new bool[mCols];
    }
    setupUI();
    generateRandom();
//    grid[0][3] = 9;
//    grid[1][3] = 9;
//    grid[1][4] = 9;
//    grid[2][7] = 9;
//    grid[3][5] = 9;
//    grid[4][4] = 9;
//    grid[6][3] = 9;
//    grid[5][8] = 9;
//    grid[8][7] = 9;
//    grid[8][4] = 9;
    printGrid();
}

void Grid::gameStatus(){
    CustomButton* btn = qobject_cast<CustomButton*>(sender());
    if( btn != NULL ) {
        if(!btn->icon().isNull()){
            return;
        }
        const int index = gridLayout->indexOf(btn);
        int x,y,z;
        gridLayout->getItemPosition(index,&x,&y,&z,&z);

        dfs(x,y);

        int rPoz = remainedPositions();
        qDebug() << "rPoz: " << rPoz;
        if(rPoz == totalBombs){
            emit wonTheGame();
        }
    }
}

void Grid::gameOver(){
    showBombs();
    clock->stopTimer();
}

void Grid::gameWon(){
    QMessageBox::about(this, "Hurra!", "You won the game!");
}

int Grid::remainedPositions(){
    int ctr = 0;
    for (int i = 0; i < gridLayout->count(); ++i){
      QWidget *widget = gridLayout->itemAt(i)->widget();
      if(widget != NULL && widget->isEnabled()){
          ctr++;
      }
    }
    return ctr;
}

void Grid::placeFlags(){
    CustomButton* btn = qobject_cast<CustomButton*>(sender());
    if( btn != NULL ) {
        QPixmap p1(":/images/flag.png");
        QIcon bt1(p1);

        const int index = gridLayout->indexOf(btn);
        int x,y,z;
        gridLayout->getItemPosition(index,&x,&y,&z,&z);

        if(btn->icon().isNull()){
            visisted[x][y] = true;
            btn->setIcon(bt1);
            btn->setIconSize(p1.rect().size() / 12);
        }
        else if(!btn->icon().isNull()){
            visisted[x][y] = false;
            btn->setIcon(QIcon());
        }
    }
}

void Grid::generateRandom(){
    int ctr = 1;
    while(true){
        if(ctr > 10){
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
        QPixmap pixmap(":/images/mine2.png");
        QIcon ButtonIcon(pixmap);

        QLayoutItem* item = gridLayout->itemAtPosition(x, y);
        QWidget* widget = item->widget();
        CustomButton* button = dynamic_cast<CustomButton*>(widget);
        button->setIcon(ButtonIcon);
        button->setStyleSheet("CustomButton {background-color: red;}");
        button->setIconSize(pixmap.rect().size() / 15);

        qDebug() << "Bomba!" <<"\n";
        emit lostTheGame();
        return;
    }
    else{
        int ctr = countMines(x,y);

        QLayoutItem* item = gridLayout->itemAtPosition(x, y);
        QWidget* widget = item->widget();
        CustomButton* button = dynamic_cast<CustomButton*>(widget);
        if(ctr != 0){
            button->setText(QString::number(ctr));
            button->setStyleSheet(numberColors[ctr]);
        }
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

void Grid::printGrid(){
    QDebug dbg(QtDebugMsg);
    for(int i = 0; i < mRows; i++){
        for(int j = 0; j < mCols; j++){
           dbg << grid[i][j];
        }
        dbg << "\n";
    }
}

void Grid::showBombs(){
    QPixmap pixmap(":/images/mine2.png");
    QIcon ButtonIcon(pixmap);

    for(int i =0; i < mRows; i++){
        for(int j=  0; j < mCols; j++){
            QLayoutItem* item = gridLayout->itemAtPosition(i, j);
            QWidget* widget = item->widget();
            CustomButton* button = dynamic_cast<CustomButton*>(widget);
            if(grid[i][j] == 9){
                button->setIcon(ButtonIcon);
                button->setIconSize(pixmap.rect().size() / 15);
            }
            button->setEnabled(false);
        }
    }
}

void Grid::setupUI(){
    QFont font;
    font.setWeight(QFont::ExtraBold);
    font.setPixelSize(23);

    numberColors.insert(1, "CustomButton {color: blue;}");
    numberColors.insert(2, "CustomButton {color: green;}");
    numberColors.insert(3, "CustomButton {color: red;}");
    numberColors.insert(4, "CustomButton {color: purple;}");
    numberColors.insert(5, "CustomButton {color: maroon;}");
    numberColors.insert(6, "CustomButton {color: turquoise;}");
    numberColors.insert(7, "CustomButton {color: black;}");
    numberColors.insert(8, "CustomButton {color: gray;}");

    setFixedSize(430,520);

    headerLayout = new QHBoxLayout();
    gridLayout = new QGridLayout();
    mainLayout = new QVBoxLayout();
    clock = new DigitalClock();
    restartButton = new QPushButton();
    restartButton->setFixedSize(45,45);

    for(int i = 0; i < mRows; i++){
        for(int j = 0; j < mCols; j++){
            CustomButton*button = new CustomButton(this);
            button->setFixedSize(45,45);
            button->setFont(font);
            gridLayout->addWidget(button, i, j);
            connect(button, SIGNAL(leftClicked()), this, SLOT(gameStatus()));
            connect(button, SIGNAL(rightClicked()), this, SLOT(placeFlags()));
            grid[i][j] = 0;
            visisted[i][j] = false;
        }
    }

    headerLayout->addWidget(restartButton);
    headerLayout->addWidget(clock);

    gridLayout->setSpacing(0);
    mainLayout->addLayout(headerLayout);
    mainLayout->addLayout(gridLayout);
    setLayout(mainLayout);

    connect(this, SIGNAL(lostTheGame()), this, SLOT(gameOver()));
    connect(this, SIGNAL(wonTheGame()), this, SLOT(gameWon()));
}
