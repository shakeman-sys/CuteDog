#include "pie.h"
#include <QPixmap>
#include "GameSetting.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include "dog.h"
#include "score.h"


Pie::Pie(QGraphicsItem *parent) :QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/C:/Users/ling/Desktop/resource/image/Pie.png"));
    setScale(GameSetting::PieScale);
    int max=GameSetting::SceneWidth-boundingRect().width()*GameSetting::DropmentScale;
    int randomNumber=QRandomGenerator::global()->bounded(1,max);
    setPos(randomNumber,0);
    startTimer(GameSetting::PieTimer);
}


void Pie::timerEvent(QTimerEvent *)
{
    setPos(x(),y()+GameSetting::PieSpeed);
    if(y()>GameSetting::SceneHight){
        scene()->removeItem(this);
        delete this;
        return;
    }

    QList<QGraphicsItem *>itemList=collidingItems();
    for(auto item:itemList){
        if(typeid(*item)==typeid(Dog)){
            Score::getInstance().increase();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
}
