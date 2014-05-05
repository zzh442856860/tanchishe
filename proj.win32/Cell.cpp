#include "Cell.h"

PngCell::PngCell(int cellX, int cellY, const char* pngFileName) {
	this->setCell(cellX, cellY);
	this->initWithFile(pngFileName);
}

PngCell::~PngCell() {}

AnimatedCell::AnimatedCell(int cellX, int cellY, int spacing, const char* pngFileName) {
	this->setSpace(spacing);
	this->setPngFileName(pngFileName);

	animation_ = CCAnimation::create();
	CCImage* image = new CCImage();
	image->initWithImageFile(pngFileName);
	CCTexture2D* texture = new CCTexture2D();
	texture->initWithImage(image);

	oneWidth_ = texture->getPixelsWide() / spacing;
	oneHeight_ = texture->getPixelsHigh();

	for (int i=0; i<spacing; i++) {
		animation_->addSpriteFrameWithTexture(texture, 
			CCRectMake(i*oneWidth_, 0, oneWidth_, oneHeight_));
	}
	CCSpriteFrame* frm = ((CCAnimationFrame*)(animation_->getFrames()->objectAtIndex(0)))->getSpriteFrame();

	this->initWithSpriteFrame(frm);
	animation_->setDelayPerUnit(0.5f);

	animate_ = CCRepeatForever::create(CCAnimate::create(animation_));

	setCell(cellX, cellY);
}

AnimatedCell::AnimatedCell(AnimatedCell& cell) {
	AnimatedCell(cell.getCellX(), cell.getCellY(), cell.getSpace(), cell.getPngFileName().c_str());
}

AnimatedCell::~AnimatedCell() {}

void AnimatedCell::startAnimation(const float interval) {
	//this->stopAction(animate_);
	animation_->setDelayPerUnit(interval);
	this->runAction(animate_);
}