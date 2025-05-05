#include "boss.h"
#include <QTimerEvent>
#include "GameSetting.h"

Boss::Boss(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/C:/Users/ling/Desktop/resource/image/boss.png"));
    setScale(GameSetting::DropmentScale);
}

void Boss::timerEvent(QTimerEvent *)
{
    setPos(x() + direction * speed, y());

    //碰壁时自动变向
    if (x() <= 0 || x() >= GameSetting::SceneWidth - boundingRect().width()) {
        direction *= -1;
    }
}
