#ifndef __MENU_SEBCE_H__
#define __MENU_SEBCE_H__

#include "cocos2d.h"

class MenuSence : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void menuStartCallback(Ref * pSender);
    
    // a selector callback
    //void startMenuCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuSence);
};

#endif // __MENU_SEBCE_H__
