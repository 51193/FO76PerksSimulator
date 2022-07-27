#include "Thumbnail.h"

Thumbnail::Thumbnail(Perk& perk)
	:key{ perk.key }, int_cost{ perk.int_cost }, font{ perk.font },
	rect_title{ perk.rect_title }, title{ perk.title },
	rect_cost{ perk.rect_cost }, cost{ perk.cost } {

	this->rect_title.setPosition(sf::Vector2f(1920, 1080));
	this->rect_title.setSize(sf::Vector2f(this->rect_title.getSize().x, this->rect_title.getSize().y / 2));
	this->rect_title.setOutlineColor(sf::Color::Black);
	this->rect_title.setOutlineThickness(1.f);

	this->title.setCharacterSize(this->title.getCharacterSize());
	this->title.setPosition(
		this->rect_title.getPosition().x + (this->rect_title.getSize().y + this->rect_title.getOutlineThickness()) + (this->rect_title.getSize().x - this->rect_title.getSize().y - this->rect_title.getOutlineThickness()) / 2.f - this->title.getGlobalBounds().width / 2.f,
		this->rect_title.getPosition().y + (this->rect_title.getSize().y / 2.f) - (this->title.getCharacterSize() / 2)
	);

	this->rect_cost.setPosition(sf::Vector2f(1920, 1080));
	this->rect_cost.setSize(sf::Vector2f(this->rect_title.getSize().y, this->rect_title.getSize().y));
	this->cost.setCharacterSize(this->rect_cost.getGlobalBounds().height* 0.7);
	this->cost.setPosition(
		this->rect_cost.getPosition().x + (this->rect_cost.getGlobalBounds().width / 2.f) - (this->cost.getGlobalBounds().width / 2.f),
		this->rect_cost.getPosition().y + (this->rect_cost.getGlobalBounds().height / 2.f) - (this->cost.getCharacterSize() / 2.f)
	);


	this->button = new Button(
		this->rect_title.getPosition().x,
		this->rect_title.getPosition().y,
		this->rect_title.getSize().x,
		this->rect_title.getSize().y,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		this->font,
		"\0"
	);
}

Thumbnail::~Thumbnail() {
	delete this->button;
}

void Thumbnail::update(sf::Vector2f mousePos) {
	this->button->update(mousePos);
}

void Thumbnail::render(sf::RenderTarget& target) {
	target.draw(rect_title);
	target.draw(title);
	target.draw(rect_cost);
	target.draw(cost);
	this->button->render(target);
}

float Thumbnail::getWidth() {
	return this->rect_title.getGlobalBounds().width;
}

float Thumbnail::getHeight() {
	return this->rect_title.getGlobalBounds().height;
}

int Thumbnail::getCost() {
	return this->int_cost;
}

int Thumbnail::getKey() {
	return this->key;
}

sf::Vector2f Thumbnail::getPosition() {
	return this->rect_title.getPosition();
}

void Thumbnail::setPosition(float x, float y) {
	float dis_x{ x - this->rect_title.getPosition().x };
	float dis_y{ y - this->rect_title.getPosition().y };

	this->rect_title.setPosition(sf::Vector2f(this->rect_title.getPosition().x + dis_x, this->rect_title.getPosition().y + dis_y));
	this->title.setPosition(sf::Vector2f(this->title.getPosition().x + dis_x, this->title.getPosition().y + dis_y));

	this->rect_cost.setPosition(sf::Vector2f(this->rect_cost.getPosition().x + dis_x, this->rect_cost.getPosition().y + dis_y));
	this->cost.setPosition(sf::Vector2f(this->cost.getPosition().x + dis_x, this->cost.getPosition().y + dis_y));

	delete this->button;
	this->button = new Button(
		this->rect_title.getPosition().x,
		this->rect_title.getPosition().y,
		this->rect_title.getSize().x,
		this->rect_title.getSize().y,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		this->font,
		"\0"
	);
}

bool Thumbnail::isPressed() {
	if (this->button->isPressed())return true;
	else return false;
}