#include "stdafx.h"
#include "Coordinate.h"


Coordinate::Coordinate(void)
{
}

void Coordinate::Init(int xMin,int xMax,int yMin,int yMax)
{
	this->xMin=xMin;
	this->xMax=xMax;
	this->yMin=yMin;
	this->yMax=yMax;
}


Coordinate::~Coordinate(void)
{
}
