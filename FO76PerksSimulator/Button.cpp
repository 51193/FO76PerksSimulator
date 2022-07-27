#include "Button.h"

Button::Button(float x, float y,
	float width, float height,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color idle_textcolor, sf::Color hover_textcolor, sf::Color active_textcolor,
	sf::Font* font, std::string text, bool have_outline)
	: font{ font },
	idle_color{ idle_color }, hover_color{ hover_color }, active_color{ active_color },
	idle_textcolor{ idle_textcolor }, hover_textcolor{ hover_textcolor }, active_textcolor{ active_textcolor },
	button_state{ BUTTON_IDLE } {
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	if (have_outline) {
		this->shape.setOutlineColor(sf::Color::Black);
		this->shape.setOutlineThickness(1.f);
	}
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(height / 3);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - (this->text.getCharacterSize() / 2.f)
	);

	this->text.setFillColor(this->idle_textcolor);
	this->shape.setFillColor(this->idle_color);
}

Button::~Button() {

}

const bool Button::isPressed() const {
	if (this->button_state == BUTTON_ACTIVE)return 1;
	return 0;
}

void Button::update(const sf::Vector2f& mousePos) {
	this->button_state = BUTTON_IDLE;
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->button_state = BUTTON_HOVER;
	}
	if (this->shape.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->button_state = BUTTON_ACTIVE;
	}
	this->updateColor();
}

void Button::updateColor() {
	switch (button_state)
	{
	case BUTTON_IDLE:
		this->shape.setFillColor(this->idle_color);
		this->text.setFillColor(this->idle_textcolor);
		break;
	case BUTTON_HOVER:
		this->shape.setFillColor(this->hover_color);
		this->text.setFillColor(this->hover_textcolor);
		break;
	case BUTTON_ACTIVE:
		this->shape.setFillColor(this->active_color);
		this->text.setFillColor(this->active_textcolor);
		break;
	default:
		std::cout << "正常来讲，是不可能看到这个的，除非你改了内存，还改歪了" << std::endl;
		break;
	}
}

void Button::render(sf::RenderTarget& target) {
	target.draw(this->shape);
	target.draw(this->text);
}

void Button::moveto(float x, float y) {
	this->shape.setPosition(x, y);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - (this->text.getCharacterSize() / 2.f)
	);
}

short unsigned int Button::getButtonState() {
	return button_state;
}
