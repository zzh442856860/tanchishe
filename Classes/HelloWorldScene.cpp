#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	bool bRet = false;
	do {
		CC_BREAK_IF(! CCLayer::init() );
		//layer 4
		for (int i=0; i<LAYER_COUNT; i++) {
			addChild(CCLayer::create(), i);
		}
		//background
		CCLayer* layer = (CCLayer*)this->getChildren()->objectAtIndex(LAYER_BACKGROUND);
		layer->setTouchEnabled(false);
		CCSprite* pSprite = CCSprite::create("snake_background.png");
		CC_BREAK_IF(! pSprite);

		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pSprite->setPosition( ccp(size.width/2, size.height/2));
		layer->addChild(pSprite);

		//close
		layer = (CCLayer*)this->getChildren()->objectAtIndex(LAYER_UI);
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(HelloWorld::menuCloseCallback));
		CC_BREAK_IF(! pCloseItem);
		pCloseItem->setPosition(ccp(size.width - 20, 20));

		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);
		layer->addChild(pMenu);

		CCMenuItemImage* pUpImage = CCMenuItemImage::create("u1.png", "u2.png", this, menu_selector(HelloWorld::upCallback));
		pUpImage->setAnchorPoint(ccp(0.5, 0));
		pUpImage->setPositionY(6.0f);

		CCMenuItemImage* pDownImage = CCMenuItemImage::create("d1.png", "d2.png", this, menu_selector(HelloWorld::downCallback));
		pDownImage->setAnchorPoint(ccp(0.5, 1));
		pDownImage->setPositionY(-6.0f);

		CCMenuItemImage* pLeftImage = CCMenuItemImage::create("b1.png", "b2.png", this, menu_selector(HelloWorld::leftCallback));
		pLeftImage->setAnchorPoint(ccp(1, 0.5));
		pLeftImage->setPositionX(-6.0f);

		CCMenuItemImage* pRightImage = CCMenuItemImage::create("f1.png", "f2.png", this, menu_selector(HelloWorld::rightCallback));
		pRightImage->setAnchorPoint(ccp(0, 0.5));
		pRightImage->setPositionX(6.0f);

		CCMenu* arrowMenu = CCMenu::create(pUpImage, pDownImage, pLeftImage, pRightImage, NULL);
		arrowMenu->setPosition(100, 100);
		layer->addChild(arrowMenu);

		//score
		scoreLabel_ = CCLabelTTF::create("Score:0", "Plok.ttf", 24);
		scoreLabel_->setPosition( ccp(30, size.height - 30));
		scoreLabel_->setAnchorPoint( ccp(0, 0.5));
		layer->addChild(scoreLabel_);

		titleLabel_ = CCLabelTTF::create("Snake On Phone!", "Plok.ttf", 30);
		titleLabel_->setPosition(ccp(size.width/2, size.height/2));
		layer->addChild(titleLabel_);
		titleLabel_->setScale(0.0f);

		gameOverLabel_ = CCLabelTTF::create("Game Over!", "Plok.ttf", 30);
		gameOverLabel_->setPosition( ccp(size.width/2, size.height/2));
		layer->addChild(gameOverLabel_);
		gameOverLabel_->setVisible(false);

		
		schedule(schedule_selector(HelloWorld::tick), 0.25f);

		//sanke and frog
		snake_ = new Snake(RIGHT, 0, 0);
		snake_->autorelease();
		snake_->getHead()->startAnimation(0.5);
		//snake_->grow_ = false;
		//snake_->grow();
		layer = (CCLayer*)this->getChildren()->objectAtIndex(LAYER_SNAKE);
		layer->addChild(snake_);

		frog_ = new Frog(0,0);
		frog_->autorelease();
		frog_->startAnimation(0.5);
		setFrogToRandomCell();
		layer = (CCLayer*)this->getChildren()->objectAtIndex(LAYER_FOOD);
		layer->addChild(frog_);

		isRunning_ = false;
		score_ = 0;
		srand(time(NULL));

		bRet = true;
	} while(0);

	return bRet;
/*
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
	*/
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::playMunchSound() {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("munch.ogg");
}

void HelloWorld::playGameOverSound() {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("game_over.ogg");
}

void HelloWorld::gameCircle(float dt) {
	if (isRunning_) {
		if (!snake_->move()) {
			gameOver();
		}
		handleNewSnakePosition();
	}
}

void HelloWorld::gameOver() {
	playGameOverSound();

	//CCLayer* layer = (CCLayer*)this->getChildren()->objectAtIndex(LAYER_UI);
	//layer->addChild(gameOverLabel_);
	gameOverLabel_->setVisible(true);
	gameOverLabel_->setScale(0);
	gameOverLabel_->runAction(CCScaleTo::create(1.0, 1.0));
	gameOverLabel_->runAction(CCRotateBy::create(1.0, 360));

	isRunning_ = false;
}

void HelloWorld::setFrogToRandomCell() {
	int x = 1 + CCRANDOM_0_1() * (CELLS_HORIZON-2-1);
	int y = 1 + CCRANDOM_0_1() * (CELLS_VERTICAL-2-1);
	
	frog_->setCell(x, y);
}

void HelloWorld::tick(float dt) {
	float scale = titleLabel_->getScale();
	if (scale < 0.8) {
		titleLabel_->setScale(scale + 0.1);
	} else {
		CCLayer* layer = (CCLayer*)this->getChildren()->objectAtIndex(LAYER_UI);
		unschedule(schedule_selector(HelloWorld::tick));
		layer->removeChild(titleLabel_);

		isRunning_ = true;
		schedule(schedule_selector(HelloWorld::gameCircle), 0.25f);
	}
}

void HelloWorld::handleNewSnakePosition() {
	SnakeHead* head = snake_->getHead();
	
	if (head->getCellX() < 0 
		|| head->getCellX() >= CELLS_HORIZON
		|| head->getCellY() < 0
		|| head->getCellY() >= CELLS_VERTICAL) {
			gameOver();
	} else if (head->isInSameCell((const Cell&)*frog_) ){
		score_ += 50;

		char score[128] = {0};
		sprintf(score, "Score: %d", score_);
		scoreLabel_->setString(score);

		CCLOG("eatfrog before: %d--%d", frog_->getCellX(), frog_->getCellY());
		snake_->eatFrog(frog_);
		snake_->grow();
		
		playMunchSound();
		//setFrogToRandomCell();
	}
}

