#ifndef FLAGLCD_H
#define FLAGLCD_H

#include<QLCDNumber>
#include<QObject>

class FlagLCD :public QLCDNumber
{
    Q_OBJECT
public:
    FlagLCD(QWidget * parent = nullptr);
    virtual ~FlagLCD() {};
    void setValue(int bombs);
    void decrement();
    void increment();

private:
    int counter = 0;
};

#endif // FLAGLCD_H
