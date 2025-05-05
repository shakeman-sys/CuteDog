#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>
#include <QObject>

class Health : public QGraphicsTextItem
{
    Q_OBJECT
public:
    Health(QGraphicsItem *parent = nullptr);
    int getHealth(){return health;}
    void decrease();
    void reset();
    static Health& getInstance(){static Health obj; return obj;}

    void setHealth(int h);

private:
    int health = 30;
};

#endif // HEALTH_H
