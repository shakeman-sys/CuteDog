#include <QApplication>
#include <QGraphicsScene>
#include <QIcon>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "GameSetting.h"
#include "dog.h"
#include "score.h"
#include "health.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("刻俄柏的蜜饼奇境");
    QApplication::setWindowIcon(QIcon(":/C:/Users/ling/Desktop/resource/image/Dog.png"));

    // 创建场景
    QGraphicsScene* scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, GameSetting::SceneWidth, GameSetting::SceneHeight);  // 逻辑坐标 (0,0) 到 (800,900)
    scene->setBackgroundBrush(QImage(":/C:/Users/ling/Desktop/resource/image/forest.png"));

    // 创建小刻（Dog）
    Dog* dog = new Dog;
    scene->addItem(dog);

    // 添加分数和健康值显示
    scene->addItem(&Score::getInstance());
    scene->addItem(&Health::getInstance());
    scene->setStickyFocus(true);  // 点击场景时不取消小刻的状态

    // 创建视图并设置
    QGraphicsView view(scene);
    view.setFixedSize(GameSetting::SceneWidth, GameSetting::SceneHeight);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.show();

    // 添加背景音乐
    QMediaPlayer bgMusic;
    QAudioOutput audioOutput;
    bgMusic.setAudioOutput(&audioOutput);
    bgMusic.setSource(QUrl("qrc:/C:/Users/ling/Desktop/resource/sound/ A WORLD FAMILIARLY UNKNOWN.wav"));
    bgMusic.play();

    return a.exec();
}
