#ifndef BUTTON_H
#define BUTTON_H

#include<iostream>
#include<fstream>
#include<map>

#include"SFML/Audio.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Network.hpp"

enum button_state {
	BUTTON_IDLE = 0,
	BUTTON_HOVER,
	BUTTON_ACTIVE
};

class Button {
public:
	Button(float x, float y,
		float width, float height,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
		sf::Color idle_textcolor, sf::Color hover_textcolor, sf::Color active_textcolor,
		sf::Font* font, std::string text, bool have_outline = false);
	~Button();

	const bool isPressed() const;

	//¹¦ÄÜ

	void update(const sf::Vector2f& mousePos);
	void updateColor();
	void render(sf::RenderTarget& target);

	void moveto(float x, float y);

	short unsigned int getButtonState();

private:
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idle_color;
	sf::Color hover_color;
	sf::Color active_color;

	sf::Color idle_textcolor;
	sf::Color hover_textcolor;
	sf::Color active_textcolor;

	short unsigned int button_state;

};

#endif