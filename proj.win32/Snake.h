#ifndef _SNAKE_H
#define _SNAKE_H

#include "Cell.h"

USING_NS_CC;

class Frog : public AnimatedCell {
public:
	Frog(int cellx, int celly);
};

class SnakeHead : public AnimatedCell {
public:
	SnakeHead(int cellx, int celly);

	void setRotationByDir(const Direction dir);
};

class SnakeTailPart : public Frog {
public:
	SnakeTailPart(const Frog* frog);
};

class Snake : public CCNode {
public:
	Snake(const Direction dir, int cellx, int celly);
	~Snake();

	const Direction getDirection() const {
		return dir_;
	}
	void setDirection(const Direction dir);
	SnakeHead* getHead() const {
		return head_;
	}
	int getTailCount() {
		return tails_.count();
	}
	void grow() {
		grow_ = true;
	}
	void eatFrog(Frog* frog) {
		currFrog_ = frog;
	}

	int getNextX();
	int getNextY();

	bool move();

private:
	Direction dir_;  //curr direction
	Direction lastDir_;

	SnakeHead* head_;
	
	CCArray tails_;

	Frog* currFrog_;
	bool grow_;
};

#endif