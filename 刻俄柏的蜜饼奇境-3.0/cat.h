#ifndef CAT_H
#define CAT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>


class Cat : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Cat(QGraphicsItem *parent = nullptr);

protected:
    virtual void timerEvent(QTimerEvent *event) override;


};

#endif // CAT_H
