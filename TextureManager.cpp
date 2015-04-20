#include "TextureManager.h"

void TextureManager::load(std::string id, const std::string& filename)
{
	//std::unique_ptr<sf::Texture> texture(new sf::Texture());
	//texture->loadFromFile(filename);

	//mTextureMap.insert(std::make_pair(id, std::move(texture)));
	sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(filename);

	mTextureMap[id] = texture;
}

sf::Texture& TextureManager::get(std::string id)
{
	/*auto found = mTextureMap.find(id);
	return *found->second;*/

	return *mTextureMap[id];
}
