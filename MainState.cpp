#include "MainState.h"
#include "Pathfinder.h"
#include <iostream>

MainState::MainState(sf::RenderWindow* window)
{
	mWindow = window;
	mRows = 0;
	mColumns = 0;
	resizeMatrix(5, 5);
	activeKey = 0;
}


void MainState::initialize(sf::RenderWindow* window)
{
	mWindow = window;
}

void MainState::resizeMatrix(int rows, int columns)
{
    if (rows <= 0 || columns <= 0)
        return;
	// performance can be greatly improved
	mNodeMatrix.resize(rows);
	for (int i = 0; i < rows; i++)
		mNodeMatrix[i].resize(columns);

    for (int i = 0; i < rows; i++)
	for (int j = 0; j < columns; j++)
	{
		mNodeMatrix[i][j].setPosition(
			sf::Vector2f(j * mNodeMatrix[i][j].getGlobalBounds().width,
			i * mNodeMatrix[i][j].getGlobalBounds().height));
	}

	NodeShape* lastRight = &mNodeMatrix[0][columns - 1];
	NodeShape* lastBottom = &mNodeMatrix[rows - 1][0];

	// Adjust view
	float test = lastRight->getPosition().x + lastRight->getGlobalBounds().width;
	sf::View view = mWindow->getView();
	if (test > mWindow->getView().getSize().x)
		view.reset(sf::FloatRect(0, 0, 
					view.getSize().x + (test - view.getSize().x), 
					view.getSize().y));
	else if (test < mWindow->getView().getSize().x)
		view.reset(sf::FloatRect(0, 0,
		view.getSize().x - (view.getSize().x - test),
		view.getSize().y));
	mWindow->setView(view);
		
	/*while (lastRight->getPosition().x + lastRight->getGlobalBounds().width >  // this needs to be checked out
		mWindow->getView().getSize().x)
	{
		sf::View view = mWindow->getView();
		view.reset(sf::FloatRect(0, 0, view.getSize().x + 1, view.getSize().y));
		//std::cout << view.getSize().x << " " << lastRight->getPosition().y << " " << lastRight->getGlobalBounds().width << std::endl;
		//view.setViewport(sf::FloatRect(0.25f, 0.25f, 0.5f, 0.5f));
		//view.setSize(view.getSize().x + 1, view.getSize().y);
		mWindow->setView(view);
	}*/


	test = lastBottom->getPosition().y + lastBottom->getGlobalBounds().height;
	if (test > mWindow->getView().getSize().y)
		view.reset(sf::FloatRect(0, 0,
		view.getSize().x,
		view.getSize().y +(test - view.getSize().y)));
	else if (test < mWindow->getView().getSize().y)
		view.reset(sf::FloatRect(0, 0,
		view.getSize().x,
		view.getSize().y - (view.getSize().y - test)));
	mWindow->setView(view);
	/*
	while (lastBottom->getPosition().y + lastBottom->getGlobalBounds().height >
		mWindow->getView().getSize().y)
	{
		sf::View view = mWindow->getView();
		//view.setViewport(sf::FloatRect(0.25f, 0.25f, 0.5f, 0.5f));
		view.reset(sf::FloatRect(0, 0, view.getSize().x, view.getSize().y + 1));
		//view.setSize(view.getSize().x, view.getSize().y + 1);
		std::cout << view.getSize().y << " " << lastBottom->getPosition().x << " " << lastBottom->getGlobalBounds().height << std::endl;
		mWindow->setView(view);
	}
	*/

	//useless hacks above
	mRows = rows;
	mColumns = columns;
}

void MainState::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < mRows; i++)
	for (int j = 0; j < mColumns; j++)
		mNodeMatrix[i][j].draw(window);
}

void MainState::handleInput(sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::F1)
			activeKey = 0;
		else if (event.key.code == sf::Keyboard::F2)
			activeKey = 1;
		else if (event.key.code == sf::Keyboard::F3)
			activeKey = 2;
		else if (event.key.code == sf::Keyboard::F4)
			activeKey = 3;
		else if (event.key.code == sf::Keyboard::F5)
		{
			activeKey = 4; // compute
			computePath();
		}
        else if (event.key.code == sf::Keyboard::F6)
        {
            resetMatrix();
        }
		else  if (event.key.code == sf::Keyboard::Up)
			resizeMatrix(mRows + 1, mColumns);
		else if (event.key.code == sf::Keyboard::Down)
			resizeMatrix(mRows - 1, mColumns);
		else if (event.key.code == sf::Keyboard::Left)
			resizeMatrix(mRows, mColumns - 1);
		else if (event.key.code == sf::Keyboard::Right)
			resizeMatrix(mRows, mColumns + 1);
	}
	else if (event.key.code == sf::Mouse::Left)
	{
		for (int i = 0; i < mNodeMatrix.size(); i++)
		for (int j = 0; j < mNodeMatrix[i].size(); j++)
			mNodeMatrix[i][j].captureMouseClick(window, activeKey);
	}
	
}

void MainState::computePath()
{
	int startPointX, startPointY;
	int endPointX, endPointY;
	std::vector< std::vector<int> > pathMatrix;
	pathMatrix.resize(mRows);
	for (int i = 0; i < mRows; i++)
		pathMatrix[i].resize(mColumns);

	for (int i = 0; i < mRows; i++)
	for (int j = 0; j < mColumns; j++)
	{
		if (mNodeMatrix[i][j].getNodeState() == 1) // walkable
			pathMatrix[i][j] = 1;
		else if (mNodeMatrix[i][j].getNodeState() == 0)
			pathMatrix[i][j] = 0;
		else if (mNodeMatrix[i][j].getNodeState() == 2)
		{
			pathMatrix[i][j] = 2;
			startPointX = i;
			startPointY = j;
		}
		else if (mNodeMatrix[i][j].getNodeState() == 3)
		{
			pathMatrix[i][j] = 3;
			endPointX = i;
			endPointY = j;
		}
	}
	
	Pathfinder pathfinder(startPointX + 1, startPointY + 1, endPointX + 1, endPointY + 1,
		pathMatrix);
    std::vector< std::vector<int> > result = pathfinder.ComputePath();
    drawPath(result);
	
}

void MainState::drawPath(std::vector< std::vector<int> >& path)
{
	for (int j = 0; j < path[0].size(); j++)
	{
		path[0][j]--;
		path[1][j]--;
		mNodeMatrix[path[0][j]][path[1][j]].setTexture("pathSquare");
	}
}

void MainState::resetMatrix()
{
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            mNodeMatrix[i][j].setTexture("walkableSquare");
}

