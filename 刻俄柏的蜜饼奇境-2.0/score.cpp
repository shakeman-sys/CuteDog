#include "score.h"
#include <QFont>
#include "GameSetting.h"

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    reset();
}

void Score::reset()
{
    score = 0;
    setPlainText("饱 腹 值 ："+QString::number(score));
    setDefaultTextColor(Qt::green);
    setFont(QFont("Courier New", GameSetting::Fontsize, QFont::Bold));
}

void Score::increase()
{
    score++;
    setPlainText("饱 腹 值 ："+QString::number(score));
}

// 新增实现
void Score::decrease()
{
    if (score > 0) {
        score--;
        setPlainText("饱 腹 值 ："+QString::number(score));
    }
}
