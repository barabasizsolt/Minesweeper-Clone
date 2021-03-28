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
    ~DigitalClock();
    QString getCurrTime();

private slots:
    void showTime();
public slots:
    void stopTimer();
    void startTimer();

private:
    QTimer * timer;
    QTime time;
    QString currTime;
};

#endif // DIGITALCLOCK_H
