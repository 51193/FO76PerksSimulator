#ifndef GAME_H
#define GAME_H

#include"State.h"

class Game {
public:

	//Ctor Dtor

	Game();
	virtual~Game();

	//����

	void updateSFMLEvent();
	void update();
	void render();
	void run();

private:

	//����

	sf::RenderWindow* sfwindow;
	sf::ContextSettings windowSettings;
	bool isFullscreen;

	sf::Event sfevent;
	std::vector<sf::VideoMode>videomode;

	sf::Font font;

	State* state;

	//��ʼ������

	void initWindow();
	void initFont();

	void initState();
};

#endif