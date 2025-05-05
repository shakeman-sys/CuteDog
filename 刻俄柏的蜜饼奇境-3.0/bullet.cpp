#include "bullet.h"
#include "GameSetting.h"
#include <QGraphicsScene>

Bullet::Bullet(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    //创造bullet
    setPixmap(QPixmap(":/C:/Users/ling/Desktop/resource/image/bullet.png"));
    this->setScale(GameSetting::BulletScale);
    startTimer(GameSetting::BulletTimer);
}

void Bullet::timerEvent(QTimerEvent *)
{
    //保证bullet出画面后删除
    setPos(x(), y() - GameSetting::BulletSpeed);
    if (y() + boundingRect().height() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}
