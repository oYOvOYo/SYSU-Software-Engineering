#include "GameSence.h"

USING_NS_CC;

Scene* GameSence::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameSence::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameSence::init()
{

	if (!Layer::init())
	{
		return false;
	}

	//add touch listener
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameSence::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("level-background-0.jpg");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0);

	auto stoneLayer = Layer::create();
	stoneLayer->setName("stoneLayer");
	auto stone = Sprite::create("stone.png");
	stone->setPosition(560, 480);
	stone->setName("stone");
	auto cheese = Sprite::create("cheese.png");
	cheese->setName("cheese");
	cheese->setVisible(false);
	stoneLayer->addChild(cheese);
	stoneLayer->addChild(stone);
	this->addChild(stoneLayer, 1);

	auto mouseLayer = Layer::create();
	mouseLayer->setName("mouseLayer");
	auto mouse = Sprite::createWithSpriteFrameName("mouse-0.png");
	mouse->setName("mouse");
	Animate* legAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("mouseAnimation"));
	mouse->runAction(RepeatForever::create(legAnimate));
	mouse->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	mouseLayer->addChild(mouse);
	this->addChild(mouseLayer, 1);
	

	auto label = Label::createWithTTF("Shoot", "fonts/arial.ttf", 48);
	label->setName("shoot");
	label->setPosition(Vec2(origin.x + visibleSize.width - label->getContentSize().width,
		origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);


	return true;
}

bool GameSence::onTouchBegan(Touch *touch, Event *unused_event) {

	auto location = touch->getLocation();
	
	auto stoneLayer = this->getChildByName("stoneLayer");
	auto mouseLayer = this->getChildByName("mouseLayer");
	auto cheese = stoneLayer->getChildByName("cheese");
	auto mouse = mouseLayer->getChildByName("mouse");
	auto stone = stoneLayer->getChildByName("stone");
	auto shoot = this->getChildByName("shoot");
	Rect rect = Rect(0, 0,
					 shoot->getContentSize().width, shoot->getContentSize().height);
	if (rect.containsPoint(shoot->convertToNodeSpace(location))) {
		auto diamond = Sprite::create("diamond.png");
		diamond->setPosition(mouse->getPosition());
		stoneLayer->addChild(diamond);

		stone->cleanup();
		auto moveto = MoveTo::create(0.5, mouse->getPosition());
		auto fadein = FadeIn::create(0.5f);
		auto moveback = MoveTo::create(0.001f, Vec2(560, 480));
		auto fadeout = FadeOut::create(0.001f);
		auto seq0 = Sequence::create(moveto, fadeout, moveback, fadein, nullptr);
		stone->runAction(seq0);

		mouse->cleanup();
		float positionX = CCRANDOM_0_1() * Director::getInstance()->getVisibleSize().width;
		float positionY = CCRANDOM_0_1() * Director::getInstance()->getVisibleSize().height;
		auto randomMove = MoveTo::create(0.5, Vec2(positionX, positionY));
		mouse->runAction(randomMove);
	}
	else {
		cheese->cleanup();
		cheese->setPosition(location);
		cheese->setVisible(true);
		auto fadein = FadeIn::create(0.001f);
		auto delay = DelayTime::create(0.5);
		auto fadeout = FadeOut::create(0.001f);
		auto seq0 = Sequence::create(fadein, delay, fadeout,nullptr);
		cheese->runAction(seq0);
		
		mouse->cleanup();
		auto rotate = RotateBy::create(0.25, 360);
		auto moveto = MoveTo::create(0.5, location);
		auto action = Spawn::createWithTwoActions(moveto, rotate);
		auto seq = Sequence::create(action, nullptr);
		mouse->runAction(seq);
	}

	return true;
}
