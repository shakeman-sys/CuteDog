#ifndef DOG_H
#define DOG_H

#include <QGraphicsPixmapItem>
#include <QObject>

class QGraphicsTextItem;
class Dog : public QObject, public  QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Dog(QGraphicsItem *parent = nullptr);

    // QGraphicsItem interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
private:
    void dropmentSpawn();
    void pieSpawn();
    void gameOver();

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
private:
    bool playing=true;
    QGraphicsTextItem* messageItem=nullptr;

};

#endif // DOG_H
