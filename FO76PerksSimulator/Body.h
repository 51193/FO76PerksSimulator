#ifndef BODY_H
#define BODY_H

#include"Title.h"

class Body {
public:
	
	Body(sf::Font* font);
	~Body();

	void update(sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

	void updateBackground();
	void updateButtons(sf::Vector2f& mousePos);//这段代码写烂了，这功能大部分都应该放Title里，但是懒得改了，能用就行
	void updateIcons();//这功能也应该放Title里
	void updateCardsNumber();
	void updateActiveCards();
	void updateCardsPosition();
	void updateSelectedCard();
	void updateCards(sf::Vector2f& mousePos);
	void updateBoolean();

	void renderBackground(sf::RenderTarget& target);
	void renderButtons(sf::RenderTarget& target);
	void renderActiveCards(sf::RenderTarget& target);

	void initBackground();
	void initButtons();//这功能大部分也都应该放Title里

	void initCards();

	void initStrenth();
	void initPerception();
	void initEndurance();
	void initCharisma();
	void initIntelligence();
	void initAgility();
	void initLuck();
	void initLegend();

private:

	Title* title;

	int active_special;

	Button* left;
	Button* right;

	std::map<std::string, Button*>buttons;

	sf::RectangleShape background;

	std::vector<Card*>strenth;
	std::vector<Card*>perception;
	std::vector<Card*>endurance;
	std::vector<Card*>charisma;
	std::vector<Card*>intelligence;
	std::vector<Card*>agility;
	std::vector<Card*>luck;
	std::vector<Card*>legend;

	std::vector<Card*>active_cards;

	int page_number;
	int cards_per_page;

	sf::Font* font;

	bool ready_for_press;

};

#endif