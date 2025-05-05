#ifndef DROPMENT_H
#define DROPMENT_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Dropment : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Dropment(QGraphicsItem *parent = nullptr);
    ~Dropment(){}

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
};

#endif // DROPMENT_H
