#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class CustomButton : public QPushButton
{
        Q_OBJECT
public:
    explicit CustomButton(QWidget * parent = nullptr);

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void rightClicked();
    void leftClicked();
};

#endif // CUSTOMBUTTON_H
