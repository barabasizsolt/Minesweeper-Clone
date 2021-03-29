#include "digitalclock.h"
#include<QDebug>

DigitalClock::DigitalClock(QWidget *parent)
    : QLCDNumber(parent)
{

    timer = new QTimer(this);
    timer->setInterval(1000);

    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
}

int DigitalClock::getTime(){
    return counter;
}

void DigitalClock::showTime(){
    counter += 1;
    display(counter);
}

void DigitalClock::stopTimer(){
    timer->stop();
}

void DigitalClock::startTimer(){
    timer->start();
}

void DigitalClock::resetTimer(){
    counter = 0;
    stopTimer();
    display(counter);
}
