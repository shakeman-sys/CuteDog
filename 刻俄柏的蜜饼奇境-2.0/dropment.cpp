#include "dropment.h"
#include <QPixmap>
#include "GameSetting.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include "dog.h"
#include "bullet.h"
#include "health.h"

Dropment::Dropment(QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/C:/Users/ling/Desktop/resource/image/toadstool.png"));
    setScale(GameSetting::DropmentScale);
    int max=GameSetting::SceneWidth-boundingRect().width()*GameSetting::DropmentScale;
    int randomNumber=QRandomGenerator::global()->bounded(1,max);
    setPos(randomNumber,0);
    startTimer(GameSetting::DropmentTimer);
}


void Dropment::timerEvent(QTimerEvent *)
{


    setPos(x(),y()+GameSetting::DropmentSpeed);
    if(y()>GameSetting::SceneHeight){
        scene()->removeItem(this);
        delete this;
        return;
    }

    QList<QGraphicsItem *>itemList=collidingItems();
    for(auto item:itemList){
        if(typeid(*item)==typeid(Dog)){
            Health::getInstance().decrease();
            scene()->removeItem(this);
            delete this;
            return;
        }
        if(typeid(*item)==typeid(Bullet)){
            scene()->removeItem(item);
            scene()->removeItem(this);
            delete item;
            delete this;
            return;
        }
    }



}
