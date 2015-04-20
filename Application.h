#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include "MainState.h"


class Application
{
public:
	Application();
	void run();

private:
	enum GameState {mainState};
	GameState gameState;
	MainState* mainstate;
	void processEvents();
	void update();
	void render();

	sf::RenderWindow mWindow;
	sf::View mView;
};
#endif
