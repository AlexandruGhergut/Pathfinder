#ifndef PATHFINDER_H
#define PATHFINDER_H

// VERY POOR IMPLEMENTATION 
// NEEDS TO BE REDESIGNED

#include "Node.h"
#include <vector>
#include <cstdlib>



class Pathfinder
{
public:
    Pathfinder(int startPointX, int startPointY,
		int endPointX, int endPointY,
		std::vector< std::vector<int> >& matrix);
    std::vector< std::vector<int> > ComputePath();
private:
	
	std::vector< std::vector<Node> > mMatrix;
	Point2D mStartPoint;
	Point2D mEndPoint;
	std::vector<Point2D> mOpenList;
	std::vector<Point2D> mClosedList;

	Node& NodeAt(Point2D index);
	Node& NodeAt(int x, int y);

	int ComputeH(Point2D index);
	void addToOpenList(Point2D index);
	void addToOpenList(std::vector<Point2D> index);
	void addToClosedList(Point2D index);
	void processNeighbors(Point2D index);
	Point2D findLowestFNode();
};

#endif
