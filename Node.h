#ifndef NODE_H
#define NODE_H

#include "Point2D.h"

struct Node
{
	Point2D matrixIndex;
	int value;
	int F;
	int G;
	int H;
	bool isWalkable;
	bool isOnOpenList;
	bool isOnClosedList;
	int openListIndex;
	Point2D parentIndex;

	Node()
	{
		matrixIndex = Point2D(0, 0);
		value = 0;
		F = 0;
		G = 0;
		H = 0;
		isWalkable = false;
		isOnOpenList = false;
		isOnClosedList = 0;
		openListIndex = 0;
		parentIndex = Point2D(0, 0);
	}

	Node operator=(const Node& rhs)
	{
		this->matrixIndex = rhs.matrixIndex;
		this->value = rhs.value;
		this->F = rhs.F;
		this->G = rhs.G;
		this->H = rhs.F;
		this->isWalkable = rhs.isWalkable;
		this->isOnClosedList = rhs.isOnClosedList;
		this->isOnOpenList = rhs.isOnOpenList;
		this->openListIndex = rhs.openListIndex;
		this->parentIndex = rhs.parentIndex;
		return *this;
	}
};


#endif