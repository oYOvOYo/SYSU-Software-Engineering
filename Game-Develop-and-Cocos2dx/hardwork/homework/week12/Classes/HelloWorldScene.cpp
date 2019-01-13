#include "HelloWorldScene.h"
#pragma execution_character_set("utf-8")
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    haveAction = false;
    dtime = 180;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    rect = Rect(0, 0, visibleSize.width, visibleSize.height);
    schedule(schedule_selector(HelloWorld::updateTime), 1.0f, dtime, 0);
    

    
    //////////////////////////////
    // 2. add nodes
    
    // 界面所有字体要求:使用fonts目录下的arial.ttf，字体大小为36
    TTFConfig fontConfig;
    fontConfig.fontFilePath = "fonts/arial.ttf";
    fontConfig.fontSize = 32;
    
    // 添加倒计时
    time = Label::createWithTTF(fontConfig, "18");
    time->setPosition(visibleSize.width / 2,
                       visibleSize.height - time->getContentSize().height / 2);
    time->setName("time");
    this->addChild(time, 1);
    

    
    
    auto texture = Director::getInstance()->getTextureCache()->addImage("$lucia_2.png");
	//从贴图中以像素单位切割，创建关键帧
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 113, 113)));
	//使用第一帧创建精灵
	player = Sprite::createWithSpriteFrame(frame0);
	player->setPosition(Vec2(origin.x + visibleSize.width / 2,
							origin.y + visibleSize.height/2));
    player->setName("player");
	addChild(player, 3);

    // 添加人物血条
	//hp条
	Sprite* sp0 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	//使用hp条设置progressBar
	pT = ProgressTimer::create(sp);
	pT->setScaleX(90);
	pT->setAnchorPoint(Vec2(0, 0));
	pT->setType(ProgressTimerType::BAR);
	pT->setBarChangeRate(Point(1, 0));
	pT->setMidpoint(Point(0, 1));
	pT->setPercentage(100);
	pT->setPosition(Vec2(origin.x+14*pT->getContentSize().width,origin.y + visibleSize.height - 2*pT->getContentSize().height));
	addChild(pT,1);
	sp0->setAnchorPoint(Vec2(0, 0));
	sp0->setPosition(Vec2(origin.x + pT->getContentSize().width, origin.y + visibleSize.height - sp0->getContentSize().height));
	addChild(sp0,0);

    
	// 静态动画
	idle.reserve(1);
	idle.pushBack(frame0);

	// 攻击动画
	attack.reserve(17);
	for (int i = 0; i < 17; i++) {
		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(113*i,0,113,113)));
		attack.pushBack(frame);
	}

	// 可以仿照攻击动画
	// 死亡动画(帧数：22帧，高：90，宽：79）
	auto texture2 = Director::getInstance()->getTextureCache()->addImage("$lucia_dead.png");
    for (int i = 0; i < 22; i++) {
        auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79*i,0,79,90)));
        dead.pushBack(frame);
    }
    
	// 运动动画(帧数：8帧，高：101，宽：68）
	auto texture3 = Director::getInstance()->getTextureCache()->addImage("$lucia_forward.png");
    for (int i = 0; i < 8; i++) {
        auto frame = SpriteFrame::createWithTexture(texture3, CC_RECT_PIXELS_TO_POINTS(Rect(68*i,0,68,101)));
        run.pushBack(frame);
    }
    

    auto wLabel = Label::createWithTTF(fontConfig, "W");
    auto aLabel = Label::createWithTTF(fontConfig, "A");
    auto sLabel = Label::createWithTTF(fontConfig, "S");
    auto dLabel = Label::createWithTTF(fontConfig, "D");
    auto xLabel = Label::createWithTTF(fontConfig, "X");
    auto yLabel = Label::createWithTTF(fontConfig, "Y");
    
    
    // 左边wasd4个虚拟按键能控制角色移动
    //    auto wButton = MenuItemLabel::create(wLabel, CC_CALLBACK_0(HelloWorld::wButtomClickCallback, this, timer));
    auto wButton = MenuItemLabel::create(wLabel, [&](Ref * sender) {
        if (!haveAction) {
            auto vec = Vec2(0, 50);
            Vec2 position = player->getPosition();
            // 角色不会移动到可视窗口外 下同
            if (rect.containsPoint(position + vec)) {
                auto moveBy = MoveBy::create(0.8f, vec);
                auto action = Spawn::createWithTwoActions(moveBy, Animate::create(Animation::createWithSpriteFrames(run, 0.1f)));
                auto seq = Sequence::create(
                        CallFunc::create(this, callfunc_selector(HelloWorld::actionBegin)),
                        action,
                        CallFunc::create(this, callfunc_selector(HelloWorld::actionFinishedCallback)),
                        NULL);
                player->runAction(seq);
            }
        }
    });
    
    auto aButton = MenuItemLabel::create(aLabel, [&](Ref * sender) {
        if (!haveAction) {
            auto vec = Vec2(-50, 0);
            Vec2 position = player->getPosition();
            if (rect.containsPoint(position + vec)) {
                auto moveBy = MoveBy::create(0.8f, vec);
                auto action = Spawn::createWithTwoActions(moveBy, Animate::create(Animation::createWithSpriteFrames(run, 0.1f)));
                auto seq = Sequence::create(
                                            CallFunc::create(this, callfunc_selector(HelloWorld::actionBegin)),
                                            action,
                                            CallFunc::create(this, callfunc_selector(HelloWorld::actionFinishedCallback)),
                                            NULL);
                player->runAction(seq);
            }
        }
    });
    
    auto sButton = MenuItemLabel::create(sLabel, [&](Ref * sender) {
        if (!haveAction) {
            auto vec = Vec2(0, -50);
            Vec2 position = player->getPosition();
            if (rect.containsPoint(position + vec)) {
                auto moveBy = MoveBy::create(0.8f, vec);
                auto action = Spawn::createWithTwoActions(moveBy, Animate::create(Animation::createWithSpriteFrames(run, 0.1f)));
                auto seq = Sequence::create(
                                            CallFunc::create(this, callfunc_selector(HelloWorld::actionBegin)),
                                            action,
                                            CallFunc::create(this, callfunc_selector(HelloWorld::actionFinishedCallback)),
                                            NULL);
                player->runAction(seq);
            }
        }
    });
    
    auto dButton = MenuItemLabel::create(dLabel, [&](Ref * sender) {
        if (!haveAction) {
            auto vec = Vec2(50, 0);
            Vec2 position = player->getPosition();
            if (rect.containsPoint(position + vec)) {
                auto moveBy = MoveBy::create(0.8f, vec);
                auto action = Spawn::createWithTwoActions(moveBy, Animate::create(Animation::createWithSpriteFrames(run, 0.1f)));
                auto seq = Sequence::create(
                                            CallFunc::create(this, callfunc_selector(HelloWorld::actionBegin)),
                                            action,
                                            CallFunc::create(this, callfunc_selector(HelloWorld::actionFinishedCallback)),
                                            NULL);
                player->runAction(seq);
            }
        }
    });
    // 右边2个虚拟按键x，y能控制角色播放不同的帧动画
    auto xButton = MenuItemLabel::create(xLabel, [&](Ref * sender) {
        if (!haveAction) {
            auto vec = Vec2(0, 0);
            Vec2 position = player->getPosition();
            if (rect.containsPoint(position + vec)) {
                auto moveBy = MoveBy::create(0.8f, vec);
                auto action = Spawn::createWithTwoActions(moveBy, Animate::create(Animation::createWithSpriteFrames(attack, 0.1f)));
                auto seq = Sequence::create(
                                            CallFunc::create(this, callfunc_selector(HelloWorld::actionBegin)),
                                            action,
                                            Animate::create(Animation::createWithSpriteFrames(idle, 0.1f)),
                                            CallFunc::create(this, callfunc_selector(HelloWorld::actionFinishedCallback)),
                                            NULL);

                player->runAction(seq);
                
            }
// No Use to if
//            inline float clampf(float value, float min_inclusive, float max_inclusive)
//            {
//                if (min_inclusive > max_inclusive) {
//                    std::swap(min_inclusive, max_inclusive);
//                }
//                return value < min_inclusive ? min_inclusive : value < max_inclusive? value : max_inclusive;
//            }
//            if (pT->getPercentage() <= 80.0f) {
//                pT->runAction(ProgressTo::create(1.0f, pT->getPercentage() + 20.0f));
//            }
             // 点击虚拟按键x播放帧动画并让血条减少,点击y播放帧动画并让血条增加(加分项)
             pT->runAction(ProgressTo::create(1.0f, pT->getPercentage() + 20.0f));
        }
    });
    
    auto yButton = MenuItemLabel::create(yLabel, [&](Ref * sender) {
        if (!haveAction) {
            auto vec = Vec2(0, 0);
            Vec2 position = player->getPosition();
            if (rect.containsPoint(position + vec)) {
                auto moveBy = MoveBy::create(0.8f, vec);
                auto action = Spawn::createWithTwoActions(moveBy, Animate::create(Animation::createWithSpriteFrames(dead, 0.1f)));
                auto seq = Sequence::create(
                                            CallFunc::create(this, callfunc_selector(HelloWorld::actionBegin)),
                                            action,
                                            Animate::create(Animation::createWithSpriteFrames(idle, 0.1f)),
                                            CallFunc::create(this, callfunc_selector(HelloWorld::actionFinishedCallback)),
                                            NULL);
                player->runAction(seq);
            }
//            if (pT->getPercentage() >= 20.0f) {
//                pT->runAction(ProgressTo::create(1.0f, pT->getPercentage() - 20.0f));
//            }
            // 点击虚拟按键x播放帧动画并让血条减少,点击y播放帧动画并让血条增加(加分项)
            pT->runAction(ProgressTo::create(1.0f, pT->getPercentage() - 20.0f));
        }
    });
    
    
    
    wButton->setPosition(wLabel->getContentSize().width * 1.5, wLabel->getContentSize().height * 1.5);
    aButton->setPosition(wLabel->getContentSize().width * 0.5, wLabel->getContentSize().height * 0.5);
    sButton->setPosition(wLabel->getContentSize().width * 1.5, wLabel->getContentSize().height * 0.5);
    dButton->setPosition(wLabel->getContentSize().width * 2.5, wLabel->getContentSize().height * 0.5);
    xButton->setPosition(visibleSize.width - wLabel->getContentSize().width * 1,
                         wLabel->getContentSize().height * 1.5);
    yButton->setPosition(visibleSize.width - wLabel->getContentSize().width * 1.5,
                         wLabel->getContentSize().height * 0.5);
    
    auto buttonMenu = Menu::create(wButton, aButton, sButton, dButton, xButton, yButton,NULL);

    
    buttonMenu->setPosition(0, 0);
    this->addChild(buttonMenu, 4);
    
    return true;
}

void HelloWorld::updateTime(float dt){
    char buffer[4] = {0};
    sprintf(buffer, "%d", dtime);
    time->setString(buffer);
    dtime--;
}

// X、Y播放的动画不能同时播放
void HelloWorld::actionBegin() {
    haveAction = true;
}
// X、Y播放的动画不能同时播放
void HelloWorld::actionFinishedCallback() {
    haveAction = false;
}

// Use CallBack version
//void HelloWorld::wButtomClickCallback(cocos2d::Label* pSender) {
//    auto player = this->getChildByName("player");
//    Vec2 position = player->getPosition();
//    player->setPosition(position + Vec2(0, 100));
//    pSender->setString("w");
//}
