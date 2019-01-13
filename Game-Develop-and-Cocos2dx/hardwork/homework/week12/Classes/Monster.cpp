#include"Monster.h"
USING_NS_CC;

Factory* Factory::factory = NULL;
Factory::Factory() {
	initSpriteFrame();
}
Factory* Factory::getInstance() {
	if (factory == NULL) {
		factory = new Factory();
	}
	return factory;
}
void Factory::initSpriteFrame(){
	auto texture = Director::getInstance()->getTextureCache()->addImage("Monster.png");
	monsterDead.reserve(4);
	for (int i = 0; i < 4; i++) {
		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(258-48*i,0,42,42)));
		monsterDead.pushBack(frame);
	}
}

Sprite* Factory::createMonster() {
	Sprite* mons = Sprite::create("Monster.png", CC_RECT_PIXELS_TO_POINTS(Rect(364,0,42,42)));
	monster.pushBack(mons);
	return mons;
}

void Factory::removeMonster(Sprite* sp) {

}
void Factory::moveMonster(Vec2 playerPos,float time){

}

Sprite* Factory::collider(Rect rect) {

}