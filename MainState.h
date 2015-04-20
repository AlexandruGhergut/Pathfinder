#ifndef MAINSTATE_H
#define MAINSTATE_H

#include "NodeShape.h"

class MainState
{
public:
	MainState(sf::RenderWindow* window);
	void initialize(sf::RenderWindow* window);
	void draw(sf::RenderWindow& window);
	void handleInput(sf::Event& event, sf::RenderWindow& window);

private:
	int mWSizeX;
	int mWSizeY;
	int mRows;
	int mColumns;
	std::vector< std::vector<NodeShape> > mNodeMatrix;
	void resizeMatrix(int rows, int columns);
	int activeKey;
	void computePath();
	void drawPath(std::vector< std::vector<int> >& path);
	sf::RenderWindow* mWindow;
    void resetMatrix();
};

#endif
