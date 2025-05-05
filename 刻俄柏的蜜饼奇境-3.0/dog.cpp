#include "dog.h"
#include <QPixmap>
#include "GameSetting.h"
#include <QKeyEvent>
#include "dropment.h"
#include "pie.h"
#include <QGraphicsScene>
#include "bullet.h"
#include "health.h"
#include "score.h"
#include "boss.h"
#include "cat.h"
#include <QTimer>
#include <QFontMetrics>
#include <QRandomGenerator>
#include <QGraphicsTextItem>
#include <QFont>

Dog::Dog(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    //创造场景
    setPixmap(QPixmap(":/C:/Users/ling/Desktop/resource/image/Dog.png"));
    setScale(GameSetting::PlayerScale);
    setPos(GameSetting::SceneWidth / 2 - boundingRect().width() * GameSetting::PlayerScale / 2,
           GameSetting::SceneHeight - boundingRect().height() * GameSetting::PlayerScale * 1.5);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus(); // 用于固定背景
    startTimer(500);

    // Boss timer
    bossTimer = new QTimer(this);
    connect(bossTimer, &QTimer::timeout, this, &Dog::spawnBoss);

}

//键盘操作
//以后可以考虑用鼠标操作Player的移动
void Dog::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
        if (pos().x() > 0)
            setPos(x() - GameSetting::MoveSpeed, y());
        break;
    case Qt::Key_D:
        if (pos().x() < GameSetting::SceneWidth - boundingRect().width() * GameSetting::PlayerScale)
            setPos(x() + GameSetting::MoveSpeed, y());
        break;
    case Qt::Key_S:
        if (pos().y() < GameSetting::SceneHeight - boundingRect().height() * GameSetting::PlayerScale)
            setPos(x(), y() + GameSetting::MoveSpeed);
        break;
    case Qt::Key_W:
        if (pos().y() > (GameSetting::SceneHeight - boundingRect().height() * GameSetting::PlayerScale) / 1.3)
            setPos(x(), y() - GameSetting::MoveSpeed);
        break;
    case Qt::Key_P:
        if (playing) return;
        playing = true;
        Health::getInstance().reset();
        Score::getInstance().reset();
        if (messageItem) {
            messageItem->hide();
        }
        break;
    case Qt::Key_Space:
        if (Score::getInstance().getScore() > 0 || canShootWithoutCost) {
            //发射条件：score>0 或 Dog已进化
            Bullet* bullet = new Bullet;
            int temp = x() + boundingRect().width() * GameSetting::PlayerScale / 2;
            temp -= bullet->boundingRect().width() * GameSetting::BulletScale / 2;
            bullet->setPos(temp, y());
            scene()->addItem(bullet);

            if (!canShootWithoutCost) {
                //未进化时，发射bullet需消耗score
                Score::getInstance().decrease();
            }
        }
        break;
    }
}

//各项目生成
void Dog::dropmentSpawn()
{
    Dropment* dropment = new Dropment;
    scene()->addItem(dropment);
}

void Dog::pieSpawn()
{
    Pie* pie = new Pie;
    scene()->addItem(pie);
}

void Dog::gameOver()
{
    playing = false;

    // 删除所有 Dropment、Pie、Boss 和 Cat
    QList<QGraphicsItem*> itemsToDelete;
    for (auto item : scene()->items()) {
        if (dynamic_cast<Dropment*>(item) ||
            dynamic_cast<Pie*>(item) ||
            dynamic_cast<Boss*>(item) ||
            dynamic_cast<Cat*>(item)) {
            itemsToDelete.append(item);
        }
    }

    // 删除所有收集的对象
    for (auto item : itemsToDelete) {
        scene()->removeItem(item);
        delete item;
    }

    // 重置 Boss 和 Cat 指针
    if (boss) {
        boss = nullptr;
    }


    if (bossTimer) {
        bossTimer->stop();
        delete bossTimer;
        bossTimer = nullptr;
    }

    if (attackTimer) {
        attackTimer->stop();
        delete attackTimer;
        attackTimer = nullptr;
    }


    // 显示游戏结束消息
    if (!messageItem) {
        messageItem = new QGraphicsTextItem;
        scene()->addItem(messageItem);
        QString message("昨日碎梦！按p键重新开始！");
        messageItem->setPlainText(message);
        messageItem->setDefaultTextColor(Qt::white);
        QFont font("Courier New", GameSetting::Fontsize * 2.5, QFont::Bold);
        messageItem->setFont(font);
        QFontMetrics fm(font);
        int msgWidth = fm.horizontalAdvance(message);
        messageItem->setPos(GameSetting::SceneWidth / 2 - msgWidth / 2, GameSetting::SceneHeight / 2);
    } else {
        messageItem->show();
    }
}

//正常游戏时
void Dog::timerEvent(QTimerEvent *)
{
    if (playing) {
        dropmentSpawn();
        pieSpawn();
    }
    if (Health::getInstance().getHealth() <= 0) {
        gameOver();
        return; // 直接返回，避免后续逻辑执行
    }

    // score达到100，生成boss
    if (Score::getInstance().getScore() >= 100 && !boss) {
        spawnBoss();
    }

    // score达到50，小刻进化
    if (Score::getInstance().getScore() > 50 && !canShootWithoutCost) {
        setPixmap(QPixmap(":/C:/Users/ling/Desktop/resource/image/dogplus.png"));
        setScale(GameSetting::PlayerScale*1.4);
        canShootWithoutCost = true;
    }

    // 如果Boss存在且游戏时间超过60秒，显示胜利信息
    //以后可以考虑单独列一个函数gameVictor
    if (boss && Score::getInstance().getScore() >= 100) {
        static QElapsedTimer victoryTimer;
        if (!victoryTimer.isValid()) {
            victoryTimer.start();
        }

        if (victoryTimer.elapsed() >= 60000) { // 60 秒
            playing = false;
            //删除对象，重置指针
            if (boss) {
                scene()->removeItem(boss);
                delete boss;
                boss = nullptr;
            }

            if (attackTimer) {
                attackTimer->stop();
                delete attackTimer;
                attackTimer = nullptr;
            }
            if (bossTimer) {
                bossTimer->stop();
                delete bossTimer;
                bossTimer = nullptr;
            }

            for (auto item : scene()->items()) {
                if (dynamic_cast<Dropment*>(item) ||
                    dynamic_cast<Pie*>(item) ||
                    dynamic_cast<Boss*>(item) ||
                    dynamic_cast<Cat*>(item)) {
                    scene()->removeItem(item);
                    delete item;
                }
            }


            Health::getInstance().reset();
            Score::getInstance().reset();
            if (!messageItem) {
                messageItem = new QGraphicsTextItem;
                scene()->addItem(messageItem);
                QString message("征服罗德岛！按p键重新开始！");
                messageItem->setPlainText(message);
                messageItem->setDefaultTextColor(Qt::white);
                QFont font("Courier New", GameSetting::Fontsize * 2.5, QFont::Bold);
                messageItem->setFont(font);
                QFontMetrics fm(font);
                int msgWidth = fm.horizontalAdvance(message);
                messageItem->setPos(GameSetting::SceneWidth / 2 - msgWidth / 2, GameSetting::SceneHeight / 2);
            } else {
                messageItem->show();
            }
        }
    }
}

void Dog::spawnBoss()
{
    if (!boss) {
        boss = new Boss;
        scene()->addItem(boss);
        // 设置 Boss 的初始位置在屏幕中央
        boss->setPos(GameSetting::SceneWidth / 2 - boss->boundingRect().width() / 2, 50);

        attackTimer = new QTimer(this);
        connect(attackTimer, &QTimer::timeout, this, &Dog::bossAttack);
        attackTimer->start(3000); // Cat生成频率
    }

}

void Dog::bossAttack()
{
    if (boss && attackTimer) {
        Cat* cat = new Cat;

        // 获取 Boss 的当前位置和宽度
        qreal bossX = boss->x();
        qreal bossWidth = boss->boundingRect().width();
        qreal catWidth = cat->boundingRect().width() * GameSetting::CatScale; // 确保使用正确的缩放

        // 计算 Cat 可以出现的 X 范围，使其出现在 Boss 附近
        int minX = qMax(0, static_cast<int>(bossX - bossWidth / 2 - catWidth / 2));
        int maxX = qMin(static_cast<int>(GameSetting::SceneWidth - catWidth),
                        static_cast<int>(bossX + bossWidth / 2 + catWidth / 2));

        // 确保 minX <= maxX
        if (minX > maxX) {
            minX = maxX; // 如果范围无效，则将 Cat 放在 Boss 的位置
        }

        // 生成随机 X 坐标 [minX, maxX]
        int randomX = QRandomGenerator::global()->bounded(minX, maxX + 1);

        cat->setPos(randomX, 0); // Cat 从顶部出现
        scene()->addItem(cat);
    }
}
