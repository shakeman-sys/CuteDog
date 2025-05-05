#ifndef PIE_H
#define PIE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Pie :  public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Pie(QGraphicsItem *parent = nullptr);
    ~Pie(){}

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
};

#endif // PIE_H
