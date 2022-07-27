#ifndef PERK_H
#define PERK_H

#include<iostream>
#include<fstream>
#include<map>
#include<vector>

#include"SFML/Audio.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Network.hpp"

class Perk {
	friend class Thumbnail;
public:

	Perk(
		float x,
		float y,
		float width,
		float height,
		sf::Font* font,
		const wchar_t* perk_title,
		const wchar_t* perk_intro,
		sf::Color title_color,
		int cost,
		int key);
	~Perk();

	void render(sf::RenderTarget& target);

	void moveto(float x, float y);

	int getCost();
	int getKey();

private:

	int key;

	sf::RectangleShape outline;

	sf::RectangleShape rect_cost;
	int int_cost;
	sf::Text cost;

	sf::RectangleShape rect_title;
	sf::Text title;

	sf::RectangleShape rect_intro;
	sf::Text intro;

	sf::Font* font;
};

#endif