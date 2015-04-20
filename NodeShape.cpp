#include "NodeShape.h"

NodeShape::NodeShape()
{
	mTextureManager.load("walkableSquare", "img/walkableSquare.png");
	mTextureManager.load("obstacleSquare", "img/obstacleSquare.png");
	mTextureManager.load("startSquare", "img/startSquare.png");
	mTextureManager.load("endSquare", "img/endSquare.png");
    mTextureManager.load("pathSquare", "img/pathSquare.png");
	mNodeState = walkable;
	mShape.setTexture(mTextureManager.get("walkableSquare"));
	mPosition = sf::Vector2f(0.0f, 0.0f);
	mShape.setPosition(mPosition);
}

void NodeShape::draw(sf::RenderWindow& window)
{
	window.draw(mShape);
}

void NodeShape::captureMouseClick(sf::RenderWindow& window, int selectType)
{
	/*selectType values
	0 = walkable, 1 = osbtacle, 2 = start, 3 = end*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		sf::FloatRect bounds = mShape.getGlobalBounds();

		if (bounds.contains(mouse))
		{
			if (selectType == 0)
			{
				mShape.setTexture(mTextureManager.get("walkableSquare"));
				mNodeState = walkable;
			}
			else if (selectType == 1)
			{
				mShape.setTexture(mTextureManager.get("obstacleSquare"));
				mNodeState = obstacle;
			}
			else if (selectType == 2)
			{
				mShape.setTexture(mTextureManager.get("startSquare"));
				mNodeState = start;
			}
			else if (selectType == 3)
			{
				mShape.setTexture(mTextureManager.get("endSquare"));
				mNodeState = end;
			}
		}
	}
}

void NodeShape::setPosition(sf::Vector2f position)
{
	mPosition = position;
	mShape.setPosition(mPosition);
}

sf::FloatRect NodeShape::getGlobalBounds()
{
	return mShape.getGlobalBounds();
}

void NodeShape::setTexture(std::string texture)
{
	mShape.setTexture(mTextureManager.get(texture));
    if (texture == "walkableSquare")
        mNodeState = walkable;
    else if (texture == "obstacleSquare")
        mNodeState = obstacle;
    else if (texture == "startSquare")
        mNodeState = start;
    else if (texture == "endSquare")
        mNodeState = end;
}

sf::Vector2f NodeShape::getPosition()
{
	return mShape.getPosition();
}


