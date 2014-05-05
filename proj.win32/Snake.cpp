#include "Snake.h"
#include "cocos2d.h"

Frog::Frog(int cellx, int celly) 
:AnimatedCell(cellx, celly, 3, "q2_3.png"){

}

SnakeHead::SnakeHead(int cellx, int celly) 
:AnimatedCell(cellx, celly, 8, "q1_8.png"){
	this->setAnchorPoint( ccp(0.5, 0.5));
}

void SnakeHead::setRotationByDir(const Direction dir) {
	/*
	switch(dir) 
	{
	case UP:
		this->setRotation(180);
		break;
	case DOWN:
		this->setRotation(0);
		break;
	case LEFT:
		this->setRotation(90);
		break;
	case RIGHT:
		this->setRotation(270);
		break;
	}
	*/
}

//-----------------------------
//
//------------------------
SnakeTailPart::SnakeTailPart(const Frog* frog) 
:Frog(frog->getCellX(), frog->getCellY() ) {

}

//----------------
//
//------------------
Snake::Snake(const Direction dir, int cellx, int celly) 
: grow_(false) {

	head_ = new SnakeHead(cellx, celly);
	head_->autorelease();

	this->addChild(head_);
	this->setDirection(dir);
}

void Snake::setDirection(const Direction dir) {
	if (lastDir_ != opposite(dir)) {
		dir_ = dir;
		head_->setRotationByDir(dir);
	}
}

Snake::~Snake() {}

int Snake::getNextX() {
	return addtoX(dir_, head_->getCellX());
}

int Snake::getNextY() {
	return addtoY(dir_, head_->getCellY());
}

bool Snake::move() {
	lastDir_ = dir_;
	//CCLOG("move!!!");
	if (grow_) {
		grow_ = false;
		CCLOG("Grow!!!");
		//add the frog in the front of the tail
		SnakeTailPart* tailPart = new SnakeTailPart(currFrog_);
		CCLOG("x-y: %d--%d", currFrog_->getCellX(), currFrog_->getCellY());
		this->addChild(tailPart);
		tails_.insertObject(tailPart, 0);

		int x = 1 + CCRANDOM_0_1() * (CELLS_HORIZON-2-1);
		int y = 1 + CCRANDOM_0_1() * (CELLS_VERTICAL-2-1);

		currFrog_->setCell(x, y);

	} else {
		if (tails_.count() > 0) {
			//first move the end of the tail to where the head currently is
			SnakeTailPart* tailEnd = (SnakeTailPart*)tails_.lastObject();
			tails_.removeLastObject(false);
			tailEnd->setCell(*head_);

			tails_.insertObject(tailEnd, 0);
		}
	}
	//move the head into the direction of the snake
	head_->setCell(getNextX(), getNextY());

	//check if head collides with tail
	for (unsigned int i=0; i<tails_.count(); i++) {
		if (head_->isInSameCell(*(SnakeTailPart*)tails_.objectAtIndex(i))) {
			return false;
		}
	}
	return true;
}