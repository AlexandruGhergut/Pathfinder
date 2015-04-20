#ifndef POINT2D_H
#define POINT2D_H

struct Point2D
{
	
	int x;
	int y;
	Point2D() { x = 0; y = 0; }
	Point2D(int i, int j) {x = i; y = j; }

	bool operator==(const Point2D& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
	}
};

#endif