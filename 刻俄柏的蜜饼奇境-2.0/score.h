#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QObject>

class Score : public QGraphicsTextItem
{
    Q_OBJECT
public:
    Score(QGraphicsItem *parent = nullptr);
    int getScore(){return score;}
    void increase();
    void decrease();
    void reset();
    static Score& getInstance(){
        static Score obj;
        return obj;
    }

private:
    int score = 0;
};

#endif // SCORE_H
