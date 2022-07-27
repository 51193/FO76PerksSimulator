#include "Game.h"

Game::Game() : sfwindow{ nullptr }, isFullscreen{ 0 } {
	this->initWindow();
	this->initFont();
	this->initState();
}

Game::~Game() {
	delete this->sfwindow;
	delete this->state;
}

void Game::updateSFMLEvent() {
	while (this->sfwindow->pollEvent(sfevent)) {
		if (this->sfevent.type == sf::Event::Closed) {
			this->sfwindow->close();
		}
	}
}

void Game::update() {

	this->updateSFMLEvent();

	this->state->update();

}

void Game::render() {
	this->sfwindow->clear(sf::Color::White);

	this->state->render(this->sfwindow);

	this->sfwindow->display();
}

void Game::run() {
	while (this->sfwindow->isOpen()) {
		this->update();
		this->render();
	}
}

void Game::initWindow() {

	std::ifstream input("Config/window.ini", std::ios::in);
	this->videomode = sf::VideoMode::getFullscreenModes();

	std::string title = "Unnamed";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	unsigned int framerate_limit{ 120 };
	bool vertical_sync_enabled{ 0 };
	unsigned int antialiasing_level{ 0 };

	if (input.is_open()) {
		std::getline(input, title);
		input >> window_bounds.width >> window_bounds.height;
		input >> isFullscreen;
		input >> framerate_limit;
		input >> vertical_sync_enabled;
		input >> antialiasing_level;


		this->windowSettings.antialiasingLevel = antialiasing_level;
		if (this->isFullscreen) {
			this->sfwindow = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
		}
		else {
			this->sfwindow = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
		}
		this->sfwindow->setFramerateLimit(framerate_limit);
		this->sfwindow->setVerticalSyncEnabled(vertical_sync_enabled);
	}
	else {
		std::ofstream output("Config/window.ini", std::ios::out);
		output << "You forgot to name it" << std::endl;
		output << sf::VideoMode::getDesktopMode().width << std::endl;
		output << sf::VideoMode::getDesktopMode().height << std::endl;
		output << false << std::endl;
		output << 120 << std::endl;
		output << false << std::endl;
		output << 0 << std::endl;
		output.close();
		initWindow();
	}
	input.close();
}

void Game::initFont() {
	font.loadFromFile("Fonts/SourceHanSansHWSC-Regular.otf");
}

void Game::initState() {
	this->state = new State(this->sfwindow, &this->font);
}