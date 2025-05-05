#ifndef BOSS_H
#define BOSS_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "GameSetting.h"

class Boss : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Boss(QGraphicsItem *parent = nullptr);

protected:
    virtual void timerEvent(QTimerEvent *event) override;

private:
    int direction = 1;
    int speed = GameSetting::BossSpeed;
};

#endif // BOSS_H
