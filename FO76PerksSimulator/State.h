#ifndef STATE_H
#define STATE_H

#include"Body.h"

class State {
public:

	State(sf::RenderWindow* window, sf::Font* font);
	~State();

	void updateMousePositions();
	void update();
	void render(sf::RenderTarget* target = NULL);

	void initIcon();
	void initText();

private:

	sf::RenderWindow* window;

	sf::Text text1;
	sf::Text text2;

	sf::Texture texture;
	sf::Sprite icon;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	sf::Font* font;

	Body* body;
};

#endif