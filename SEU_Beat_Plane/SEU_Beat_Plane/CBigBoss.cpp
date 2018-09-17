#include "stdafx.h"
#include "CEnemyTrackerPlane.h"
#include "CEnemyPlane.h"
#include "CGameControler.h"
#include "CEnemyBullet.h"
#include "CExplosion.h"
#include "CGift.h"
#include "CUserPlane.h"
#include "CBigBoss.h"
#include<math.h>

int BigBoss::bossstatus = 1;//判断boss形态

BigBoss::BigBoss() :
	EnemyPlane(BIGBOSS),
	CountFire(0),
	MoveF(0),
	StayTime(0.0f),
	k(0)
{
	/*CBB_head = this;*/
}

void BigBoss::CircleBullet(int x, int y, BulletType bulletType)
{
	for (int i = 0; i < 10; i++)
	{
		new EnemyBullet(x, y, bulletType, i*(2 * PI / 10));
	}
}
void BigBoss::BarBullet(int x, int y, BulletType bulletType)
{
	for (int i = 0; i < 5; i++)
	{
		new EnemyBullet(x, y, bulletType, i*(2 * PI / 10));
	}
	for (int i = 4; i >= 0; i--)
	{
		new EnemyBullet(x, y, bulletType, i*(2 * PI / 10));
	}
}
void BigBoss::Update()
{
	if (CEP_nHP > 500)                             //boss形态
	{
		bossstatus = 1;
		
	}
	if (CEP_nHP <=500 && CEP_nHP>200)
	{
		bossstatus = 2;
		if (CEP_nHP > 490 && CEP_nHP <= 500)
		{ new  Explosion(CBS_nX +60, CBS_nY + 90,BULLETBLAST);}
			
	}
	if (CEP_nHP <= 200)
	{
		bossstatus = 3;
		if(CEP_nHP>190&&CEP_nHP<=200)
			new  Explosion(CBS_nX -60, CBS_nY , PLANEBLAST);
	}
	float tD = GameControler::GetInstance()->GetElapsedTime();
	float fDis = tD * CBS_nSpeed;
	int XSpeed = 75;

	if (StayTime == 0)
	{
		if (CBS_nX > 800 || MoveF == 0)
		{
			CBS_nX -= XSpeed * tD;
			MoveF = 0;
		}
		if (CBS_nX < 100 || MoveF == 1)
		{
			CBS_nX += XSpeed * tD;
			MoveF = 1;
		}
	}


	CBS_nY = 100;

	CEP_fFireTime -= tD;

	if (StayTime > 0)//发射激光时boss停止运动
	{
		StayTime -= tD;
	}
	if (StayTime < 0)
	{
		StayTime = 0;
	}
	if (CEP_fFireTime <= 0.0f)//发射子弹
	{
		CEP_fFireTime = 1.0f;
		k = 0;
		new EnemyBullet(CBS_nX + CBS_nWidth / 2 - 8, CBS_nY + CBS_nHeight, (BulletType)(CEP_nEnemyType % 4), 17.0 * PI / 36.0);
		CountFire++;
		if (CountFire % 3 == 0)
		{
			CircleBullet(CBS_nX + 5, CBS_nY + CBS_nHeight - 5, AMMO3);
			CircleBullet(CBS_nX + CBS_nWidth - 5, CBS_nY + CBS_nHeight - 5, AMMO2);
		}

	}
	if (bossstatus == 2 || bossstatus == 3)
	{
		if (CountFire % 4== 0)
		{
			new EnemyBullet(CBS_nX + CBS_nWidth / 2 - 30, CBS_nY + CBS_nHeight - 30, AMMO8, k*(2 * PI / 30));
			k++;
		}
	}
	/*if (CountFire % 1 == 0)
	{
		new EnemyBullet(CBS_nX + CBS_nWidth / 2 - 30, CBS_nY + CBS_nHeight - 30, AMMO8, k*(2* PI / 30));
		k++;
	}*/
	
	if (CountFire % 6 == 0)
	{
		CircleBullet(CBS_nX + CBS_nWidth / 2, CBS_nY + CBS_nHeight, AMMO1);
	}
	if(bossstatus!=3)
	if (CountFire % 10 == 0)
	{
		/*	CircleBullet(CBS_nX + CBS_nWidth / 2, CBS_nY + CBS_nHeight, AMMO7);*/
		new	EnemyBullet(CBS_nX + CBS_nWidth / 2 - 30, CBS_nY + CBS_nHeight - 30, AMMO7, 17.0 * PI / 36.0);
		//for (int i = 0; i < 20; i++)                         //制裁之光（破坏游戏平衡性与游戏体验）
		//{
		//	new	CEnemyBullet(i*50, 40, AMMO7, 17.0 * PI / 36.0);
		//}
		StayTime = 1.5f;
	}
	if (UserPlane::GetInstance()->CheckCollision(CBS_nX, CBS_nY, CBS_nWidth, CBS_nHeight, 20))
	{
		/*	CBS_bIsVisible = false;*/
		new Explosion(CBS_nX + CBS_nWidth / 2, CBS_nY + CBS_nHeight / 2, PLANEBLAST);
		return;
	}

}

BigBoss::~BigBoss()
{
}
