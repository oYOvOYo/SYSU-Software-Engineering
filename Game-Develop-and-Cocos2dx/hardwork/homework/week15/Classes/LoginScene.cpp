#pragma execution_character_set("UTF-8")
#include "LoginScene.h"
#include "cocostudio/CocoStudio.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "Global.h"
#include "GameScene.h"
#include <regex>
using std::to_string;
using std::regex;
using std::match_results;
using std::regex_match;
using std::cmatch;
using namespace rapidjson;
USING_NS_CC;

using namespace cocostudio::timeline;

#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;

Scene* LoginScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoginScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();
	visibleHeight = size.height;
	visibleWidth = size.width;

	// default user name, use to know can button be clicked
	const string defaultUserName = "Player Name";
	textField = TextField::create(defaultUserName, "Arial", 30);
	textField->setPosition(Size(visibleWidth / 2, visibleHeight / 4 * 3));
	this->addChild(textField, 2);

	auto button = Button::create();
	button->setTitleText("Login");
	button->setTitleFontSize(30);
	button->setPosition(Size(visibleWidth / 2, visibleHeight / 2));

	button->addClickEventListener([&](Ref * sender) {
		auto userName = textField->getStringValue();
		if (!userName.empty())
		{
			auto request = new HttpRequest();
			auto postData = "username=" + userName;

			request->setUrl("http://localhost:8080/login");
			request->setRequestType(HttpRequest::Type::POST);
			request->setRequestData(postData.c_str(), strlen(postData.c_str()));
			request->setResponseCallback([&](HttpClient *sender, HttpResponse * response) {
				if (!response) return;
				if (!response->isSucceed()) {
					textField->setText("(っ °Д °;)っ:是不是服务器没开");
					return;
				}
				rapidjson::Document document;
				document.Parse<0>(Global::vectorChar2String(response->getResponseData()).c_str());
				if (document.HasParseError()) {
					textField->setText("(っ °Д °;)っ:后台君在玩蛇");
					return;
				}
				if (document.IsObject() && document.HasMember("result")) {
					if (document["result"].GetBool()) {
						Global::gameSessionId = Global::getSessionIdFromHeader(Global::vectorChar2String(response->getResponseHeader()));
						// go to game sence
						Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene(), Color3B(255, 255, 255)));
					}
					else {
						if (document.HasMember("info")) {
							textField->setText(document["info"].GetString());
						}
					}
				}
			});
			cocos2d::network::HttpClient::getInstance()->send(request);
			request->release();
		}
	});
	this->addChild(button, 2);

	return true;
}
