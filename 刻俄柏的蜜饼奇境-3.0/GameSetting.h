// GameSetting.h
//各项目的部分参数
#ifndef GAMESETTING_H
#define GAMESETTING_H

namespace GameSetting {
const int SceneWidth = 800;
const int SceneHeight = 900;
const int Fontsize = 16;

// Player settings
const float PlayerScale = 0.15;
const int MoveSpeed = 15;

// Dropment settings
const float DropmentScale = 0.4;
const int DropmentTimer = 100;  // 出现频率（毫秒）
const int DropmentSpeed = 5;    // 下落速度

// Pie settings
const float PieScale = 0.3;
const int PieTimer = 50;       // 出现频率（毫秒）
const int PieSpeed = 7;         // 下落速度

// Bullet settings
const float BulletScale = 0.7;
const int BulletTimer = 50;
const int BulletSpeed = 10;

// Boss settings
const float BossScale = 0.3;
const int BossSpeed = 6;

// Cat settings
const float CatScale = 0.12;
const int CatSpeed = 10;

}

#endif // GAMESETTING_H
