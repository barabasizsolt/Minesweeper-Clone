#include "digitalclock.h"
#include<QDebug>

DigitalClock::DigitalClock(QWidget *parent)
    : QLCDNumber(parent)
{

    timer = new QTimer(this);
    time = QTime(0, 0, 0);
    timer->setInterval(5);

    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start();
}

DigitalClock::~DigitalClock(){
    delete timer;
}

QString DigitalClock::getCurrTime(){
    return this->currTime;
}

void DigitalClock::showTime(){
    QTime t = time.addMSecs(5);
    if(t.second() == 999){
        time = QTime(0, 0, 0);
    }
    else{
        time = t;
    }
    display(t.toString("ss"));
}

void DigitalClock::stopTimer(){
    timer->stop();
}

void DigitalClock::startTimer(){
    timer->start();
}

void DigitalClock::resetTimer(){
    time = QTime(0, 0, 0);
}
