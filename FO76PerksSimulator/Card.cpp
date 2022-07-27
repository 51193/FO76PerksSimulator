#include "Card.h"

Card::Card(float x,
	float y,
	float width,
	float height,
	sf::Font* font,
	const wchar_t* perk_title,
	sf::Color title_color,
	int key)
	:key{ key },
	x{ x },
	y{ y },
	width{ width },
	height{ height },
	font{ font },
	perk_title{ perk_title },
	title_color{ title_color },
	max_level{ 0 },
	active_perk{ NULL } {
}

Card::~Card() {
	while (!perks.empty()) {
		delete* perks.rbegin();
		perks.pop_back();
	}
	while (!buttons.empty()) {
		delete* buttons.rbegin();
		buttons.pop_back();
	}
}

void Card::update(sf::Vector2f& mousePos) {
	for (auto& i : this->buttons) {
		i->update(mousePos);
	}
	this->updatePerk();
}

void Card::render(sf::RenderTarget& target) {
	active_perk->render(target);
	for (auto& i : this->buttons) {
		i->render(target);
	}
}

void Card::updatePerk() {
	active_perk = perks[0];
	for (size_t i{ 0 }; i < buttons.size(); i++) {
		if (buttons[i]->getButtonState() == BUTTON_HOVER || buttons[i]->getButtonState() == BUTTON_ACTIVE) {
			active_perk = perks[i];
		}
	}
}

void Card::moveto(float x, float y) {
	this->x = x;
	this->y = y;
	float button_width{ this->width / 5 };
	for (size_t i{ 0 }; i < buttons.size(); i++) {
		this->buttons[i]->moveto(
			this->x + button_width * i,
			this->y + this->height - button_width);
	}
	for (auto& i : this->perks) {
		i->moveto(x, y);
	}
}

void Card::addLevel(const wchar_t* perk_intro, int cost) {
	perks.push_back(new Perk(this->x, this->y, this->width, this->height, this->font, this->perk_title, perk_intro, this->title_color, cost, this->key));
	max_level++;
}

void Card::finishAddingLevel() {

	float button_width{ this->width / 5 };

	for (size_t i{ 0 }; i < max_level; i++) {
		this->buttons.push_back(new Button(
			this->x + button_width * i,
			this->y + this->height - button_width,
			button_width,
			button_width,
			sf::Color::Color(150, 150, 150),
			sf::Color::Color(150, 150, 150, 128),
			sf::Color::Color(150, 150, 150, 0),
			sf::Color::Black,
			sf::Color::Black,
			sf::Color::Black,
			this->font,
			std::to_string(i + 1),
			true
		));
	}
}

bool Card::isPressed() {
	for (size_t i{ 0 }; i < this->buttons.size(); i++) {
		if (this->buttons[i]->isPressed())return true;
	}
	return false;
}

Perk* Card::selectedPerk() {
	for (size_t i{ 0 }; i < this->buttons.size(); i++) {
		if (this->buttons[i]->isPressed())return this->perks[i];
	}
	return NULL;
}

Perk* Card::getPerk(int i) {
	if (i < this->perks.size()) {
		return this->perks[i];
	}
	else return nullptr;
}

int Card::getKey() {
	return this->key;
}
