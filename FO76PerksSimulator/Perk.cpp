#include "Perk.h"

Perk::Perk(
	float x,
	float y,
	float width,
	float height,
	sf::Font* font,
	const wchar_t* perk_title,
	const wchar_t* perk_intro,
	sf::Color title_color,
	int cost,
	int key)
	:key{ key }, font { font }, int_cost{ cost } {
	this->outline.setPosition(sf::Vector2f(x, y));
	this->outline.setSize(sf::Vector2f(width, height));
	this->outline.setFillColor(sf::Color::Transparent);
	this->outline.setOutlineColor(sf::Color::Black);
	this->outline.setOutlineThickness(1.f);

	float cost_width{ height*2 / 15 };
	float cost_blank{ height / 30 };

	this->rect_cost.setPosition(sf::Vector2f(x + cost_blank, y + cost_blank));
	this->rect_cost.setSize(sf::Vector2f(cost_width, cost_width));
	this->rect_cost.setFillColor(sf::Color::White);
	this->rect_cost.setOutlineColor(sf::Color::Black);
	this->rect_cost.setOutlineThickness(1.f);
	this->cost.setFont(*this->font);
	this->cost.setString(std::to_string(cost));
	this->cost.setCharacterSize(cost_width * 2 / 3);
	this->cost.setFillColor(sf::Color::Black);
	this->cost.setPosition(
		this->rect_cost.getPosition().x + (this->rect_cost.getGlobalBounds().width / 2.f) - (this->cost.getGlobalBounds().width / 2.f),
		this->rect_cost.getPosition().y + (this->rect_cost.getGlobalBounds().height / 2.f) - (this->cost.getCharacterSize() / 2.f)
	);
	
	this->rect_title.setPosition(sf::Vector2f(x, y));
	this->rect_title.setSize(sf::Vector2f(width, height / 5));
	this->rect_title.setFillColor(title_color);
	this->title.setFont(*this->font);
	this->title.setString(perk_title);
	this->title.setCharacterSize(height / 16);
	this->title.setFillColor(sf::Color::White);
	this->title.setPosition(
		this->rect_title.getPosition().x + cost_width + 2 * cost_blank ,
		this->rect_title.getPosition().y + (this->rect_title.getGlobalBounds().height / 2.f) - (this->title.getCharacterSize() / 2.f)
	);


	this->rect_intro.setPosition(sf::Vector2f(x, y + this->rect_title.getGlobalBounds().height));
	this->rect_intro.setSize(sf::Vector2f(width, height - this->rect_title.getGlobalBounds().height));
	this->rect_intro.setFillColor(sf::Color::Color(220, 220, 220));
	this->intro.setFont(*this->font);
	this->intro.setString(perk_intro);
	this->intro.setCharacterSize(title.getCharacterSize());
	this->intro.setFillColor(sf::Color::Black);
	this->intro.setPosition(sf::Vector2f(x + 5, (y + this->rect_title.getGlobalBounds().height) + 5));

}

Perk::~Perk() {

}

void Perk::render(sf::RenderTarget& target) {
	target.draw(this->outline);
	target.draw(this->rect_title);
	target.draw(this->title);
	target.draw(this->rect_intro);
	target.draw(this->intro);
	target.draw(this->rect_cost);
	target.draw(this->cost);
}

void Perk::moveto(float x, float y) {
	this->outline.setPosition(sf::Vector2f(x, y));

	float cost_width{ this->outline.getGlobalBounds().height * 2 / 15 };
	float cost_blank{ this->outline.getGlobalBounds().height / 30 };

	this->rect_cost.setPosition(sf::Vector2f(x + cost_blank, y + cost_blank));
	this->cost.setPosition(
		this->rect_cost.getPosition().x + (this->rect_cost.getGlobalBounds().width / 2.f) - (this->cost.getGlobalBounds().width / 2.f),
		this->rect_cost.getPosition().y + (this->rect_cost.getGlobalBounds().height / 2.f) - (this->cost.getCharacterSize() / 2.f)
	);

	this->rect_title.setPosition(sf::Vector2f(x, y));
	this->title.setPosition(
		this->rect_title.getPosition().x + cost_width + 2 * cost_blank,
		this->rect_title.getPosition().y + (this->rect_title.getGlobalBounds().height / 2.f) - (this->title.getCharacterSize() / 2.f)
	);

	this->rect_intro.setPosition(sf::Vector2f(x, y + this->rect_title.getGlobalBounds().height));
	this->intro.setPosition(sf::Vector2f(x + 5, (y + this->rect_title.getGlobalBounds().height) + 5));
}

int Perk::getCost() {
	return this->int_cost;
}

int Perk::getKey() {
	return this->key;
}
