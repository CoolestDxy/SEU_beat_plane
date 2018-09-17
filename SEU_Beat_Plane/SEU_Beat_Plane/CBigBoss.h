#pragma once
#include "stdafx.h"
#include "CEnemyPlane.h"
class BigBoss :public EnemyPlane
{
public:
	BigBoss();
	void Update();
	void CircleBullet(int x, int y, BulletType bulletType);
	void BarBullet(int x, int y, BulletType bulletType);
	~BigBoss();
	static int bossstatus;
private:

	int CountFire;
	int MoveF;
	int k;
	float StayTime;
};
