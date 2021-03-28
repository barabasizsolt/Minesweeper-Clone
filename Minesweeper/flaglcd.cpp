#include "flaglcd.h"

FlagLCD::FlagLCD(QWidget *parent):
    QLCDNumber(parent){
}

void FlagLCD::setValue(int bombs){
    counter = bombs;
    display(counter);
}

void FlagLCD::decrement(){
    counter--;
    display(counter);
}

void FlagLCD::increment(){
    counter++;
    display(counter);
}
