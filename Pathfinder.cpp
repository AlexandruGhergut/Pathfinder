#include "Pathfinder.h"
#include <iostream>

Pathfinder::Pathfinder(int startPointX, int startPointY,
	int endPointX, int endPointY,
	std::vector< std::vector<int> >& matrix)
{
	mStartPoint = Point2D(startPointX, startPointY);
	mEndPoint = Point2D(endPointX, endPointY);


	mMatrix.resize(matrix.size() + 2);
	for (int i = 0; i < mMatrix.size(); i++)
		mMatrix[i].resize(matrix[0].size() + 2);

	for (int i = 0; i < mMatrix[0].size(); i++)
	{
		mMatrix[0][i].value = 0;
		mMatrix[mMatrix.size() - 1][i].value = 0;
	}

	for (int i = 0; i < mMatrix.size(); i++)
	{
		mMatrix[i][0].value = 0;
		mMatrix[i][mMatrix[0].size() - 1];
	}

	for (int i = 0; i < matrix.size(); i++)
	for (int j = 0; j < matrix[i].size(); j++)
	{
		mMatrix[i + 1][j + 1].matrixIndex = Point2D(i + 1, j + 1);
		mMatrix[i + 1][j + 1].value = matrix[i][j];
	}

	//
	for (int i = 0; i < mMatrix.size(); i++)
	{
		for (int j = 0; j < mMatrix[i].size(); j++)
			std::cout << mMatrix[i][j].value << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;

	for (int i = 0; i < mMatrix.size(); i++)
	{
		for (int j = 0; j < mMatrix[i].size(); j++)
			std::cout << " (" << mMatrix[i][j].matrixIndex.x  << " " << mMatrix[i][j].matrixIndex.y << " )";
		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
			std::cout << matrix[i][j] << " ";
		std::cout << std::endl;
	}

	mMatrix[startPointX][startPointY].value = 2;
	mMatrix[endPointX][endPointY].value = 3;
}

Node& Pathfinder::NodeAt(Point2D index)
{
	return mMatrix[index.x][index.y];
}

Node& Pathfinder::NodeAt(int x, int y)
{
	return mMatrix[x][y];
}

std::vector< std::vector<int> > Pathfinder::ComputePath()
{
	addToOpenList(mStartPoint);
	do
	{
		Point2D currentNodeI = findLowestFNode();
		addToClosedList(currentNodeI);
		processNeighbors(currentNodeI);
	} while (!NodeAt(mEndPoint).isOnClosedList && mOpenList.size() != 0);

	std::vector< std::vector<int> > path;
	path.resize(2);

	Node currentNode = NodeAt(mEndPoint);
	while (currentNode.parentIndex.x != mStartPoint.x || 
			currentNode.parentIndex.y != mStartPoint.y)
	{
		NodeAt(currentNode.parentIndex).value = 9;
		path[0].push_back(currentNode.parentIndex.x);
		path[1].push_back(currentNode.parentIndex.y);
		currentNode = NodeAt(currentNode.parentIndex);
	}

	
	return path;
}

int Pathfinder::ComputeH(Point2D index)
{
	return abs(mEndPoint.x - index.x) + abs(mEndPoint.y - index.y);
}

void Pathfinder::addToOpenList(Point2D index)
{
	mOpenList.push_back(index);
	NodeAt(index).openListIndex = mOpenList.size() - 1;
	NodeAt(index).isOnOpenList = true;
}

void Pathfinder::addToClosedList(Point2D index)
{
	mClosedList.push_back(index);

	int i = NodeAt(index).openListIndex;
	for (int i = NodeAt(index).openListIndex + 1; i < mOpenList.size(); i++)
		NodeAt(mOpenList[i]).openListIndex--;
	mOpenList.erase(mOpenList.begin() + NodeAt(index).openListIndex);


	NodeAt(index).isOnClosedList = true;
	NodeAt(index).isOnOpenList = false;
}

Point2D Pathfinder::findLowestFNode()
{
	Point2D selectedIndex = mOpenList[0];
	for (int i = 1; i < mOpenList.size(); i++)
	if (NodeAt(selectedIndex).F > NodeAt(mOpenList[i]).F)
		selectedIndex = NodeAt(mOpenList[i]).matrixIndex;

	return selectedIndex;
}

void Pathfinder::processNeighbors(Point2D index)
{
    bool diagonalMove = true;
	std::vector<Point2D> neighbors;
    neighbors.push_back(Point2D(index.x, index.y - 1)); // N
    neighbors.push_back(Point2D(index.x + 1, index.y)); // E
    neighbors.push_back(Point2D(index.x, index.y + 1)); // S
    neighbors.push_back(Point2D(index.x - 1, index.y)); // W

    if (diagonalMove)
    {
        if (NodeAt(neighbors[0]).value != 0 && NodeAt(neighbors[1]).value != 0)
            neighbors.push_back(Point2D(index.x + 1, index.y - 1)); // NE
        if (NodeAt(neighbors[1]).value != 0 && NodeAt(neighbors[2]).value != 0)
            neighbors.push_back(Point2D(index.x + 1, index.y + 1)); // SE
        if (NodeAt(neighbors[2]).value != 0 && NodeAt(neighbors[3]).value != 0)
            neighbors.push_back(Point2D(index.x - 1, index.y + 1)); // SW
        if (NodeAt(neighbors[3]).value != 0 && NodeAt(neighbors[0]).value != 0)
            neighbors.push_back(Point2D(index.x - 1, index.y - 1)); // NW
    }

    int movementCost;
	for (int i = 0; i < neighbors.size(); i++)
	{
        if (i <= 3) // for N, E, S, W
            movementCost = 10;
        else // for NE, SE, SW, NW
            movementCost = 14;

		Node* currentNode = &NodeAt(neighbors[i]);
		if (currentNode->value != 0)
		{
			if (!currentNode->isOnClosedList && !currentNode->isOnOpenList)
			{
				addToOpenList(neighbors[i]);
				currentNode->parentIndex = index;
                currentNode->G = NodeAt(index).G + movementCost;
				currentNode->H = ComputeH(currentNode->matrixIndex);
				currentNode->F = currentNode->G + currentNode->H;
			}
			else if (!currentNode->isOnClosedList && currentNode->isOnOpenList)
			{
                if (NodeAt(index).G + movementCost < currentNode->G)
				{
					currentNode->parentIndex = index;
                    currentNode->G = NodeAt(index).G + movementCost;
					currentNode->H = ComputeH(currentNode->matrixIndex);
					currentNode->F = currentNode->G + currentNode->H;
				}
			}
		}
	}
}
