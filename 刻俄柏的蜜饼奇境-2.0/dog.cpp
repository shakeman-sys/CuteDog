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

Dog::Dog(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
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
        messageItem->hide();
        break;
    case Qt::Key_Space:
        if (Score::getInstance().getScore() > 0 || canShootWithoutCost) {
            Bullet* bullet = new Bullet;
            int temp = x() + boundingRect().width() * GameSetting::PlayerScale / 2;
            temp -= bullet->boundingRect().width() * GameSetting::BulletScale / 2;
            bullet->setPos(temp, y());
            scene()->addItem(bullet);

            if (!canShootWithoutCost) {
                Score::getInstance().decrease();
            }
        }
        break;
    }
}

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
    for (auto item : scene()->items()) {
        if ((typeid(*item) == typeid(Dropment)) || (typeid(*item) == typeid(Pie))) {
            scene()->removeItem(item);
            delete item;
        }
    }

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
    } else
        messageItem->show();
}

void Dog::timerEvent(QTimerEvent *)
{
    if (playing) {
        dropmentSpawn();
        pieSpawn();
    }
    if (Health::getInstance().getHealth() <= 0) {
        gameOver();
    }

    // Check score for boss spawn
    if (Score::getInstance().getScore() >= 100 && !boss) {
        bossTimer->start(1000); // Start boss spawn timer
    }

    // Update dog image based on score
    if (Score::getInstance().getScore() > 50 && !canShootWithoutCost) {
        setPixmap(QPixmap(":/C:/Users/ling/Desktop/resource/image/dogplus.png"));
        setScale(GameSetting::PlayerScale);
        canShootWithoutCost = true;
    }
}

void Dog::spawnBoss()
{
    if (!boss) {
        boss = new Boss;
        scene()->addItem(boss);
        boss->setPos(GameSetting::SceneWidth / 2 - boss->boundingRect().width() / 2, 50);

        // Start boss attack timer
        attackTimer = new QTimer(this);
        connect(attackTimer, &QTimer::timeout, this, &Dog::bossAttack);
        attackTimer->start(2000); // Attack every 2 seconds
    }

    // Remove boss after 60 seconds
    static int bossSpawnTime = 0;
    bossSpawnTime++;
    if (bossSpawnTime >= 60 * 30) { // Assuming 30 FPS
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
        bossTimer->stop();
        delete bossTimer;
        bossTimer = nullptr;

        // Game victory
        Health::getInstance().reset();
        Score::getInstance().reset();
        if (!messageItem) {
            messageItem = new QGraphicsTextItem;
            scene()->addItem(messageItem);
            QString message("胜利！按p键重新开始！");
            messageItem->setPlainText(message);
            messageItem->setDefaultTextColor(Qt::white);
            QFont font("Courier New", GameSetting::Fontsize * 2.5, QFont::Bold);
            messageItem->setFont(font);
            QFontMetrics fm(font);
            int msgWidth = fm.horizontalAdvance(message);
            messageItem->setPos(GameSetting::SceneWidth / 2 - msgWidth / 2, GameSetting::SceneHeight / 2);
        } else
            messageItem->show();
    }
}

void Dog::bossAttack()
{
    if (boss) {
        Cat* cat = new Cat;

        // 计算随机 X 坐标
        qreal maxX = GameSetting::SceneWidth - cat->boundingRect().width();
        if (maxX < 0) maxX = 0;  // 防止负数
        int randomX = QRandomGenerator::global()->bounded(0, static_cast<int>(maxX));

        cat->setPos(randomX, 0);
        scene()->addItem(cat);
    }
}
