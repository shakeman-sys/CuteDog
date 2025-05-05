#include "cat.h"
#include <QTimerEvent>
#include "GameSetting.h"
#include "dog.h"
#include "health.h"
#include <QRandomGenerator>


Cat::Cat(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    //创造Cat
    setPixmap(QPixmap(":/C:/Users/ling/Desktop/resource/image/mon3tr.png"));
    setScale(GameSetting::CatScale);
    startTimer(50);
}

void Cat::timerEvent(QTimerEvent *)
{
    setPos(x(), y() + GameSetting::CatSpeed);

    if (y() > GameSetting::SceneHeight) {
        if (scene()) {  // 确保 Cat 仍在场景中
            scene()->removeItem(this);
            delete this;
        }
        return;
    }

    QList<QGraphicsItem*> collisions = collidingItems();
    for (auto item : collisions) {
        if (typeid(*item) == typeid(Dog)) {
            Health::getInstance().setHealth(0);
            if (scene()) {  // 确保 Cat 仍在场景中
                scene()->removeItem(this);
                delete this;
            }
            return;
        }
    }
}
