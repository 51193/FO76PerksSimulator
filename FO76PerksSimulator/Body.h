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
	void updateButtons(sf::Vector2f& mousePos);//��δ���д���ˣ��⹦�ܴ󲿷ֶ�Ӧ�÷�Title��������ø��ˣ����þ���
	void updateIcons();//�⹦��ҲӦ�÷�Title��
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
	void initButtons();//�⹦�ܴ󲿷�Ҳ��Ӧ�÷�Title��

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