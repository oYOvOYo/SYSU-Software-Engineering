#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Factory:public cocos2d::Ref {
public:
	//获取单例工厂
	static Factory* getInstance();
	//生成一个怪物，并存储到容器中管理
	Sprite* createMonster();
	//让容器中的所有怪物都往角色移动，通过容器管理所有的怪物很方便
	void moveMonster(Vec2 playerPos,float time);
	//移除怪物
	void removeMonster(Sprite*);
	//判断碰撞
	Sprite* collider(Rect rect);
	//初始化怪物帧动画
	void initSpriteFrame();
private:
	Factory();
	Vector<Sprite*> monster;
	cocos2d::Vector<SpriteFrame*> monsterDead;
	static Factory* factory;
};