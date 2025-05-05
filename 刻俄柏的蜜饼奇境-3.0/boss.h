#ifndef BOSS_H
#define BOSS_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Boss : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Boss(QGraphicsItem *parent = nullptr);

private slots:
    void move();

private:
    int direction = 1;  // 1表示向右，-1表示向左
    QTimer* moveTimer = nullptr;  // 使用 QTimer 控制移动
};

#endif // BOSS_H
