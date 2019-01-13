#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include "Global.h"
using namespace cocos2d::ui;

#include "network/HttpClient.h"
using namespace cocos2d::network;

using std::string;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    float visibleHeight;
    float visibleWidth;
    TextField * score_field;
    TextField * rank_field;
    Button *submit_button;
    Button *rank_button;
};

