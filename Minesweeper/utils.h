#ifndef UTILS_H
#define UTILS_H

#include <QPixmap>
#include <QIcon>
#include <QMap>
#include <QGridLayout>
#include "custombutton.h"

struct Position{
    int x;
    int y;
};

class Utils{

public:
    Utils();
    ~Utils();
    QIcon *getFlagIcon();
    QIcon* getInjuredIcon();
    QIcon* getMineIcon();
    QIcon* getSmilyeIcon();
    QPixmap *getSunglassIcon();
    QPixmap* getFlagPixmap();
    QPixmap* getInjuredPixmap();
    QPixmap* getMinePixmap();
    QPixmap* getSmileyPixmap();
    QPixmap *getSunglassPixmap();
    QString getColors(int ctr);
    Position getCurrentPosition(QWidget* widget, QGridLayout* layout);

private:
    QPixmap *flagPixmap;
    QIcon *flagIcon;
    QPixmap *injuredPixmap;
    QIcon *injuredIcon;
    QPixmap *minePixmap;
    QIcon *mineIcon;
    QPixmap *smileyPixmap;
    QIcon *smileyIcon;
    QPixmap *sunglassPixmap;
    QIcon *sunglassIcon;
    QMap <int, QString> numberColors;
};

#endif // UTILS_H
