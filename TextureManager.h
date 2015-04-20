#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

// TODO - possible memory leak
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
	void load(std::string id, const std::string& filename);
	sf::Texture& get(std::string id);
private:
	/*std::map<std::string,
		std::unique_ptr<sf::Texture>> mTextureMap;*/

	std::map < std::string, sf::Texture*> mTextureMap;
	
};
#endif