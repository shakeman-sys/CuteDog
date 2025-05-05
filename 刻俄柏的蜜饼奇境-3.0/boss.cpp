#include "boss.h"
#include <QTimer>
#include "GameSetting.h"

Boss::Boss(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    //创造boss
    setPixmap(QPixmap(":/C:/Users/ling/Desktop/resource/image/boss.png"));
    setScale(GameSetting::BossScale);

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Boss::move);
    moveTimer->start(50);  // 每 50ms 移动一次
}

void Boss::move()
{
    // boss移动逻辑
    setPos(x() + direction * GameSetting::BossSpeed, y());

    // 获取场景宽度和Boss宽度
    int sceneWidth = GameSetting::SceneWidth;
    int bossWidth = boundingRect().width();

    // 碰壁时自动变向
    if (x() <= 0) {
        direction = 1;  // 碰到左边界，向右移动
    } else if (x() >= sceneWidth - bossWidth/2) {
        direction = -1;  // 碰到右边界，向左移动
    }

    // 确保 Boss 没有被意外删除
    if (!scene()) {
        moveTimer->stop();
        deleteLater();  // 安全删除
    }
}
