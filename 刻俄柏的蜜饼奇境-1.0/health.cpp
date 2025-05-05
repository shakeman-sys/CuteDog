#include "health.h"
#include <QFont>
#include"GameSetting.h"

Health::Health(QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    reset();
}

void Health::reset()
{
    health=3;
    setPlainText("健 康 值 ："+QString::number(health));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("Courier New",GameSetting::Fontsize,QFont::Bold));
    setPos(x(),GameSetting::Fontsize*2);
}

void Health::decrease()
{
    health--;
    setPlainText("健 康 值 ："+QString::number(health));
}
