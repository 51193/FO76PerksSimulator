#ifndef CARD_H
#define CARD_H

#include"Button.h"
#include"Perk.h"

class Card {
public:

	Card(float x,
		float y,
		float width,
		float height,
		sf::Font* font,
		const wchar_t* perk_title,
		sf::Color title_color,
		int key);
	~Card();

	void update(sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

	void updatePerk();

	void moveto(float x, float y);

	void addLevel(const wchar_t* perk_intro, int cost);
	void finishAddingLevel();

	bool isPressed();
	Perk* selectedPerk();
	Perk* getPerk(int i);

	int getKey();

private:

	int key;

	float x;
	float y;
	float width;
	float height;
	sf::Font* font;
	const wchar_t* perk_title;
	sf::Color title_color;

	short int max_level;

	std::vector<Perk*>perks;
	std::vector<Button*>buttons;

	Perk* active_perk;

};

#endif