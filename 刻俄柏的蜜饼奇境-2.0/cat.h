#ifndef CAT_H
#define CAT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>
#include "GameSetting.h"

class Cat : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Cat(QGraphicsItem *parent = nullptr);

protected:
    virtual void timerEvent(QTimerEvent *event) override;

private:
    int speed = GameSetting::DropmentSpeed*2;
};

#endif // CAT_H
