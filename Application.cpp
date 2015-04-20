#include "Application.h"

Application::Application() : mWindow(sf::VideoMode(1024, 768), "Pathfinder")
{
	gameState = mainState;
	mView.setCenter(sf::Vector2f(800 / 2, 600 / 2)); // hard coded
	mView.setSize(sf::Vector2f(800, 600)); // hard coded
	//mView.setViewport(sf::FloatRect(0.25f, 0.25f, 0.5f, 0.5f));
	mWindow.setView(mView);
	mWindow.setFramerateLimit(30);
	if (gameState == mainState)
		mainstate = new MainState(&mWindow); // to do - destructor

}

void Application::run()
{
	while (mWindow.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Application::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();
		if (mainState == gameState)
		{
			mainstate->handleInput(event, mWindow);

		}
	}
}

void Application::update()
{

}

void Application::render()
{
	mWindow.clear();
	if (gameState == mainState)
		mainstate->draw(mWindow);
	mWindow.display();
}