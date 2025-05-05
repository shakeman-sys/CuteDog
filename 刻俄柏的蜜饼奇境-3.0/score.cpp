#include "score.h"
#include <QFont>
#include "GameSetting.h"

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    reset();
}

void Score::reset()
{
    score = 5;//初始饱腹值
    setPlainText("饱 腹 值 ："+QString::number(score));
    setDefaultTextColor(Qt::green);
    setFont(QFont("Courier New", GameSetting::Fontsize, QFont::Bold));
}

void Score::increase()
{
    score++;
    setPlainText("饱 腹 值 ："+QString::number(score));
}


void Score::decrease()
{
    if (score > 0) {
        score--;
        setPlainText("饱 腹 值 ："+QString::number(score));
    }
}
