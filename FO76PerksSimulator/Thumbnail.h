#ifndef THUMBNAIL_H
#define THUMBNAIL_H

#include"Card.h"

class Thumbnail {
public:

	Thumbnail(Perk& perk);
	~Thumbnail();

	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget& target);

	float getWidth();
	float getHeight();
	int getCost();
	int getKey();
	sf::Vector2f getPosition();

	void setPosition(float x, float y);

	bool isPressed();

private:
	int key;

	sf::RectangleShape rect_cost;
	int int_cost;
	sf::Text cost;

	sf::RectangleShape rect_title;
	sf::Text title;

	sf::Font* font;

	Button* button;
};

#endif