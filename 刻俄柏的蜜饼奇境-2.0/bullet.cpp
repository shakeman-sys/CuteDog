#include "bullet.h"
#include "GameSetting.h"
#include <QGraphicsScene>

Bullet::Bullet(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/C:/Users/ling/Desktop/resource/image/bullet.png"));
    this->setScale(GameSetting::BulletScale);
    startTimer(GameSetting::BulletTimer);
}

void Bullet::timerEvent(QTimerEvent *)
{
    setPos(x(), y() - GameSetting::BulletSpeed);
    if (y() + boundingRect().height() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}
