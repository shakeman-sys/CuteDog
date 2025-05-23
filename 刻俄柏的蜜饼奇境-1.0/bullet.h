#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Bullet :  public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(QGraphicsItem *parent = nullptr);

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
};

#endif // BULLET_H
