#pragma execution_character_set("UTF-8")
#include "GameScene.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include <regex>
using std::regex;
using std::match_results;
using std::regex_match;
using std::cmatch;
using namespace rapidjson;

USING_NS_CC;

cocos2d::Scene* GameScene::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameScene::init() {
	if (!Layer::init())
	{
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();
	visibleHeight = size.height;
	visibleWidth = size.width;

	score_field = TextField::create("Score", "Arial", 30);
	score_field->setPosition(Size(visibleWidth / 4, visibleHeight / 4 * 3));
	this->addChild(score_field, 2);

	submit_button = Button::create();
	submit_button->setTitleText("Submit");
	submit_button->setTitleFontSize(30);
	submit_button->setPosition(Size(visibleWidth / 4, visibleHeight / 4));
	this->addChild(submit_button, 2);

	rank_field = TextField::create("", "Arial", 30);
	rank_field->setPosition(Size(visibleWidth / 4 * 3, visibleHeight / 4 * 3));
	this->addChild(rank_field, 2);

	rank_button = Button::create();
	rank_button->setTitleText("Rank");
	rank_button->setTitleFontSize(30);
	rank_button->setPosition(Size(visibleWidth / 4 * 3, visibleHeight / 4));
	this->addChild(rank_button, 2);

	submit_button->addClickEventListener([&](Ref* sender) {
		auto score_str = score_field->getStringValue();
		if (score_str.empty()) return;
		if (CCString::create(score_str)->intValue() > 0)
		{
			auto request = new HttpRequest();
			auto postData = "score=" + score_str;

			vector<string> headers;
			headers.push_back("Cookie:  GAMESESSIONID=" + Global::gameSessionId);

			request->setUrl("http://localhost:8080/submit");
			request->setRequestType(HttpRequest::Type::POST);
			request->setHeaders(headers);
			request->setRequestData(postData.c_str(), strlen(postData.c_str()));
			request->setResponseCallback([&](HttpClient *sender, HttpResponse * response) {
				if (!response) return;
				if (!response->isSucceed()) {
					score_field->setText("(っ °Д °;)っ:是不是服务器没开");
					return;
				}
				rapidjson::Document document;
				document.Parse<0>(Global::vectorChar2String(response->getResponseData()).c_str());
				if (document.HasParseError()) {
					score_field->setText("(っ °Д °;)っ:后台君在玩蛇");
					return;
				}
				if (document.IsObject() && document.HasMember("result")) {
					if (document["result"].GetBool()) {
						if (document.HasMember("info")) {
							score_field->setText(document["info"].GetString());
						}
					}
					else {
						if (document.HasMember("info")) {
							score_field->setText(document["info"].GetString());
						}
					}
				}
			});
			cocos2d::network::HttpClient::getInstance()->send(request);
			request->release();
		}
	});

	rank_button->addClickEventListener([&](Ref* sender) {
		auto request = new HttpRequest();
		char* postData = "top=10";
		vector<string> headers;
		headers.push_back("Cookie:  GAMESESSIONID=" + Global::gameSessionId);

		request->setUrl("http://localhost:8080/rank?top=10");
		request->setRequestType(HttpRequest::Type::GET);
		request->setHeaders(headers);
		// request->setRequestData(postData, strlen(postData));
		request->setResponseCallback([&](HttpClient *sender, HttpResponse * response) {
			if (!response) return;
			if (!response->isSucceed()) {
				rank_field->setText("(っ °Д °;)っ:是不是服务器没开");
				return;
			}
			rapidjson::Document document;
			document.Parse<0>(Global::vectorChar2String(response->getResponseData()).c_str());
			if (document.HasParseError()) {
				rank_field->setText("(っ °Д °;)っ:后台君在玩蛇");
				return;
			}
			if (document.IsObject() && document.HasMember("result")) {
				if (document["result"].GetBool()) {
					if (document.HasMember("info")) {
						string s = document["info"].GetString();
						std::replace(s.begin(), s.end(), '|', '\n');
						rank_field->setText(s);
					}
				}
				else {
					if (document.HasMember("info")) {
						rank_field->setText(document["info"].GetString());
					}
				}
			}
		});
		cocos2d::network::HttpClient::getInstance()->send(request);
		request->release();
	});

	return true;
}
