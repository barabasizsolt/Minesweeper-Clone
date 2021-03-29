#ifndef UTILS_H
#define UTILS_H

#include <QPixmap>
#include <QIcon>
#include <QMap>

class Utils
{
public:
    Utils();
    ~Utils();
    QIcon *getFlagIcon();
    QIcon* getInjuredIcon();
    QIcon* getMineIcon();
    QIcon* getSmilyeIcon();
    QPixmap* getFlagPixmap();
    QPixmap* getInjuredPixmap();
    QPixmap* getMinePixmap();
    QPixmap* getSmileyPixmap();
    QString getColors(int ctr);
private:
    QPixmap *flagPixmap;
    QIcon *flagIcon;
    QPixmap *injuredPixmap;
    QIcon *injuredIcon;
    QPixmap *minePixmap;
    QIcon *mineIcon;
    QPixmap *smileyPixmap;
    QIcon *smileyIcon;
    QMap <int, QString> numberColors;
};

#endif // UTILS_H
