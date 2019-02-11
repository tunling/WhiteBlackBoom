#include "WhiteBlackScene.h"
#include "SimpleAudioEngine.h"
#include "Hero.h"
#include "SimpleAudioEngine.h"
#include"cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MyCallBackReader.h"
using namespace cocos2d;
using namespace cocostudio::timeline;
USING_NS_CC;
Scene* WhiteBlackScene::createScene()
{
	return WhiteBlackScene::create();
}
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
}
bool WhiteBlackScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CSLoader* instance = CSLoader::getInstance();
	instance->registReaderObject("MyCallBackReader", (ObjectFactory::Instance)MyCallBackReader::getInstance);
	Node *m_csbNode = CSLoader::createNode("WhiteBlack.csb");
	m_csbNode->setContentSize(visibleSize);
	ui::Helper::doLayout(m_csbNode);
	this->addChild(m_csbNode);

	this->scheduleUpdate();
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(WhiteBlackScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(WhiteBlackScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	actor = Hero::create("1.png");
	actor->init("actor.plist");
	if (actor == nullptr) {
		problemLoading("1.png");
	}
	else {
		actor->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
		this->addChild(actor, 0);
	}
	return true;
}

void WhiteBlackScene::releaseKey() {
	keys[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
	keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
	keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
	keys[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;
}

void WhiteBlackScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event) {
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		releaseKey();
		keys[keycode] = true;
		actor->move(3);
		actor->state = 3;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		releaseKey();
		keys[keycode] = true;
		actor->move(1);
		actor->state = 1;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		releaseKey();
		keys[keycode] = true;
		actor->move(2);
		actor->state = 2;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		releaseKey();
		keys[keycode] = true;
		actor->move(0);
		actor->state = 0;
	}
}

void WhiteBlackScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event) {
	keys[keycode] = false;
	if ((keycode == EventKeyboard::KeyCode::KEY_UP_ARROW && actor->state==3)
		|| (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && actor->state == 1)
		|| (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && actor->state == 2)
		|| (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW && actor->state == 0)) 
	{
		actor->stop();
		actor->state = -1;
	}
}

bool WhiteBlackScene::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

void WhiteBlackScene::update(float dt) {
	float x = actor->getPosition().x;
	float y = actor->getPosition().y;
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
		actor->setPosition(x, y - 1);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
		actor->setPosition(x - 1, y);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
		actor->setPosition(x + 1, y);
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)) {
		actor->setPosition(x, y + 1);
	}
}
