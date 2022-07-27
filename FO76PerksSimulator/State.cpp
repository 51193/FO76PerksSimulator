#include "State.h"

State::State(sf::RenderWindow* window, sf::Font* font) :window(window), font{ font }{
	this->initIcon();
	this->initText();
	body = new Body(this->font);
}

State::~State() {
	delete this->body;
}

void State::updateMousePositions() {
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::update() {
	this->updateMousePositions();
	this->body->update(this->mousePosView);
}

void State::render(sf::RenderTarget* target) {
	this->body->render(*target);
	this->window->draw(this->icon);
	target->draw(this->text1);
	target->draw(this->text2);
}

void State::initIcon() {
	this->texture.loadFromFile("Recources\\BoS.png");
	this->icon.setTexture(this->texture);
	this->icon.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
	this->icon.setPosition(460, 40);
	this->icon.setColor(sf::Color::Color(255, 255, 255, 64));
}

void State::initText() {
	this->text1.setCharacterSize(15);
	this->text1.setFillColor(sf::Color::Black);
	this->text1.setFont(*this->font);
	this->text1.setPosition(0, 0);
	this->text1.setString(L"本软件完全开源免费");


	this->text2.setCharacterSize(15);
	this->text2.setFillColor(sf::Color::Black);
	this->text2.setFont(*this->font);
	this->text2.setPosition(0, this->window->getSize().y - this->text2.getCharacterSize() - 5);
	this->text2.setString(L"东海岸钢铁兄弟会出品（QQ:1025056083）");
}
