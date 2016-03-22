#pragma once
class Coordinate
{
public:
	Coordinate(void);
	~Coordinate(void);
	void Init(int xMin,int xMax,int yMin,int yMax);
public:
	int xMin; 
	int xMax; 
	int yMin; 
	int yMax; 
};

#ifndef COORDINATE
#define FIT				(point.x>c.xMin) & (point.x<c.xMax) & (point.y>c.yMin) & (point.y<c.yMax)
#define START_GAME		(175,430,325,383)
#define START_HELP		(175,430,430,490)
#define START_END		(175,430,515,575)
#define GAME_BACK		(60,128,500,560)
#define GAME_HELP		(838,925,481,538)
#define HELP_BACK		(45,95,541,569)
#define MUSIC			(27,65,16,65)
#endif

