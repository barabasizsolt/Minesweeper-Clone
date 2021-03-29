#include "utils.h"

Utils::Utils(){
    flagPixmap = new QPixmap(":/images/flag.png");
    flagIcon = new QIcon(*flagPixmap);
    injuredPixmap = new QPixmap(":/images/injured_emoji.png");
    injuredIcon = new QIcon(*injuredPixmap);
    minePixmap = new QPixmap(":/images/mine2.png");
    mineIcon = new QIcon(*minePixmap);
    smileyPixmap = new QPixmap(":/images/smile_emoji.png");
    smileyIcon = new QIcon(*smileyPixmap);

    numberColors.insert(0, "color: none; font-family:Comic Sans MS;}");
    numberColors.insert(1, "color: blue; font-family:Comic Sans MS;}");
    numberColors.insert(2, "color: green; font-family:Comic Sans MS;}");
    numberColors.insert(3, "color: red; font-family:Comic Sans MS;}");
    numberColors.insert(4, "color: purple; font-family:Comic Sans MS;}");
    numberColors.insert(5, "color: maroon; font-family:Comic Sans MS;}");
    numberColors.insert(6, "color: turquoise; font-family:Comic Sans MS;}");
    numberColors.insert(7, "color: black; font-family:Comic Sans MS;}");
    numberColors.insert(8, "color: gray; font-family:Comic Sans MS;}");
}

Utils::~Utils(){
    delete flagPixmap;
    delete flagIcon;
    delete injuredPixmap;
    delete injuredIcon;
    delete minePixmap;
    delete mineIcon;
    delete smileyPixmap;
    delete smileyIcon;
}

QIcon *Utils::getFlagIcon(){
    return flagIcon;
}

QIcon *Utils::getInjuredIcon(){
    return injuredIcon;
}

QIcon *Utils::getMineIcon(){
    return mineIcon;
}

QIcon *Utils::getSmilyeIcon(){
    return smileyIcon;
}

QPixmap *Utils::getFlagPixmap(){
    return flagPixmap;
}

QPixmap *Utils::getInjuredPixmap(){
     return injuredPixmap;
}

QPixmap *Utils::getMinePixmap(){
    return minePixmap;
}

QPixmap *Utils::getSmileyPixmap(){
    return smileyPixmap;
}

QString Utils::getColors(int ctr){
    return numberColors[ctr];
}
