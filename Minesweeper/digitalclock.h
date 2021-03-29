#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

#include<QObject>
#include<QLCDNumber>
#include<QTimer>
#include<QTime>
#include<QMessageBox>

class DigitalClock : public QLCDNumber
{
    Q_OBJECT

public:
    DigitalClock(QWidget *parent = nullptr);
    virtual ~DigitalClock() { delete timer; };
    int getTime();

private slots:
    void showTime();
public slots:
    void stopTimer();
    void startTimer();
    void resetTimer();

private:
    QTimer * timer;
    int counter = 0;
};

#endif // DIGITALCLOCK_H
