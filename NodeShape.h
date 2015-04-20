#ifndef NODESHAPE_H
#define NODESHAPE_H

#include "TextureManager.h"

// VERY POOR IMPLEMENTATION 
// NEEDS TO BE REDESIGNED

class NodeShape
{
public:
	NodeShape();
	void draw(sf::RenderWindow& window);
	void captureMouseClick(sf::RenderWindow& window, int selectType);
	void setPosition(sf::Vector2f posiiton);
	sf::FloatRect getGlobalBounds();
	enum NodeState{ walkable, obstacle, start, end, path };
	NodeState mNodeState;
	void setTexture(std::string);
	sf::Vector2f getPosition();
	int getNodeState()
	{
		if (mNodeState == walkable)
			return 1;
		else if (mNodeState == obstacle)
			return 0;
		else if (mNodeState == start)
			return 2;
		else if (mNodeState == end)
			return 3;
	}
private:

	sf::Sprite mShape;
	TextureManager mTextureManager;
	sf::Vector2f mPosition;
};

#endif
