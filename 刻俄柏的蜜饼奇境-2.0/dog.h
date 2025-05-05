#ifndef DOG_H
#define DOG_H

#include <QGraphicsPixmapItem>
#include <QObject>

class QGraphicsTextItem;
class Dog : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Dog(QGraphicsItem *parent = nullptr);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
private:
    void dropmentSpawn();
    void pieSpawn();
    void gameOver();
    void spawnBoss();
    void bossAttack();

protected:
    virtual void timerEvent(QTimerEvent *event) override;
private:
    bool playing = true;
    QGraphicsTextItem* messageItem = nullptr;
    QGraphicsPixmapItem* boss = nullptr;
    QTimer* bossTimer = nullptr;
    QTimer* attackTimer = nullptr;
    bool canShootWithoutCost = false;
};

#endif // DOG_H
