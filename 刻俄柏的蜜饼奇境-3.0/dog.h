#ifndef DOG_H
#define DOG_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>

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
    void timerEvent(QTimerEvent *event) override;
    void spawnBoss();
    void bossAttack();

private:
    bool playing = true;
    QGraphicsTextItem* messageItem = nullptr;
    QGraphicsPixmapItem* boss = nullptr;
    QTimer* bossTimer = nullptr;
    QTimer* attackTimer = nullptr;
    bool canShootWithoutCost = false;
    int catSpawnCounter = 0;  // 新增计数器控制Cat生成频率


};

#endif // DOG_H
