
#include "custombutton.h"

CustomButton::CustomButton(QWidget *parent):
    QPushButton(parent)
{

}

void CustomButton::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::RightButton){
        emit rightClicked();
    }
    if(e->button() == Qt::LeftButton){
        emit leftClicked();
    }
}
