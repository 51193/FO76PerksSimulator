#ifndef GAME_H
#define GAME_H

#include"State.h"

class Game {
public:

	//Ctor Dtor

	Game();
	virtual~Game();

	//功能

	void updateSFMLEvent();
	void update();
	void render();
	void run();

private:

	//变量

	sf::RenderWindow* sfwindow;
	sf::ContextSettings windowSettings;
	bool isFullscreen;

	sf::Event sfevent;
	std::vector<sf::VideoMode>videomode;

	sf::Font font;

	State* state;

	//初始化功能

	void initWindow();
	void initFont();

	void initState();
};

#endif