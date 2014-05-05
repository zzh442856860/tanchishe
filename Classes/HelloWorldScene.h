#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "../proj.win32/Snake.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
	void upCallback(CCObject* pSender) {
		snake_->setDirection(UP);
	}
	void downCallback(CCObject* pSender) {
		snake_->setDirection(DOWN);
	}
	void leftCallback(CCObject* pSender) {
		snake_->setDirection(LEFT);
	}
	void rightCallback(CCObject* pSender) {
		snake_->setDirection(RIGHT);
	}

	void gameCircle(float dt);
	void tick(float dt);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

private:
	void setFrogToRandomCell();
	void gameOver();

	void handleNewSnakePosition();

	void playMunchSound();
	void playGameOverSound();

	int score_;
	bool isRunning_;

	CCLabelTTF* scoreLabel_;
	CCLabelTTF* gameOverLabel_;
	CCLabelTTF* titleLabel_;

	Snake* snake_;
	Frog* frog_;
};

#endif // __HELLOWORLD_SCENE_H__
