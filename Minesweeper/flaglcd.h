#ifndef FLAGLCD_H
#define FLAGLCD_H

#include<QLCDNumber>
#include<QWidget>

class FlagLCD :public QLCDNumber
{
public:
    FlagLCD(QWidget * parent = nullptr);
    void setValue(int bombs);
    void decrement();
    void increment();

private:
    int counter = 0;
};

#endif // FLAGLCD_H
