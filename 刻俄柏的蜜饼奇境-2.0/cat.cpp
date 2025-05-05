#include "cat.h"
#include <QTimerEvent>
#include "GameSetting.h"
#include "dog.h"
#include "health.h"

Cat::Cat(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/C:/Users/ling/Desktop/resource/image/mon3tr.png"));
    setScale(GameSetting::DropmentScale);
    startTimer(50);
}

void Cat::timerEvent(QTimerEvent *)
{
    setPos(x(), y() + GameSetting::DropmentSpeed);

    if (y() > GameSetting::SceneHeight) {
        scene()->removeItem(this);
        delete this;
        return;
    }

    QList<QGraphicsItem*> collisions = collidingItems();
    for (auto item : collisions) {
        if (typeid(*item) == typeid(Dog)) {
            Health::getInstance().setHealth(0);
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
}
