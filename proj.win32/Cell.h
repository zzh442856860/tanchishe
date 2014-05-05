#ifndef CELL_H_
#define CELL_H_

#include "cocos2d.h"

USING_NS_CC;

static const int CELL_WIDTH = 24;
static const int CELL_HEIGHT = CELL_WIDTH;
static const int CELLS_HORIZON = 16;//16个cell
static const int CELLS_VERTICAL = 12;

static const int LAYER_COUNT = 4;
static const int LAYER_BACKGROUND = 0;
static const int LAYER_FOOD = 1;
static const int LAYER_SNAKE = 2;
static const int LAYER_UI = 3;

enum Direction {
	DIR_NULL,
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};

static int addtoX(const Direction dir, const int dx) {
	switch (dir)
	{
	case UP:
	case DOWN:
		return dx;
	case LEFT:
		return dx - 1;
	case RIGHT:
		return dx + 1;
	default:
		break;
	}
	return dx;
}

static int addtoY(const Direction dir, const int dy) {
	switch (dir)
	{
	case LEFT:
	case RIGHT:
		return dy;
	case UP:
		return dy + 1;
	case DOWN:
		return dy - 1;
	default:
		break;
	}
	return dy;
}

static Direction opposite(const Direction dir) {
	switch(dir) {
	case UP:
		return DOWN;
	case DOWN:
		return UP;
	case LEFT:
		return RIGHT;
	case RIGHT:
		return LEFT;
	default:
		return DIR_NULL;
	}
}

//cell是一个正方形，x,y是cell的中心点
class Cell : public CCSprite{
public:
	//Cell(int x, int y, char* fileName);

	CC_SYNTHESIZE(int, cellx_, CellX);
	CC_SYNTHESIZE(int, celly_, CellY);
	CC_SYNTHESIZE(int, spacing_, Space);
	CC_SYNTHESIZE(std::string, pngFileName_, PngFileName);

	void setCell(const Cell& cell) {
		setCell(cell.getCellX(), cell.getCellY());
	}
	void setCell(int cellX, int cellY) {
		cellx_ = cellX;
		celly_ = cellY;
		setPosition( ccp(cellX*CELL_WIDTH + CELL_WIDTH/2,
			cellY*CELL_HEIGHT + CELL_HEIGHT/2));
	}

	bool isInSameCell(const Cell& cell) {
		return cell.getCellX() == cellx_ && cell.getCellY() == celly_;
	}
};

class PngCell : public Cell {
public:
	PngCell(int cellX, int cellY, const char* pngFileName);
	virtual ~PngCell();
	
};

class AnimatedCell : public Cell {
public:
	AnimatedCell(int cellX, int cellY, int spacing, const char* pngFileName);
	AnimatedCell(AnimatedCell& cell);
	virtual ~AnimatedCell();

	//void reset(int cellX, int cellY, int spacing, const char* pngFileName);

	void startAnimation(const float interval);
private:
	int oneWidth_;
	int oneHeight_;

	CCRepeatForever* animate_;
	CCAnimation* animation_;
};

#endif