#include "dog.h"
#include <QPixmap>
#include "GameSetting.h"
#include <QKeyEvent>
#include"dropment.h"
#include"pie.h"
#include <QGraphicsScene>
#include"bullet.h"
#include"health.h"
#include "score.h"
#include<QGraphicsTextItem>
#include<QFontMetrics>
using namespace GameSetting;




Dog::Dog(QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/C:/Users/ling/Desktop/resource/image/Dog.png"));
    setScale(PlayerScale);
    setPos(SceneWidth/2-boundingRect().width()*PlayerScale/2,
           SceneHight-boundingRect().height()*PlayerScale*1.5);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();//用于固定背景
    startTimer(500);

}


void Dog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_A:
        if(pos().x()>0)
            setPos(x()-MoveSpeed,y());
        break;
    case Qt::Key_D:
        if(pos().x()<SceneWidth-boundingRect().width()*PlayerScale)
            setPos(x()+MoveSpeed,y());
        break;
    case Qt::Key_S:
        if(pos().y()<SceneHight-boundingRect().height()*PlayerScale)
            setPos(x(),y()+MoveSpeed);
        break;
    case Qt::Key_W:
        if(pos().y()>(SceneHight-boundingRect().height()*PlayerScale)/1.3)
            setPos(x(),y()-MoveSpeed);
        break;
    case Qt::Key_P:
        if(playing) return;
        playing =true;
        Health::getInstance().reset();
        Score::getInstance().reset();
        messageItem->hide();
        break;
    case Qt::Key_Space:
        Bullet *bullet = new Bullet;
        int temp=x()+boundingRect().width()*PlayerScale/2;
        temp-=bullet->boundingRect().width()*BulletScale/2;
        bullet->setPos(temp,y());
        scene()->addItem(bullet);
        break;
    }
}

void Dog::dropmentSpawn()
{

    Dropment *dropment = new Dropment;
    scene()->addItem(dropment);

}

void Dog::pieSpawn()
{

    Pie *pie = new Pie;
    scene()->addItem(pie);

}

void Dog::gameOver()
{
    playing=false;
    for(auto item:scene()->items()){
        if((typeid(*item)==typeid(Dropment))||(typeid(*item)==typeid(Pie))){
            scene()->removeItem(item);
            delete item;
        }
    }

    if(!messageItem){
        messageItem=new QGraphicsTextItem;
        scene()->addItem(messageItem);
        QString message("昨日碎梦！按p键重新开始！");
        messageItem->setPlainText(message);
        messageItem->setDefaultTextColor(Qt::white);
        QFont font("Courier New",GameSetting::Fontsize*2.5,QFont::Bold);
        messageItem->setFont(font);
        QFontMetrics fm(font);
        int msgWidth=fm.horizontalAdvance(message);
        messageItem->setPos(GameSetting::SceneWidth/2-msgWidth/2,GameSetting::SceneHight/2);

    }else
        messageItem->show();
}

void Dog::timerEvent(QTimerEvent *)
{
    if(playing){
        dropmentSpawn();
        pieSpawn();
    }
    if(Health::getInstance().getHealth()<=0){
        gameOver();
    }
}


