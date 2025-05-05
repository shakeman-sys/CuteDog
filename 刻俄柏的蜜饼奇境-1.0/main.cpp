#include <QApplication>

#include <QGraphicsScene>
#include<QIcon>
#include <QGraphicsView>
#include <GameSetting.h>
#include "dog.h"
#include "score.h"
#include "health.h"
#include<QtMultimedia>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("刻俄伯的蜜饼奇境");
    QApplication::setWindowIcon(QIcon(":/C:/Users/ling/Desktop/resource/image/Dog.png"));


    //创（召）建（唤）小刻！
    Dog* dog=new Dog;


    //创建场景
    QGraphicsScene* scene=new QGraphicsScene;
    scene->addItem(dog);
    scene->setSceneRect(0,0,GameSetting::SceneWidth,GameSetting::SceneHight);  //逻辑坐标，从（0，0）到（800，800）
    scene->setBackgroundBrush(QImage(":/C:/Users/ling/Desktop/resource/image/forest.png"));
    //创建分数文字
    scene->addItem(&Score::getInstance());
    scene->addItem(&Health::getInstance());
    scene->setStickyFocus(true); //点击场景时，不取消小刻的状态

    QGraphicsView view(scene);
    view.setFixedSize(GameSetting::SceneWidth,GameSetting::SceneHight);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.show();

    //添加背景音乐
    QMediaPlayer bgMusic;
    QAudioOutput audioOutput;
    bgMusic.setAudioOutput(&audioOutput);
    bgMusic.setSource(QUrl("qrc:/C:/Users/ling/Desktop/resource/sound/ A WORLD FAMILIARLY UNKNOWN.wav"));
    bgMusic.play();
    return a.exec();
}
