#include "Body.h"

Body::Body(sf::Font* font) :font{ font }, active_special{ _Strenth }, page_number{ 1 }, cards_per_page{ 0 }, ready_for_press{ true } {
	title = new Title(this->font);
	this->initBackground();
	this->initButtons();
	this->initCards();
}

Body::~Body() {
	while (!this->strenth.empty()) {
		delete* this->strenth.rbegin();
		this->strenth.pop_back();
	}
	while (!this->perception.empty()) {
		delete* this->perception.rbegin();
		this->perception.pop_back();
	}
	while (!this->endurance.empty()) {
		delete* this->endurance.rbegin();
		this->endurance.pop_back();
	}
	while (!this->charisma.empty()) {
		delete* this->charisma.rbegin();
		this->charisma.pop_back();
	}
	while (!this->intelligence.empty()) {
		delete* this->intelligence.rbegin();
		this->intelligence.pop_back();
	}
	while (!this->agility.empty()) {
		delete* this->agility.rbegin();
		this->agility.pop_back();
	}
	while (!this->luck.empty()) {
		delete* this->luck.rbegin();
		this->luck.pop_back();
	}
	while (!this->legend.empty()) {
		delete* this->legend.rbegin();
		this->legend.pop_back();
	}
	for (auto& i : this->buttons) {
		delete i.second;
	}
	delete this->title;
	delete this->left;
	delete this->right;
}

void Body::update(sf::Vector2f& mousePos) {
	this->updateButtons(mousePos);
	this->updateBackground();
	this->title->update(mousePos);
	this->updateIcons();
	this->updateCardsNumber();
	this->updateActiveCards();
	this->updateCardsPosition();
	this->updateCards(mousePos);
	this->updateSelectedCard();
	this->updateBoolean();
}

void Body::render(sf::RenderTarget& target) {
	this->renderBackground(target);
	this->title->render(target);
	this->renderActiveCards(target);
	this->renderButtons(target);
}

void Body::updateBackground() {
	if (this->title->getHeight() > 760) {
		this->background.setPosition(0, 760);
		this->background.setSize(sf::Vector2f(1920, 320));
	}
	else {
		this->background.setPosition(0, this->title->getHeight());
		this->background.setSize(sf::Vector2f(1920, 1080 - this->title->getHeight()));
	}
}

void Body::updateButtons(sf::Vector2f& mousePos) {
	for (auto& i : this->buttons) {
		i.second->update(mousePos);
	}
	left->update(mousePos);
	right->update(mousePos);

	left->moveto(875, this->title->getHeight() + 10);
	right->moveto(965, this->title->getHeight() + 10);

	if (buttons.at("Strenth")->isPressed()) {
		this->active_special = _Strenth;
		this->page_number = 1;
	}
	else if (buttons.at("Perception")->isPressed()) {
		this->active_special = _Perception;
		this->page_number = 1;
	}
	else if (buttons.at("Endurance")->isPressed()) {
		this->active_special = _Endurance;
		this->page_number = 1;
	}
	else if (buttons.at("Charisma")->isPressed()) {
		this->active_special = _Charisma;
		this->page_number = 1;
	}
	else if (buttons.at("Intelligence")->isPressed()) {
		this->active_special = _Intelligence;
		this->page_number = 1;
	}
	else if (buttons.at("Agility")->isPressed()) {
		this->active_special = _Agility;
		this->page_number = 1;
	}
	else if (buttons.at("Luck")->isPressed()) {
		this->active_special = _Luck;
		this->page_number = 1;
	}
	else if (buttons.at("Legend")->isPressed()) {
		this->active_special = _Legend;
		this->page_number = 1;
	}

	if (ready_for_press) {
		if (this->right->isPressed()) {
			switch (this->active_special) {
			case _Strenth:
				if (this->strenth.size() > this->page_number * this->cards_per_page) this->page_number++;
				break;
			case _Perception:
				if (this->perception.size() > this->page_number * this->cards_per_page) this->page_number++;
				break;
			case _Endurance:
				if (this->endurance.size() > this->page_number * this->cards_per_page) this->page_number++;
				break;
			case _Charisma:
				if (this->charisma.size() > this->page_number * this->cards_per_page) this->page_number++;
				break;
			case _Intelligence:
				if (this->intelligence.size() > this->page_number * this->cards_per_page) this->page_number++;
				break;
			case _Agility:
				if (this->agility.size() > this->page_number * this->cards_per_page) this->page_number++;
				break;
			case _Luck:
				if (this->luck.size() > this->page_number * this->cards_per_page) this->page_number++;
				break;
			case _Legend:
				if (this->legend.size() > this->page_number * this->cards_per_page) this->page_number++;
				break;
			}
		}
		else if (this->left->isPressed() && page_number > 1) {
			page_number--;
		}
	}
}

void Body::updateIcons() {
	for (auto& i : this->buttons) {
		if (i.second->getButtonState() == BUTTON_ACTIVE) {
			this->title->getIcon(i.first)->setColor(sf::Color::Color(255, 255, 255, 128));
		}
		else if (i.second->getButtonState() == BUTTON_HOVER) {
			this->title->getIcon(i.first)->setColor(sf::Color::Color(255, 255, 255, 192));
		}
		else {
			this->title->getIcon(i.first)->setColor(sf::Color::Color(255, 255, 255, 255));
		}
	}
}

void Body::updateCardsNumber() {
	if (this->title->getHeight() > 760) {
		this->cards_per_page = 10;
	}
	else {
		this->cards_per_page = (static_cast<int>(1080 - this->title->getHeight()) / 320) * 10;
	}
}

void Body::updateActiveCards() {
	while (!active_cards.empty()) {
		active_cards.pop_back();
	}
	switch (active_special) {
	case _Strenth: {
		for (int i{ (page_number - 1) * cards_per_page }; i < page_number * cards_per_page && i < strenth.size(); i++) {
			active_cards.push_back(strenth[i]);
		}
		break;
	}
	case _Perception: {
		for (int i{ (page_number - 1) * cards_per_page }; i < page_number * cards_per_page && i < perception.size(); i++) {
			active_cards.push_back(perception[i]);
		}
		break;
	}
	case _Endurance: {
		for (int i{ (page_number - 1) * cards_per_page }; i < page_number * cards_per_page && i < endurance.size(); i++) {
			active_cards.push_back(endurance[i]);
		}
		break;
	}
	case _Charisma: {
		for (int i{ (page_number - 1) * cards_per_page }; i < page_number * cards_per_page && i < charisma.size(); i++) {
			active_cards.push_back(charisma[i]);
		}
		break;
	}
	case _Intelligence: {
		for (int i{ (page_number - 1) * cards_per_page }; i < page_number * cards_per_page && i < intelligence.size(); i++) {
			active_cards.push_back(intelligence[i]);
		}
		break;
	}
	case _Agility: {
		for (int i{ (page_number - 1) * cards_per_page }; i < page_number * cards_per_page && i < agility.size(); i++) {
			active_cards.push_back(agility[i]);
		}
		break;
	}
	case _Luck: {
		for (int i{ (page_number - 1) * cards_per_page }; i < page_number * cards_per_page && i < luck.size(); i++) {
			active_cards.push_back(luck[i]);
		}
		break;
	}
	case _Legend: {
		for (int i{ (page_number - 1) * cards_per_page }; i < page_number * cards_per_page && i < legend.size(); i++) {
			active_cards.push_back(legend[i]);
		}
		break;
	}
	}
}

void Body::updateCardsPosition() {
	if (this->title->getHeight() > 760) {
		float x{ 3.3f };
		float y{ 770 };

		for (auto& i : this->active_cards) {
			i->moveto(x, y);
			x += 192;
		}
	}
	else {
		float x{ 3.3f };
		float y{ title->getHeight() + ((1080 - title->getHeight()) / (cards_per_page / 10) - 300) / 2 };

		for (auto& i : this->active_cards) {
			i->moveto(x, y);
			x += 192;
			if (x > 1734.6) {
				x = 3.3f;
				y += (1080 - title->getHeight()) / (cards_per_page / 10);
			}
		}
	}
}

void Body::updateSelectedCard() {
	if (ready_for_press) {
		for (auto& i : this->active_cards) {
			if (i->isPressed()) {
				this->title->addThumbnail(*i->selectedPerk(), this->active_special);
			}
		}
	}
}

void Body::updateCards(sf::Vector2f& mousePos) {
	for (auto& i : this->active_cards) {
		i->update(mousePos);
	}
}

void Body::updateBoolean() {
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->ready_for_press = true;
	else this->ready_for_press = false;
}

void Body::renderBackground(sf::RenderTarget& target) {
	target.draw(this->background);
}

void Body::renderButtons(sf::RenderTarget& target) {
	for (auto& i : this->buttons) {
		i.second->render(target);
	}
	left->render(target);
	right->render(target);
}

void Body::renderActiveCards(sf::RenderTarget& target) {
	for (auto& i : this->active_cards) {
		i->render(target);
	}
}

void Body::initBackground() {
	this->background.setPosition(0, this->title->getHeight());
	this->background.setSize(sf::Vector2f(1920, 1080 - this->title->getHeight()));
	this->background.setFillColor(sf::Color::Color(250, 250, 250));
}

void Body::initButtons() {
	buttons["Strenth"] = new Button(
		44.5,
		20,
		151,
		72,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		this->font,
		"\0"
	);
	
	buttons["Perception"] = new Button(
		284.5,
		20,
		151,
		72,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		this->font,
		"\0"
	);

	buttons["Endurance"] = new Button(
		524.5,
		20,
		151,
		72,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		this->font,
		"\0"
	);

	buttons["Charisma"] = new Button(
		764.5,
		20,
		151,
		72,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		this->font,
		"\0"
	);

	buttons["Intelligence"] = new Button(
		1004.5,
		20,
		151,
		72,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		this->font,
		"\0"
	);

	buttons["Agility"] = new Button(
		1244.5,
		20,
		151,
		72,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		this->font,
		"\0"
	);

	buttons["Luck"] = new Button(
		1484.5,
		20,
		151,
		72,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		this->font,
		"\0"
	);

	buttons["Legend"] = new Button(
		1764,
		25,
		72,
		72,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		this->font,
		"\0"
	);

	left = new Button(
		875,
		135,
		75,
		75,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Black,
		sf::Color::Color(0, 0, 0, 192),
		sf::Color::Color(0, 0, 0, 128),
		this->font,
		"<-"
	);

	right = new Button(
		965,
		135,
		75,
		75,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Transparent,
		sf::Color::Black,
		sf::Color::Color(0, 0, 0, 192),
		sf::Color::Color(0, 0, 0, 128),
		this->font,
		"->"
	);
}

void Body::initCards() {
	this->initStrenth();
	this->initPerception();
	this->initEndurance();
	this->initCharisma();
	this->initIntelligence();
	this->initAgility();
	this->initLuck();
	this->initLegend();
}

void Body::initStrenth() {

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ӵ���",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ʵ��������ҩ��\n��������45%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ʵ��������ҩ��\n��������90%",
		2
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�����˹Ź��ǡ�",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    δװ������װ��\nʱ��ÿ������+2����\n���ԣ����40�㣩",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    δװ������װ��\nʱ��ÿ������+3����\n���ԣ����60�㣩",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    δװ������װ��\nʱ��ÿ������+4����\n���ԣ����80�㣩",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ƻ���",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ǹ�д����ɵ�\n�˺�+25%������5%��\n�����²���Ķ���",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ǹ�д����ɵ�\n�˺�+50%������10%��\n�����²���Ķ���",
		2
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ܱ۳�ǹ",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ����ǹе������\n����30%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ����ǹе������\n����60%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ����ǹе������\n����90%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ػ���",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    �������˫�ֽ�\nս������ɵ��˺�+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �������˫�ֽ�\nս������ɵ��˺�+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �������˫�ֽ�\nս������ɵ��˺�+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ר�Ҽ��ػ���",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    �������˫�ֽ�\nս������ɵ��˺�+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �������˫�ֽ�\nս������ɵ��˺�+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �������˫�ֽ�\nս������ɵ��˺�+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ʦ���ػ���",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    �������˫�ֽ�\nս������ɵ��˺�+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �������˫�ֽ�\nս������ɵ��˺�+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �������˫�ֽ�\nս������ɵ��˺�+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�蹥��",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    �յ����Ե��˵�\n��ս�����˺�����15%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �յ����Ե��˵�\n��ս�����˺�����30%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �յ����Ե��˵�\n��ս�����˺�����45%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�Ƕ�ʿ",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ������ĵ��ֽ�\nս������ɵ��˺�+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ������ĵ��ֽ�\nս������ɵ��˺�+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ������ĵ��ֽ�\nս������ɵ��˺�+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ר�Ҽ��Ƕ�ʿ",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ������ĵ��ֽ�\nս������ɵ��˺�+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ������ĵ��ֽ�\nս������ɵ��˺�+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ������ĵ��ֽ�\nս������ɵ��˺�+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ʦ���Ƕ�ʿ",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ������ĵ��ֽ�\nս������ɵ��˺�+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ������ĵ��ֽ�\nս������ɵ��˺�+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ������ĵ��ֽ�\nս������ɵ��˺�+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ǹ��",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ������ķǱ���\n������ǹе��ɵ���\n��+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ������ķǱ���\n������ǹе��ɵ���\n��+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ������ķǱ���\n������ǹе��ɵ���\n��+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ר�Ҽ���ǹ��",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ������ķǱ���\n������ǹе��ɵ���\n��+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ������ķǱ���\n������ǹе��ɵ���\n��+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ������ķǱ���\n������ǹе��ɵ���\n��+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ʦ����ǹ��",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ������ķǱ���\n������ǹе��ɵ���\n��+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ������ķǱ���\n������ǹе��ɵ���\n��+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ������ķǱ���\n������ǹе��ɵ���\n��+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ��Ľ�ս������\n��ͽ�ֹ������ӶԷ�\n25%�Ļ���",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ��Ľ�ս������\n��ͽ�ֹ������ӶԷ�\n50%�Ļ���",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ��Ľ�ս������\n��ͽ�ֹ������ӶԷ�\n75%�Ļ���",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ȭ",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    �������ȭ����\n�ɵ��˺�+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �������ȭ����\n�ɵ��˺�+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �������ȭ����\n�ɵ��˺�+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ӵ�����",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ����ǹеװ����\n�����10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ����ǹеװ����\n�����20%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ����ǹеװ����\n�����30%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ��Ľ�ս������\n��������20%���Ӷ�\n�ٶ������10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ��Ľ�ս������\n��������40%���Ӷ�\n�ٶ������20%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ��Ľ�ս������\n��������60%���Ӷ�\n�ٶ������30%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ��ը����������\n30%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ��ը����������\n60%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ��ը����������\n90%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ����������Ʒ��\n��������25%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ����������Ʒ��\n��������50%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ����������Ʒ��\n��������75%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����·",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ���Ŷ���װ��ʱ��\n����˳�̿ɶԵ���\n����˺���ʧ��",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ���Ŷ���װ��ʱ��\n����˳�̿ɶԵ���\n��ɴ����˺�������\n��ʹ����ʧ��",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ���Ŷ���װ��ʱ��\n����˳�̿ɶԵ���\n��ɾ����˺�������\n��ʹ����ʧ��",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ɢ��",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ɢ��ǹ��������\n��30%��װ���ٶ����\n10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ɢ��ǹ��������\n��60%��װ���ٶ����\n20%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ɢ��ǹ��������\n��90%��װ���ٶ����\n30%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ɢ��ǹ��",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    �������ɢ��ǹ\n��ɵ��˺�+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �������ɢ��ǹ\n��ɵ��˺�+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �������ɢ��ǹ\n��ɵ��˺�+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ר�Ҽ�ɢ��ǹ��",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    �������ɢ��ǹ\n��ɵ��˺�+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �������ɢ��ǹ\n��ɵ��˺�+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �������ɢ��ǹ\n��ɵ��˺�+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ʦ��ɢ��ǹ��",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    �������ɢ��ǹ\n��ɵ��˺�+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �������ɢ��ǹ\n��ɵ��˺�+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    �������ɢ��ǹ\n��ɵ��˺�+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ��������+10",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ��������+20",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ��������+30",
		3
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ��������+40",
		4
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���׳",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    װ�ױ���������\n��25%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    װ�ױ���������\n��50%",
		2
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ȫ����",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ���Ŷ���װ�׳�\n�̵�ʱ��ֻ����ԭ\n��һ��ľ۱������\n��",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ���Ŷ���װ�׳�\n�̵�ʱ�򣬲�������\n����ľ۱��������",
		2
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����ҩ��",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    ����ҩ�����\n�����룩����������\n��30%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ����ҩ�����\n�����룩����������\n��60%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    ����ҩ�����\n�����룩����������\n��90%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();
}

void Body::initPerception() {

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    �������V.A.T.\nS.�в鿴Ŀ�������\n�����Եľ������",
		2
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ͻ����",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ����ս��ѵ����\nζ���Զ���ǹ��ɵ�\n�˺�+10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ����ս��ѵ����\nζ���Զ���ǹ��ɵ�\n�˺�+15%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    ����ս��ѵ����\nζ���Զ���ǹ��ɵ�\n�˺�+20%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ר�Ҽ�ͻ����Ա",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    �ϸ�ս��ѵ����\nζ���Զ���ǹ��ɵ�\n�˺�+10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    �ϸ�ս��ѵ����\nζ���Զ���ǹ��ɵ�\n�˺�+15%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    �ϸ�ս��ѵ����\nζ���Զ���ǹ��ɵ�\n�˺�+20%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ʦ��ͻ����Ա",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ����������ս��\nѵ��������ʹ���Զ�\n��ǹʱ��ɵ��˺�+10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ����������ս��\nѵ��������ʹ���Զ�\n��ǹʱ��ɵ��˺�+15%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    ����������ս��\nѵ��������ʹ���Զ�\n��ǹʱ��ɵ��˺�+20%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���л���",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ����V.A.T.S.��\n��׼Ŀ��֫�壬����\n����������ÿһ����\n�����׼ȷ�Ⱥ��˺�",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ����V.A.T.S.��\n��׼Ŀ��֫�壬����\n����������ÿһ����\n����ø���׼ȷ�Ⱥ�\n�˺�",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    ����V.A.T.S.��\n��׼Ŀ��֫�壬����\n����������ÿһ����\n����ø�׼ȷ�Ⱥ���\n��",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ٷ�����",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ʹ�������׼ʱ��\n������ǹ��̺;�ȷ\n�����10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ʹ�������׼ʱ��\n������ǹ��̺;�ȷ\n�����20%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    ʹ�������׼ʱ��\n������ǹ��̺;�ȷ\n�����30%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ɱ���",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ��Ĺ���������\n������25%�Ļ���",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ��Ĺ���������\n������50%�Ļ���",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    ��Ĺ���������\n������75%�Ļ���",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"С������",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ��Ͷ��������ʱ\n����Կ���Ͷ�����ߣ�\n�������15%��Ͷ����\n��",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ��Ͷ��������ʱ\n����Կ���Ͷ�����ߣ�\n�������30%��Ͷ����\n��",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    ��Ͷ��������ʱ\n����Կ���Ͷ�����ߣ�\n�������50%��Ͷ����\n��",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ӫ�����",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    �Է�����˵���\n��+20%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    �Է�����˵���\n��+40%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    �Է�����˵���\n��+60%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"԰�ո���",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    �ջ�ֲ���ʱ��\n��������ճ�",
		1
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ��ը�뾶����50%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ��ը�뾶����",
		2
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�������",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    �����Զ���ǹװ\n���ٶȼӿ�10%������\n�ø��õ����侫׼��",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    �����Զ���ǹװ\n���ٶȼӿ�20%������\n�ý�һ�������侫׼\n��",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    �����Զ���ǹװ\n���ٶȼӿ�30%������\n�þ��ѵ����侫׼��",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ѻ�����",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ʹ�������׼ʱ��\n��Ĳ�ǹ��̺;�ȷ\n�����10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ʹ�������׼ʱ��\n��Ĳ�ǹ��̺;�ȷ\n�����20%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    ʹ�������׼ʱ��\n��Ĳ�ǹ��̺;�ȷ\n�����30%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ҹ��",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ������6��������\n6��Ǳ��ʱ���ҹ����\n��",
		2
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ҹè��",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ����6��������6\n�㣬����+1����֪+1",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ����6��������6\n�㣬����+2����֪+2",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    ����6��������6\n�㣬����+3����֪+3",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����֮��",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    40%���ʴӶ����\nʬ�����ҵ��������",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    60%���ʴӶ����\nʬ�����ҵ��������",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    80%���ʴӶ����\nʬ�����ҵ��������",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ���+1�������ܣ�\n��ʹ����ʱ����ѷ�\nΧ���10%",
		1
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ר�Ҽ�����",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ���+1�������ܣ�\n��ʹ����ʱ����ѷ�\nΧ���10%",
		1
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ʦ������",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ���+1�������ܣ�\n��ʹ����ʱ����ѷ�\nΧ���10%",
		1
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���侵",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    �������������\n��+10",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    �������������\n��+20",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    �������������\n��+30",
		3
	);
	(*this->perception.rbegin())->addLevel(
		L"    �������������\n��+40",
		4
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ǹ��",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+15%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+20%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ר�Ҽ���ǹ��",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+15%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+20%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ʦ����ǹ��",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+15%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+20%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"˫��ɵ����",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ���ɢ��ǹ�ľ�\nȷ�Ⱥ͵�ҩɢ������",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ���ɢ��ǹ�ľ�\nȷ�Ⱥ͵�ҩɢ����һ\n������",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    ���ɢ��ǹ�ľ�\nȷ�Ⱥ͵�ҩɢ������\n����",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ѻ���",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ����׼ʱ��ø�\n�õĿ���������ס��\n��ʱ���ӳ�25%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ����׼ʱ��ø�\n�õĿ���������ס��\n��ʱ���ӳ�50%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    ����׼ʱ��ø�\n�õĿ���������ס��\n��ʱ���ӳ�75%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"̹��ɱ��",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ʹ�ò�ǹ����ǹ\n����ʱ������Ŀ��12%\n�Ļ��ף�����3%����\n��ʹ�з�����ʧ��״\n̬",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    ʹ�ò�ǹ����ǹ\n����ʱ������Ŀ��24%\n�Ļ��ף�����6%����\n��ʹ�з�����ʧ��״\n̬",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    ʹ�ò�ǹ����ǹ\n����ʱ������Ŀ��36%\n�Ļ��ף�����9%����\n��ʹ�з�����ʧ��״\n̬",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��־�ղؼ�",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ��Χ������־ʱ��\n��������ʾ��",
		1
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��֪����",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    ��Χ��������ʱ��\n��������ʾ��",
		1
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"Ѱ������",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    �ڷ�Χ����ƿ��\n��ʱ��������������\nʾ��",
		1
	);
	(*this->perception.rbegin())->finishAddingLevel();

}

void Body::initEndurance() {

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���Ͻ����",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ��֫���ܵ�����\n�����ڼ���30%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ��֫���ܵ�����\n�����ڼ���60%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ��֫��������ȫ\n�����˺�",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ͨ��",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ����ҹ��ļ���\n�Ϳڿ����������20%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����ҹ��ļ���\n�Ϳڿ����������40%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����ҹ��ļ���\n�Ϳڿ����������60%",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ʳ����",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ʳ�����ࡢʬ��\n���������ˡ���ʬ��\n��������󹤵�ʬ��\n���Իָ�����ֵ�ͼ�\n���̶�",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ʳ�����ࡢʬ��\n���������ˡ���ʬ��\n��������󹤵�ʬ��\n���Իָ����������\nֵ�ͼ����̶�",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ʳ�����ࡢʬ��\n���������ˡ���ʬ��\n��������󹤵�ʬ��\n���Իָ����������\nֵ�ͼ����̶�",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ҩ��ħ",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    �����κ�ҩ��ҩ\nЧʱ�䶼����30%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    �����κ�ҩ��ҩ\nЧʱ�䶼����60%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    �����κ�ҩ��ҩ\nЧʱ�䶼����100%",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ҩ�￹��",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ����ҩ��ʱ����\n�Ļ��ή��һ��",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ���ö�ҩ����\n����ȫ������",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���ְ�����",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ���ӿ������汶\n��",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ���ӿ�������Ϊ\nԭ������",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    �������϶��⻺\n��25%�Ŀڿʳ̶�",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    �������϶��⻺\n��50%�Ŀڿʳ̶�",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    �������϶��⻺\n��75%�Ŀڿʳ̶�",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    �ܵ������Ա�ը\n�ͻ��湥�����˺���\n��15%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    �ܵ������Ա�ը\n�ͻ��湥�����˺���\n��30%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    �ܵ������Ա�ը\n�ͻ��湥�����˺���\n��75%",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ʬ������",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    �ܵ�����ʱ����\nʹ����ʧ������ֵ��\n���ָ�",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    �ܵ�����ʱ����\nʹ����ʧ������ֵ��\n���ʸ���",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    �ܵ�����ʱ����\nʹ����ʧ������ֵ��\n���ʸ���",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�����",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ��Ӫ�ػ򹤷���\n�����𽥻ָ�����ֵ",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ��Ӫ�ػ򹤷���\n�����������ֵ����\n��֫������",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ����û�д�����\nװ��ʱ���10�˺���\n��������",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����û�д�����\nװ��ʱ���20�˺���\n��������",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����û�д�����\nװ��ʱ���30�˺���\n��������",
		3
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����û�д�����\nװ��ʱ���40�˺���\n��������",
		4
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����û�д�����\nװ��ʱ���50�˺���\n��������",
		5
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ٶ�����",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    �����ʳ������\n�ļ��ʼ���30%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    �����ʳ������\n�ļ��ʼ���60%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    �����ʳ������\n�ļ��ʼ���90%",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ͭ����θ",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ������ʳ�ķ���\n����30%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ������ʳ�ķ���\n����60%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ������Ϊ��ʳ��\n��ȡ����",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ����15�������\n��ֵ����",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����30�������\n��ֵ����",
		3
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����45�������\n��ֵ����",
		4
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���ƿڸ�֮��",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ����ҩ��ʱ����\n50%����ֵ�ͷ�",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ���ڷ���ҩ�ﲻ\n������ɼ���",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    �����ܱ߻�����\n�����ļ��ʼ���30%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    �����ܱ߻�����\n�����ļ��ʼ���60%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    �����ܱ߻�����\n�����ļ��ʼ���90%",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ҹ֮����",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ����6��������6\n�㣬�������ֵ+20",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����6��������6\n�㣬�������ֵ+40",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�������",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ������6�㵽����\n6��֮��������ֵ��\n��",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ������6�㵽����\n6��֮���ø�������\nֵ�ָ�",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���޵�",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ����̶�Խ�ߣ�\n����Խ�ߣ����5����\n����",
		1
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ���ڷ��俹��+10",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ���ڷ��俹��+20",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ���ڷ��俹��+30",
		3
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ���ڷ��俹��+40",
		4
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����ٱ�",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    �ڱ�������ˮ��\n��ʱ��������",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    �ڱ�������ˮ��\n��ʱ�������",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���߹���",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    �㱻�����Ҹ�\n��ʱ��������2������\n���+25%�˺��ӳ�",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    �㱻�����Ҹ�\n��ʱ��������2������\n���+50%�˺��ӳ�",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���ٴ�л��",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ����ʳ����⻺\n��25%�ļ����̶�",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����ʳ����⻺\n��50%�ļ����̶�",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����ʳ����⻺\n��75%�ļ����̶�",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"̫���ܹ���",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ����6��������6\n���ڼ䣬���������\n�ɺ������ӳɸ�1��",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����6��������6\n���ڼ䣬���������\n�ɺ������ӳɸ�2��",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����6��������6\n���ڼ䣬���������\n�ɺ������ӳɸ�3��",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"̫��֮��",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ������6�㵽����\n6��֮����Ի����ָ�\n�����˺�",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ������6�㵽����\n6��֮����Կ��ٻָ�\n�����˺�",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�����Ʒ",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ����Һ��������\n���ĸ��ʽ���30%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����Һ��������\n���ĸ��ʽ���60%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ����Һ��������\n���ĸ��ʽ���90%",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ������������\nȾ�������ļ��ʼ���\n30%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ������������\nȾ�������ļ��ʼ���\n60%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ������������\nȾ�������ļ��ʼ���\n90%",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ˮ�к�",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ��Ӿʱ�㲻����\n�ܵ������˺�������\n������ˮ�º���",
		1
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"רְ�ƹ�",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ���������Ⱦ��\n���",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�Թ���",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    �Թ������Ի��\n��������",
		1
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�޸�ˮ��������ʩ",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    ҩ������Ŀڿ�\n�̶Ƚ���50%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    ҩ�ﲻ���ٵ���\n�ڿ�",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

}

void Body::initCharisma() {

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    �����ǹ��׼��\n�����25%�ļ�����\n����������",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �����ǹ��׼��\n�����50%�ļ�����\n����������",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �����ǹ��׼��\n�����75%�ļ�����\n����������",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    �������Լ�֮�⣬\nÿλ���ѽ�ʹ����6\n�˺�&�������ԣ����\n18��",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �������Լ�֮�⣬\nÿλ���ѽ�ʹ����8\n�˺�&�������ԣ����\n18��",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �������Լ�֮�⣬\nÿλ���ѽ�ʹ����\n10�˺�&�������ԣ���\n��18��",
		3
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �������Լ�֮�⣬\nÿλ���ѽ�ʹ����\n12�˺�&�������ԣ���\n��18��",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"E.M.T.",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    �㸴�����ҽ�\n��15���ڻ��������\n��",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �㸴�����ҽ�\n��30���ڻ�ø��ߵ�\n�����ָ�",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �㸴�����ҽ�\n��60���ڻ����ߵ�\n�����ָ�",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    ���������ÿһ\nλ����Ϊ���ṩ1����\n��",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ���������ÿһ\nλ����Ϊ���ṩ2����\n��",
		2
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ҽ",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    �������������\n������ҩЧ��ø���\n��",
		2
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����֮��",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    �������������\n�湥��ʱ������ʱ��\n������ֵ���������ף�",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �������������\n�湥��ʱ������ʱ��\n���϶�����ֵ������\n���ף�",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �������������\n�湥��ʱ������ʱ��\n����������ֵ������\n���ף�",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����¶Ӫ��",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    �����������\n������ʱ���������\n�������ٶȷŻ�40%",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �����������\n������ʱ���������\n�������ٶȷŻ�80%",
		2
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ң����",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    �ܵ��ƾ�Ӱ��ʱ��\n�������+2",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �ܵ��ƾ�Ӱ��ʱ��\n�������+3",
		2
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���̵Ľ���",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    ���ڷ���ҷ���\n�����������ø���\n�ݵ������۸�",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ���ڷ���ҷ���\n�����������÷ǳ�\n�Żݵ������۸�",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �ڷ���ҷ�����\n��������������۸�\n����ǰ���Ż���",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ע����",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    ���㸴������\n10�������ж���ָ�\n+6",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ���㸴������\n10�������ж���ָ�\n+12",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ���㸴������\n10�������ж���ָ�\n+18",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    ���㴦���״̬\n�У������Ķ�����\n���Ի��5%�Ķ��⾭\n��ֵ",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ���㴦���״̬\n�У������Ķ�����\n���Ի��10%�Ķ��⾭\n��ֵ",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ���㴦���״̬\n�У������Ķ�����\n���Ի��15%�Ķ��⾭\n��ֵ",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    ����ð��ʱ����\n�ܵ��˺�����10%��ͬ\nʱ�ж���Ļָ��ٶ�\n����10%",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ����ð��ʱ����\n�ܵ��˺�����20%��ͬ\nʱ�ж���Ļָ��ٶ�\n����20%",
		3
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ����ð��ʱ����\n�ܵ��˺�����30%��ͬ\nʱ�ж���Ļָ��ٶ�\n����30%",
		4
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���ȿ���",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    ���ڵķ���ֵ��\n���ӽ�������Ŀ��\n���25��ķ���ļ�\n��",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ���ڵķ���ֵ��\n���ӽ�������Ŀ��\n���50��ķ���ļ�\n��",
		2
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ɶ��к�",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    սǰ���������\nӰ���Ϊ˫��",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    սǰ���������\nӰ���Ϊ����",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���Ƽ�",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    ���ڽ�ʳ���ߺ�\nˮʱ��Ϊ���ѻ��ⲿ\n�ּ�����ڿ�",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ���ڽ�ʳ���ߺ�\nˮʱ��Ϊ���ѻ����\n�༢����ڿ�",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ���ڽ�ʳ���ߺ�\nˮʱ��Ϊ���ѻ����\n��������ڿ�",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ɹŴ��",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    �þƾ���������\n���",
		1
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���亣��",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    �ܷ���Ӱ��ʱ��\n����������Ե�Ϊ��\n����������80�����\nֵ",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �ܷ���Ӱ��ʱ��\n����������Ե�Ϊ��\n����������140�����\nֵ",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �ܷ���Ӱ��ʱ��\n����������Ե�Ϊ��\n����������200�����\nֵ",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���ҽ��",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    ����������Һ�5\n��������Իָ�����\nֵ",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ����������Һ�7\n��������Իָ�����\nֵ",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ����������Һ�\n10��������Իָ���\n��ֵ",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"С�ӻ���",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    ��С���б�����\n�ȼӿ�10%",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ��С���б�����\n�ȼӿ�20%",
		2
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    ����Ŀ���2��\n�ڼ�����10%���˺���\n��",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ����Ŀ���2��\n�ڼ�����20%���˺���\n��",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ����Ŀ���2��\n�ڼ�����30%���˺���\n��",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�Ŷ�ҽ����",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    �������������\nҲ����ҽ�Ƹ����Ķ�\n�ѣ�Ч����������50%",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �������������\nҲ����ҽ�Ƹ����Ķ�\n�ѣ�Ч����������75%",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �������������\nҲ����ҽ�Ƹ����Ķ�\n�ѣ�Ч����������\n100%",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���ⴸ",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    ���㹥������\n��Ŀ����5���ڳ���5%\n�Ķ����˺�",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ���㹥������\n��Ŀ����7���ڳ���7%\n�Ķ����˺�",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ���㹥������\n��Ŀ����10���ڳ���\n10%�Ķ����˺�",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��Ѫ����",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    Ѫ�������ڿ���\n����ڿʣ�Ч������\n50%���ϣ����Ҳ��ٲ�\n������",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    Ѫ�������ڿ���\n���õؿڿʣ�Ч����\n��100%���ϣ����Ҳ���\n��������",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    Ѫ�������ڿ���\n�����ؿڿʣ�Ч����\n��150%���ϣ����Ҳ���\n��������",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����������",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    �����ǹ��׼һ\nЩ�������25%�ļ�\n��������������",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �����ǹ��׼һ\nЩ�������50%�ļ�\n��������������",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    �����ǹ��׼һ\nЩ�������75%�ļ�\n��������������",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�����н�",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    ���п����ƶ�ʱ\n�ٸ�30%��ƿ��",
		1
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    ��ļ���������\nʱ����50%�ļ��ʿ���\nΪ�����Ķ�������һ\n�ּ���",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    ��ļ���������\nʱ����Ȼ����Ϊ����\n�Ķ�������һ�ּ���",
		2
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�������",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    �������Ҳ�б�\n�죬�������Ч��\n+25%",
		1
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����֮��",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    ���㸴������\n���������з���ֵ",
		1
	);
	(*this->charisma.rbegin())->finishAddingLevel();

}

void Body::initIntelligence() {

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"װ����",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    �������������\n�߼����׸�װ������\nҪ���ͼ��",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��������װ�׵�\n�������ļ���",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    �������Ļ�����\n�������",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���õ��",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ����������ҩ��\n��������30%",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ����������ҩ��\n��������60%",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ����������ҩ��\n��������90%",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�а���",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ����������Ʒ��\n�ڿ��Խ�Լ25%�Ĳ���",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ����������Ʒ��\n�ڿ��Խ�Լ50%�Ĳ���",
		2
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ƻ�ר��",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ��ı�ը�����\n�����20%�˺�",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��ı�ը�����\n�����30%�˺�",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��ı�ը�����\n�����40%�˺�",
		3
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��ı�ը�����\n�����50%�˺�",
		4
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��ı�ը�����\n�����60%�˺�",
		5
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ������ɶ����\n��15%",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ������ɶ����\n��30%",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ������ɶ����\n��45%",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����һ��",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ����԰ѻ��׺�\n�������׵�״̬�޸�\n����׼���ֵ��130%",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ����԰ѻ��׺�\n�������׵�״̬�޸�\n����׼���ֵ��160%",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ����԰ѻ��׺�\n�������׵�״̬�޸�\n����׼���ֵ��200%",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ǹеʦ",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ǹе���ʽ���\n10%���������������\n�ȼ�1��ǹе����Ҫ��\n��ͼ��",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ǹе���ʽ���\n20%���������������\n�ȼ�2��ǹе����Ҫ��\n��ͼ��",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ǹе���ʽ���\n30%���������������\n�ȼ�3��ǹе����Ҫ��\n��ͼ��",
		3
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ǹе���ʽ���\n40%���������������\n�ȼ�4��ǹе����Ҫ��\n��ͼ��",
		4
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ǹе���ʽ���\n50%���������������\n�ȼ�5��ǹе����Ҫ��\n��ͼ��",
		5
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"רҵˮ�ܹ�",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    �������������\n���ٶȽ���20%���޸�\n����Ҳ����",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    �������������\n���ٶȽ���40%���޸�\n����Ҳ����",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    �������������\n���ٶȽ���60%���޸�\n����Ҳ����",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ʱ��ʿ",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ��ս��������\n����10%�����������\n����ȼ�1�Ľ�ս����\n����Ҫ���ͼ��",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��ս��������\n����20%�����������\n����ȼ�2�Ľ�ս����\n����Ҫ���ͼ��",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��ս��������\n����30%�����������\n����ȼ�3�Ľ�ս����\n����Ҫ���ͼ��",
		3
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��ս��������\n����40%�����������\n����ȼ�4�Ľ�ս����\n����Ҫ���ͼ��",
		4
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��ս��������\n����50%�����������\n����ȼ�5�Ľ�ս����\n����Ҫ���ͼ��",
		5
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���޿���",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ����ֵ����20%ʱ��\n���20�˺����ԣ�10%\n�˺������Լ�15%����\n�������ָ�",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ����ֵ����20%ʱ��\n���30�˺����ԣ�15%\n�˺������Լ�15%����\n�������ָ�",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ����ֵ����20%ʱ��\n���40�˺����ԣ�20%\n�˺������Լ�15%����\n�������ָ�",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ƶ���Դ",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ���ж���װ�׺�\n���ܵ���������25%",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ���ж���װ�׺�\n���ܵ���������50%",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ���ж���װ�׺�\n���ܵ���������75%",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ҩ��ʦ",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ��������������\n��30%����",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��������������\n��60%����",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��������ȥ����\n���ķ���",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����ʦ",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    �������������\n�߼�����װ�׸�װ��\n����Ҫ���ͼ��",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��������װ�׵�\n�������ļ���",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    �������Ķ���װ\n���;������",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����ʹ����",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    �۱���ĵĳ���\nʱ���ӳ�30%",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    �۱���ĵĳ���\nʱ���ӳ�60%",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ���ھ۱������\n��������ʱ��",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������ר��",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ����жԻ�����\n��25%�ļ���������ƽ\n������",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ����жԻ�����\n��50%�ļ���������ƽ\n������",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ����жԻ�����\n��75%�ļ���������ƽ\n������",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ѧ��",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    �������ѿ�����\n������ǹ����Ҫ���\nͼ��",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ���������1����\n��ǹе��װ������Ҫ\n���ͼ)",
		2
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ר�Ҽ���ѧ��",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ���������2����\n��ǹе��װ������Ҫ\n���ͼ��",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��������ǹе��\n�ĵĲ��ϸ���",
		2
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ʦ����ѧ��",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ���������3����\n��ǹе��װ������Ҫ\n���ͼ��",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ������������ǹ\n�;������",
		2
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ȶ�",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ���Ŷ���װ��ʱ��\n����ǹе��ø��߾�\nȷ�ȣ�������Ŀ��15%\n����",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ���Ŷ���װ��ʱ��\n����ǹе��ȷ�Ƚ�һ\n����ߣ�������Ŀ��\n30%����",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ���Ŷ���װ��ʱ��\n����ǹе��þ���һ\n��׼�ȣ�������Ŀ��\n45%����",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ������޸��κ�\n�������������״̬\n��130%",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ������޸��κ�\n�������������״̬\n��160%",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ������޸��κ�\n�������������״̬\n��200%",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ƻ���",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ��Թ��������\n�˺�+40%",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��Թ��������\n�˺�+80%",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��Թ��������\n�˺�+120%",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����װ���޲���",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ��Ķ���װ����\n���ٶȽ���20%���޸�\n����Ҳ����",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��Ķ���װ����\n���ٶȽ���40%���޸�\n����Ҳ����",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    ��Ķ���װ����\n���ٶȽ���60%���޸�\n����Ҳ����",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���ר��",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ��������ͻ���\n���Ի�ø���Ĳ���",
		1
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ڿ�",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ���+1�ڿͼ��ܣ�\n�ն�����ʱ�����",
		1
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ڿ�ר��",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ���+1�ڿͼ��ܣ�\n�ն�����ʱ�����",
		1
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ڿʹ�ʦ",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ���+1�ڿͼ��ܣ�\n�ն�����ʱ�����",
		1
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ѧ��",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    ����ҩ��ʱ����\n��˫��������",
		1
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

}

void Body::initAgility() {

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ж����к�",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    �ж������ָ���\n�����15%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    �ж������ָ���\n�����30%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    �ж������ָ���\n�����45%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    30����ÿ�λ�ɱ\n���˻��+6%�����\n36%�����˺��ӳɣ�ÿ\n�λ�ɱ����ˢ�¼�ʱ",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    30����ÿ�λ�ɱ\n���˻��+7%�����\n42%�����˺��ӳɣ�ÿ\n�λ�ɱ����ˢ�¼�ʱ",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    30����ÿ�λ�ɱ\n���˻��+8%�����\n48%�����˺��ӳɣ�ÿ\n�λ�ɱ����ˢ�¼�ʱ",
		3
	);
	(*this->agility.rbegin())->addLevel(
		L"    30����ÿ�λ�ɱ\n���˻��+9%�����\n54%�����˺��ӳɣ�ÿ\n�λ�ɱ����ˢ�¼�ʱ",
		4
	);
	(*this->agility.rbegin())->addLevel(
		L"    30����ÿ�λ�ɱ\n���˻��+10%�����\n60%�����˺��ӳɣ�ÿ\n�λ�ɱ����ˢ�¼�ʱ",
		5
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��Ұ����",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ����ֵ����20%ʱ\n�Զ�ʹ�������룬ÿ\n20���ܴ���һ��",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ����ֵ����30%ʱ\n�Զ�ʹ�������룬ÿ\n20���ܴ���һ��",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ����ֵ����40%ʱ\n�Զ�ʹ�������룬ÿ\n20���ܴ���һ��",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�����ж�",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ���Զ��������\n��ɶ���15%��͵Ϯ��\n��",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ���Զ��������\n��ɶ���30%��͵Ϯ��\n��",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ���Զ��������\n��ɶ���50%��͵Ϯ��\n��",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�������",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ����ֵ����40%\nʱ�������ĸ����ж�\n�������ӿ�10%�ĳ��\n�ٶ�",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ����ֵ����50%\nʱ�������ĸ����ж�\n�������ӿ�20%�ĳ��\n�ٶ�",
		2
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ƻ�",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ÿ�α����п���\n����10%���˺�����Ҫ\n����30�ж���",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ÿ�α����п���\n����20%���˺�����Ҫ\n����30�ж���",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ÿ�α����п���\n����30%���˺�����Ҫ\n����30�ж���",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ִ����",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ���ɢ��ǹ��5%\n�ĸ������ʧ�⣬��\n10%�ĸ�������²�",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ���ɢ��ǹ��10%\n�ĸ������ʧ�⣬��\n20%�ĸ�������²�",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ���ɢ��ǹ��15%\n�ĸ������ʧ�⣬��\n30%�ĸ�������²�",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�رܻ���",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    δװ������װ��\nʱ��ÿ������+1����\n�����������ԣ����\n15�㣩",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    δװ������װ��\nʱ��ÿ������+2����\n�����������ԣ����\n30�㣩",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    δװ������װ��\nʱ��ÿ������+3����\n�����������ԣ����\n45�㣩",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ɽ����",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ׹���˺�����40%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ׹���˺�����80%",
		2
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�λ���Ա",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ��������Զ���\nǹ��ɵ��˺�+10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ��������Զ���\nǹ��ɵ��˺�+15%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ��������Զ���\nǹ��ɵ��˺�+20%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ר�Ҽ��λ���Ա",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ��������Զ���\nǹ��ɵ��˺�+10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ��������Զ���\nǹ��ɵ��˺�+15%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ��������Զ���\nǹ��ɵ��˺�+20%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ʦ�λ���Ա",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ��������Զ���\nǹ��ɵ��˺�+10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ��������Զ���\nǹ��ɵ��˺�+15%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ��������Զ���\nǹ��ɵ��˺�+20%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ǹе����",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    V.A.T.S.�л���\nɱĿ��ʱ������һ��\nĿ����ɵ��˺�+10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    V.A.T.S.�л���\nɱĿ��ʱ���֮���\n2��Ŀ��������10%\n��20%�Ķ����˺�",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    V.A.T.S.�л���\nɱĿ��ʱ���֮���\n3��Ŀ��������10%��\n20%��30%�Ķ����˺�",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ǹ�ɱ���",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    װ����ǹʱ����\n�ٶ�����10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    װ����ǹʱ����\n�ٶ�����20%",
		2
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ǹ��",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+15%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+20%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ר�Ҽ���ǹ��",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+15%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+20%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ʦ����ǹ��",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+15%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ������ķ��Զ�\n��ǹ��ɵ��˺�+20%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������԰",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ������������\n����׼���壬Ҳ����\n������׼��������Ҫ\n���ͼ��",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ������������\n���߼����壬Ҳ����\n�����߼���������Ҫ\n���ͼ��",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ������������\n��ר�Ҽ����壬Ҳ��\n������ר�Ҽ�����\n����Ҫ���ͼ��",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�������˶�Ա",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ������ĵ��ж�\n��������20%��δʹ��\n����װ�ף�",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ������ĵ��ж�\n��������30%��δʹ��\n����װ�ף�",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ������ĵ��ж�\n��������40%��δʹ��\n����װ�ף�",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"˯ħ",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    �������������\n��ҹ����ɶ���50%��\n͵Ϯ�˺�",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    �������������\n��ҹ����ɶ���100%\n��͵Ϯ�˺�",
		2
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ִ�����",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ��ǹ���侫׼��\n+15%��֫���²м���\n+4%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ��ǹ���侫׼��\n+30%��֫���²м���\n+8%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ��ǹ���侫׼��\n+45%��֫���²м���\n+12%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ƶ����",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    δװ������װ��\nʱ�����ʱ���+15��\n�˺�����������",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    δװ������װ��\nʱ�����ʱ���+30��\n�˺�����������",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    δװ������װ��\nʱ�����ʱ���+45��\n�˺�����������",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ʹ�ý�ս������\n��Ǳ�й��������2.3\n���˺�",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ʹ�ý�ս������\n��Ǳ�й��������2.6\n���˺�",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ʹ�ý�ս������\n��Ǳ�й��������3��\n�˺�",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��װ",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ������ǹ25%����\n��",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ������ǹ50%����\n��",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ������ǹ75%����\n��",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�����ع�",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ����С�ӵĳ���\nʱ���Ϊ������",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ����С�ӵĳ���\nʱ���Ϊ������",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ����С�ӵĳ���\nʱ���Ϊ�ı���",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"Ǳ��",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    Ǳ��ʱ����⵽\n���Ѷ�����25%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    Ǳ��ʱ����⵽\n���Ѷ�����50%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    Ǳ��ʱ����⵽\n���Ѷ�����75%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ͨ��ͽ��������",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ʳ�Ｐ��Ʒ����\n������30%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ʳ�Ｐ��Ʒ����\n������60%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ʳ�Ｐ��Ʒ����\n������90%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ɫ��ʿ",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ��Ļ�������\n�Ƚ���20%���޸�����\nҲ����",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ��Ļ�������\n�Ƚ���40%���޸�����\nҲ����",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    ��Ļ�������\n�Ƚ���60%���޸�����\nҲ����",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ҩ��",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ������ҩʱ����\n����40%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    ������ҩʱ����\n����80%",
		2
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����������",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    Ǳ��˦�����ˣ�\n�ܲ�����Ӱ������״\n̬",
		1
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ӯ�Ų�",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    ��Ǳ��ʱ������\n�������׻��������",
		1
	);
	(*this->agility.rbegin())->finishAddingLevel();

}

void Body::initLuck() {

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����ǿ��",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ����V.A.T.S.��\n���˺�+50%",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ����V.A.T.S.��\n���˺�+75%",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ����V.A.T.S.��\n���˺�+100%",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"һ�Ż���",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    5%�Ķ����˺���\nζ����ĵ�����һ��\n�ļ��ʻᱻը��Ѫ��\n�ܵ�����",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    10%�Ķ����˺���\nζ����ĵ�����һ��\n�ļ��ʻᱻը��Ѫ��\n�ܵ�����",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    15%�Ķ����˺���\nζ����ĵ�����һ��\n�ļ��ʻᱻը��Ѫ��\n�ܵ�����",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ͷС����",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ��40%�ļ�������\nʳƷ�������ҵ�����\n�Ĺ�ͷʳƷ",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��60%�ļ�������\nʳƷ�������ҵ�����\n�Ĺ�ͷʳƷ",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��80%�ļ�������\nʳƷ�������ҵ�����\n�Ĺ�ͷʳƷ",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ƿ���ռ���",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ��ᷢ���г���\n33%��ƿ�ǲ���ƿ�ǲ�\n�����",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��ᷢ���г���\n66%��ƿ�ǲ���ƿ�ǲ�\n�����",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��ᷢ���г���\n100%��ƿ�ǲ���ƿ��\n�������",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�������",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ����ĸ���Ӱ��\n����25%",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ����ĸ���Ӱ��\n����50%",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ����ĸ���Ӱ��\n����75%",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    �������ڽ�����\n85%�ı�����",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    �������ڽ�����\n70%�ı�����",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    �������ڽ�����\n55%�ı�����",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������Ҷ��",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ��V.A.T.S.�е�\nÿ�ι������ж��м�\n�ʽ���ı����Ƴ���",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��V.A.T.S.�е�\nÿ�ι������ж��н�\n�ߵļ��ʽ���ı���\n�Ƴ���",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��V.A.T.S.�е�\nÿ�ι������ж��м�\n��ļ��ʽ���ı���\n�Ƴ���",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����ĳ��",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ��V.A.T.S.�е�\nÿ�λ�ɱ����15%�ļ�\n��ʹ�ж�����ȫ����\n��",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��V.A.T.S.�е�\nÿ�λ�ɱ����25%�ļ�\n��ʹ�ж�����ȫ����\n��",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��V.A.T.S.�е�\nÿ�λ�ɱ����35%�ļ�\n��ʹ�ж�����ȫ����\n��",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    Я����������10\n���˺�����������\n��δװ������װ�ף�",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    Я����������20\n���˺�����������\n��δװ������װ�ף�",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    Я����������30\n���˺�����������\n��δװ������װ�ף�",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����ǩ",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ��������ʱ����\n�������к�С������\n������",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��������ʱ����\n�������нϴ�����\n������",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��������ʱ����\n�������кܴ�����\n������",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ʱ����ת",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    �����ܹ���ʱ��\nװ���е�װ���н�С\n�������޸�����",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    �����ܹ���ʱ��\nװ���е�װ���нϴ�\n�������޸�����",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    �����ܹ���ʱ��\nװ���е�װ���кܴ�\n�������޸�����",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���ؾ�����",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ���㵹��ʱ����\nż�������ؾ����߳�\n�ְ��㸴��",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ���㵹��ʱ����\n��Ƶ���������ؾ���\n�߳��ְ��㸴��",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ���㵹��ʱ����\n���������ؾ����߳�\n�ְ��㸴��",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���ؿ�",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ���ؿ�ż�����\n����V.A.T.S.�����\n��",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ���ؿ;������\n����V.A.T.S.�����\n��",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ���ؿ���V.A.T.\nS.�г����˺ܶ�Σ�\n��֪���������",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"���ص���",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    �������������\n��ʳ�ü�����֯����\n����ֵ����߸���",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ���������ɸ���\n��ʳ�ü�����֯����\n����ֵ����߸���",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ���������ɴ���\n��ʳ�ü�����֯����\n����ֵ����߸���",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"һǹ�����",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ����ǹе��4%��\n�������ʧ�⣬��4%\n�ĸ�������²�",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ����ǹе��8%��\n�������ʧ�⣬��8%\n�ĸ�������²�",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ����ǹе��12%��\n�������ʧ�⣬��12%\n�ĸ�������²�",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ҩ��˾",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ��40%�ļ�������\n����ҩ������ʱ�ҵ�\n����ļ���ҩ��",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��60%�ļ�������\n����ҩ������ʱ�ҵ�\n����ļ���ҩ��",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��80%�ļ�������\n����ҩ������ʱ�ҵ�\n����ļ���ҩ��",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��̬ɱ�˿�",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ��V.A.T.S.�У�\nÿ���һ�λ�ɱ����\n5%�ļ���ʹ��ı���\n�Ƴ���",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��V.A.T.S.�У�\nÿ���һ�λ�ɱ����\n10%�ļ���ʹ��ı���\n�Ƴ���",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��V.A.T.S.�У�\nÿ���һ�λ�ɱ����\n15%�ļ���ʹ��ı���\n�Ƴ���",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ��6%�ļ��ʿ���\n�ڵ������ʱ������\n��װ���",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��12%�ļ��ʿ���\n�ڵ������ʱ������\n��װ���",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��18%�ļ��ʿ���\n�ڵ������ʱ������\n��װ���",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ��6%�ļ��ʷ���\n���˵Ĳ���Զ���˺�\n����PVP��",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��12%�ļ��ʷ���\n���˵Ĳ���Զ���˺�\n����PVP��",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��18%�ļ��ʷ���\n���˵Ĳ���Զ���˺�\n����PVP��",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ѹ���",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ��40%�ļ�������\n��ҩ�����ҵ������\n��ҩ",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��60%�ļ�������\n��ҩ�����ҵ������\n��ҩ",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��80%�ļ�������\n��ҩ�����ҵ������\n��ҩ",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ����ֵ����30%��\n״̬�£���15%�ļ���\n�����ܵ��˺���δװ\n������װ�ף�",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ����ֵ����30%��\n״̬�£���30%�ļ���\n�����ܵ��˺���δװ\n������װ�ף�",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ����ֵ����30%��\n״̬�£���45%�ļ���\n�����ܵ��˺���δװ\n������װ�ף�",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�������˶�",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ����������ʱ��\n��10%�ļ�����������\n˫�ݳ�Ʒ��",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ����������ʱ��\n��20%�ļ�����������\n˫�ݳ�Ʒ��",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ����������ʱ��\n��30%�ļ�����������\n˫�ݳ�Ʒ��",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ĥ��",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ��Ĳ�ǹ������\n5%�������Ŀ��֫��\n�з�",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��Ĳ�ǹ������\n10%�������Ŀ��֫��\n�з�",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��Ĳ�ǹ������\n15%�������Ŀ��֫��\n�з�",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"Ц�����",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ����ʱ�����Ʒ\n���ӳ�һö�������\n������",
		1
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ΰͱ���",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ��Ʒ�����ʳ��\n�����ٶȼ���30%",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��Ʒ�����ʳ��\n�����ٶȼ���60%",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    ��Ʒ�����ʳ��\n�����ٶȼ���90%",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ķ",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    �ڸ����������\nʱ����50%�ļ��ʲ���\n��ҽ����",
		1
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����ݳ�",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ���޺���־����\n�����ʱ�䷭��",
		1
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ������ľ�ɻ��\n����ľ��",
		1
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"׷����",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    �����������\n���ڼ��������ָ�",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    �����������\n���ڼ��ø��������ָ�",
		2
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��̻���",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    ���ٴӷ����б�\n��ĸ��ʣ�ͬʱҲ��\n�����������Ʊ����\n����",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    ����ӷ����б�\n�죬������Ҳ�޷���\n������",
		2
	);
	(*this->luck.rbegin())->finishAddingLevel();

}

void Body::initLegend() {

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ���1��������1\n��������������������\n����������������Ϊ\n15",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���2��������2\n��������������������\n����������������Ϊ\n15",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���3��������3\n��������������������\n����������������Ϊ\n15",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���5��������5\n��������������������\n����������������Ϊ\n15",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�����֪",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ���1���֪��1\n���֪��������������\n����������������Ϊ\n15",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���2���֪��2\n���֪��������������\n����������������Ϊ\n15",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���3���֪��3\n���֪��������������\n����������������Ϊ\n15",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���5���֪��5\n���֪��������������\n����������������Ϊ\n15",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ���1��������1\n��������������������\n����������������Ϊ\n15",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���2��������2\n��������������������\n����������������Ϊ\n15",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���3��������3\n��������������������\n����������������Ϊ\n15",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���5��������5\n��������������������\n����������������Ϊ\n15",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ���1��������1\n��������������������\n����������������Ϊ\n15",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���2��������2\n��������������������\n����������������Ϊ\n15",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���3��������3\n��������������������\n����������������Ϊ\n15",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���5��������5\n��������������������\n����������������Ϊ\n15",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ���1��������1\n��������������������\n����������������Ϊ\n15",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���2��������2\n��������������������\n����������������Ϊ\n15",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���3��������3\n��������������������\n����������������Ϊ\n15",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���5��������5\n��������������������\n����������������Ϊ\n15",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ���1�����ݺ�1\n�����ݸ�������������\n����������������Ϊ\n15",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���2�����ݺ�2\n�����ݸ�������������\n����������������Ϊ\n15",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���3�����ݺ�3\n�����ݸ�������������\n����������������Ϊ\n15",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���5�����ݺ�5\n�����ݸ�������������\n����������������Ϊ\n15",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ���1�����˺�1\n�����˸�������������\n����������������Ϊ\n15",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���2�����˺�2\n�����˸�������������\n����������������Ϊ\n15",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���3�����˺�3\n�����˸�������������\n����������������Ϊ\n15",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���5�����˺�5\n�����˸�������������\n����������������Ϊ\n15",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����������",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ������װ��ʱ\n��������15��������\n����Ѫ����",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ������װ��ʱ\n��������20��������\n����Ѫ����",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ������װ��ʱ\n��������30��������\n����Ѫ����",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ������װ��ʱ\n��������40��������\n����Ѫ����",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    �ڶ���װ��ģʽ\n�£�������ĵ��ж�\n��������20%",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    �ڶ���װ��ģʽ\n�£�������ĵ��ж�\n��������30%",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    �ڶ���װ��ģʽ\n�£�������ĵ��ж�\n��������40%",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    �ڶ���װ��ģʽ\n�£�������ĵ��ж�\n��������50%",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ҩ����",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ������ҩʱ����\n����50%",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ������ҩʱ����\n����75%",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ������ҩʱ����\n����100%",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ������ҩʱ����\n����150%",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����ҩ��ʦ",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ÿСʱ����1��ս\n��ǿ��ҩ��������\n��3��",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ÿ50��������1��\nս��ǿ��ҩ�������\n�ɴ�4��",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ÿ40��������1��\nս��ǿ��ҩ�������\n�ɴ�5��",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ÿ40��������2��\nս��ǿ��ҩ�������\n�ɴ�5��",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ��V.A.T.S.�У�\n��ս������20������\n��������˺�",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ��V.A.T.S.�У�\n��ս������30������\n��������˺�",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ��V.A.T.S.�У�\n��ս������40������\n��������˺�",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ��V.A.T.S.�У�\n��ս������50������\n��������˺�",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�ἺΪ��",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ���㴦�����״\n̬�У��ҵ��˹�����\nʱ�����ǽ�����10%\n�Ķ����˺�",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���㴦�����״\n̬�У��ҵ��˹�����\nʱ�����ǽ�����20%\n�Ķ����˺�",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���㴦�����״\n̬�У��ҵ��˹�����\nʱ�����ǽ�����30%\n�Ķ����˺�",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���㴦�����״\n̬�У��ҵ��˹�����\nʱ�����ǽ�����40%\n�Ķ����˺�",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����䤱�",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ����������ƥ��\n�Ļ���ʱ��+50������\n������",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ����������ƥ��\n�Ļ���ʱ��+100����\n�˺�����",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ����������ƥ��\n�Ļ���ʱ��+150����\n�˺�����",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ����������ƥ��\n�Ļ���ʱ��+200����\n�˺�����",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"Ǳ�д�ʦ",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    �Զ�����0����\n�˺����������ͺڿ�\n����+3",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    �Զ�����1����\n�˺����������ͺڿ�\n����+3",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    �Զ�����2����\n�˺����������ͺڿ�\n����+3",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    �Զ�����3����\n�˺����������ͺڿ�\n����+3",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��������",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ����������ƥ��\n�Ļ���ʱ��+50������\n������",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ����������ƥ��\n�Ļ���ʱ��+100����\n�˺�����",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ����������ƥ��\n�Ļ���ʱ��+150����\n�˺�����",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ����������ƥ��\n�Ļ���ʱ��+200����\n�˺�����",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"��ը��Ⱦ",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ��Ͷ����ը���\nɱ�ĵ�����20%�ļ���\n�ᱬը",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ��Ͷ����ը���\nɱ�ĵ�����30%�ļ���\n�ᱬը",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ��Ͷ����ը���\nɱ�ĵ�����40%�ļ���\n�ᱬը",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ��Ͷ����ը���\nɱ�ĵ�����50%�ļ���\n�ᱬը",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"������",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ͽ��ʱ����5%��\n�ʿ�������ʱ������\nը",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ͽ��ʱ����10%��\n�ʿ�������ʱ������\nը",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ͽ��ʱ����15%��\n�ʿ�������ʱ������\nը",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ͽ��ʱ����20%��\n�ʿ�������ʱ������\nը",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����ݾ�",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ÿ30��������1��\n����������ҩ���\n��Ϊ5��",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ÿ25��������1��\n����������ҩ���\n��Ϊ6��",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ÿ20��������1��\n����������ҩ���\n��Ϊ7��",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ÿ20��������2��\n����������ҩ���\n��Ϊ10��",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�������",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ���˵���������\n��10%����Ϊ��Ķ���\nװ����ľ۱���ĳ�\n��",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���˵���������\n��13%����Ϊ��Ķ���\nװ����ľ۱���ĳ�\n��",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���˵���������\n��16%����Ϊ��Ķ���\nװ����ľ۱���ĳ�\n��",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���˵���������\n��20%����Ϊ��Ķ���\nװ����ľ۱���ĳ�\n��",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ѪծѪ��",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    �ɹ��񵲽�ս��\n��ʱ�ظ�1������ֵ��\n1���ж�����������15\n��",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    �ɹ��񵲽�ս��\n��ʱ�ظ�2������ֵ��\n2���ж�����������15\n��",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    �ɹ��񵲽�ս��\n��ʱ�ظ�3������ֵ��\n3���ж�����������15\n��",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    �ɹ��񵲽�ս��\n��ʱ�ظ�4������ֵ��\n4���ж�����������15\n��",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"Ѫ��",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    �����󣬶��ѽ�\n���+25�˺����ԣ���\n��8���ڻظ�40����\nֵ",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    �����󣬶��ѽ�\n���+30�˺����ԣ���\n��10���ڻظ�50����\nֵ",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    �����󣬶��ѽ�\n���+35�˺����ԣ���\n��12���ڻظ�60����\nֵ",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    �����󣬶��ѽ�\n���+40�˺����ԣ���\n��14���ڻظ�70����\nֵ",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����Ϊ��",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    +50���俹�ԣ�ÿ\n��ظ�1�����ֵ",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    +75���俹�ԣ�ÿ\n��ظ�2�����ֵ",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    +100���俹�ԣ�\nÿ��ظ�3�����ֵ",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    +300���俹�ԣ�\nÿ��ظ�6�����ֵ",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"ңԶ�̻�",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ��Զ��������ɱ\n�ĵ�����10%���ʻᱬ\nը",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ��Զ��������ɱ\n�ĵ�����13%���ʻᱬ\nը",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ��Զ��������ɱ\n�ĵ�����16%���ʻᱬ\nը",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ��Զ��������ɱ\n�ĵ�����20%���ʻᱬ\nը",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"�����˺�",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    ���ս������ɱ\n�ĵ�����10%���ʻᱬ\nը",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���ս������ɱ\n�ĵ�����13%���ʻᱬ\nը",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���ս������ɱ\n�ĵ�����16%���ʻᱬ\nը",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    ���ս������ɱ\n�ĵ�����20%���ʻᱬ\nը",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"����֮��",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    10���ڣ���Ǳ��\n״̬�¶�Ŀ����ɵ�\nԶ���˺�����10%",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    10���ڣ���Ǳ��\n״̬�¶�Ŀ����ɵ�\nԶ���˺�����20%",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    10���ڣ���Ǳ��\n״̬�¶�Ŀ����ɵ�\nԶ���˺�����30%",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    10���ڣ���Ǳ��\n״̬�¶�Ŀ����ɵ�\nԶ���˺�����40%",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

}