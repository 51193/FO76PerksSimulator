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
		L"子弹带",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    实弹武器弹药的\n重量减轻45%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    实弹武器弹药的\n重量减轻90%",
		2
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"《蛮人古古那》",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    未装备动力装甲\n时，每点力量+2能量\n抗性（最高40点）",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    未装备动力装甲\n时，每点力量+3能量\n抗性（最高60点）",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    未装备动力装甲\n时，每点力量+4能量\n抗性（最高80点）",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"破坏者",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    枪托打击造成的\n伤害+25%，并有5%的\n几率致残你的对手",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    枪托打击造成的\n伤害+50%，并有10%的\n几率致残你的对手",
		2
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"熊臂持枪",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    重型枪械的重量\n减轻30%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    重型枪械的重量\n减轻60%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    重型枪械的重量\n减轻90%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"重击者",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的双手近\n战武器造成的伤害+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的双手近\n战武器造成的伤害+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的双手近\n战武器造成的伤害+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"专家级重击者",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的双手近\n战武器造成的伤害+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的双手近\n战武器造成的伤害+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的双手近\n战武器造成的伤害+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"大师级重击者",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的双手近\n战武器造成的伤害+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的双手近\n战武器造成的伤害+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的双手近\n战武器造成的伤害+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"阻攻手",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    收到来自敌人的\n近战攻击伤害减少15%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    收到来自敌人的\n近战攻击伤害减少30%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    收到来自敌人的\n近战攻击伤害减少45%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"角斗士",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的单手近\n战武器造成的伤害+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的单手近\n战武器造成的伤害+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的单手近\n战武器造成的伤害+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"专家级角斗士",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的单手近\n战武器造成的伤害+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的单手近\n战武器造成的伤害+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的单手近\n战武器造成的伤害+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"大师级角斗士",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的单手近\n战武器造成的伤害+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的单手近\n战武器造成的伤害+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的单手近\n战武器造成的伤害+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"重枪手",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的非爆破\n性重型枪械造成的伤\n害+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的非爆破\n性重型枪械造成的伤\n害+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的非爆破\n性重型枪械造成的伤\n害+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"专家级重枪手",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的非爆破\n性重型枪械造成的伤\n害+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的非爆破\n性重型枪械造成的伤\n害+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的非爆破\n性重型枪械造成的伤\n害+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"大师级重枪手",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的非爆破\n性重型枪械造成的伤\n害+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的非爆破\n性重型枪械造成的伤\n害+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的非爆破\n性重型枪械造成的伤\n害+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"门牙",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    你的近战武器以\n及徒手攻击无视对方\n25%的护甲",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    你的近战武器以\n及徒手攻击无视对方\n50%的护甲",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    你的近战武器以\n及徒手攻击无视对方\n75%的护甲",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"铁拳",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的拳击造\n成的伤害+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的拳击造\n成的伤害+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的拳击造\n成的伤害+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"子弹上膛",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    重型枪械装填速\n度提高10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    重型枪械装填速\n度提高20%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    重型枪械装填速\n度提高30%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"武术家",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    你的近战武器重\n量减少了20%，挥动\n速度提高了10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    你的近战武器重\n量减少了40%，挥动\n速度提高了20%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    你的近战武器重\n量减少了60%，挥动\n速度提高了30%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"军火运输",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    爆炸物重量减轻\n30%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    爆炸物重量减轻\n60%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    爆炸物重量减轻\n90%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"仓鼠",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    所有垃圾物品的\n重量减少25%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    所有垃圾物品的\n重量减少50%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    所有垃圾物品的\n重量减少75%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"天堂路",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    穿着动力装甲时，\n向敌人冲刺可对敌人\n造成伤害和失衡",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    穿着动力装甲时，\n向敌人冲刺可对敌人\n造成大量伤害，并且\n能使他们失衡",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    穿着动力装甲时，\n向敌人冲刺可对敌人\n造成巨量伤害，并且\n能使他们失衡",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"散弹",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    散弹枪重量减少\n了30%，装填速度提高\n10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    散弹枪重量减少\n了60%，装填速度提高\n20%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    散弹枪重量减少\n了90%，装填速度提高\n30%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"散弹枪手",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的散弹枪\n造成的伤害+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的散弹枪\n造成的伤害+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的散弹枪\n造成的伤害+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"专家级散弹枪手",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的散弹枪\n造成的伤害+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的散弹枪\n造成的伤害+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的散弹枪\n造成的伤害+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"大师级散弹枪手",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的散弹枪\n造成的伤害+10%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的散弹枪\n造成的伤害+15%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    现在你的散弹枪\n造成的伤害+20%",
		3
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"虎背",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    负重上限+10",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    负重上限+20",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    负重上限+30",
		3
	);
	(*this->strenth.rbegin())->addLevel(
		L"    负重上限+40",
		4
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"体格健壮",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    装甲比正常重量\n轻25%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    装甲比正常重量\n轻50%",
		2
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"完全充能",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    穿着动力装甲冲\n刺的时候，只消耗原\n来一半的聚变核心能\n量",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    穿着动力装甲冲\n刺的时候，不再消耗\n额外的聚变核心能量",
		2
	);
	(*this->strenth.rbegin())->finishAddingLevel();

	this->strenth.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"旅行药房",
		sf::Color::Color(98, 136, 106),
		this->strenth.size()
	));
	(*this->strenth.rbegin())->addLevel(
		L"    所有药物（包括\n治疗针）的重量减少\n了30%",
		1
	);
	(*this->strenth.rbegin())->addLevel(
		L"    所有药物（包括\n治疗针）的重量减少\n了60%",
		2
	);
	(*this->strenth.rbegin())->addLevel(
		L"    所有药物（包括\n治疗针）的重量减少\n了90%",
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
		L"洞察力",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    你可以在V.A.T.\nS.中查看目标各项伤\n害抗性的具体情况",
		2
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"突击队",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    基础战斗训练意\n味着自动步枪造成的\n伤害+10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    基础战斗训练意\n味着自动步枪造成的\n伤害+15%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    基础战斗训练意\n味着自动步枪造成的\n伤害+20%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"专家级突击队员",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    严格战斗训练意\n味着自动步枪造成的\n伤害+10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    严格战斗训练意\n味着自动步枪造成的\n伤害+15%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    严格战斗训练意\n味着自动步枪造成的\n伤害+20%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"大师级突击队员",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    长久以来的战斗\n训练让你在使用自动\n步枪时造成的伤害+10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    长久以来的战斗\n训练让你在使用自动\n步枪时造成的伤害+15%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    长久以来的战斗\n训练让你在使用自动\n步枪时造成的伤害+20%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"集中火力",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    现在V.A.T.S.会\n瞄准目标肢体，集中\n火力可以让每一发射\n击获得准确度和伤害",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    现在V.A.T.S.会\n瞄准目标肢体，集中\n火力可以让每一发射\n击获得更高准确度和\n伤害",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    现在V.A.T.S.会\n瞄准目标肢体，集中\n火力可以让每一发射\n击获得高准确度和伤\n害",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"百发百中",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    使用瞄具瞄准时，\n所有手枪射程和精确\n度提高10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    使用瞄具瞄准时，\n所有手枪射程和精确\n度提高20%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    使用瞄具瞄准时，\n所有手枪射程和精确\n度提高30%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"杀虫剂",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    你的攻击无视所\n有昆虫25%的护甲",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    你的攻击无视所\n有昆虫50%的护甲",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    你的攻击无视所\n有昆虫75%的护甲",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"小心手雷",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    扔投掷武器的时\n候可以看见投掷弧线，\n并且提高15%的投掷距\n离",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    扔投掷武器的时\n候可以看见投掷弧线，\n并且提高30%的投掷距\n离",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    扔投掷武器的时\n候可以看见投掷弧线，\n并且提高50%的投掷距\n离",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"荧光瞄具",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    对发光敌人的伤\n害+20%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    对发光敌人的伤\n害+40%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    对发光敌人的伤\n害+60%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"园艺高手",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    收获植物的时候，\n获得两倍收成",
		1
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"掷弹兵",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    爆炸半径增加50%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    爆炸半径翻倍",
		2
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"地面进攻",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    现在自动步枪装\n填速度加快10%，并获\n得更好的腰射精准度",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    现在自动步枪装\n填速度加快20%，并获\n得进一步的腰射精准\n度",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    现在自动步枪装\n填速度加快30%，并获\n得绝佳的腰射精准度",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"狙击高手",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    使用瞄具瞄准时，\n你的步枪射程和精确\n度提高10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    使用瞄具瞄准时，\n你的步枪射程和精确\n度提高20%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    使用瞄具瞄准时，\n你的步枪射程和精确\n度提高30%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"夜眸",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    在下午6点至早上\n6点潜行时获得夜视能\n力",
		2
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"夜猫子",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    晚上6点至早上6\n点，智力+1，感知+1",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    晚上6点至早上6\n点，智力+2，感知+2",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    晚上6点至早上6\n点，智力+3，感知+3",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"屠夫之赐",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    40%几率从动物的\n尸体上找到额外的肉",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    60%几率从动物的\n尸体上找到额外的肉",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    80%几率从动物的\n尸体上找到额外的肉",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"开锁",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    获得+1开锁技能，\n并使开锁时的最佳范\n围提高10%",
		1
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"专家级开锁",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    获得+1开锁技能，\n并使开锁时的最佳范\n围提高10%",
		1
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"大师级开锁",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    获得+1开锁技能，\n并使开锁时的最佳范\n围提高10%",
		1
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"折射镜",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    现在你的能量抗\n性+10",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    现在你的能量抗\n性+20",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    现在你的能量抗\n性+30",
		3
	);
	(*this->perception.rbegin())->addLevel(
		L"    现在你的能量抗\n性+40",
		4
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"步枪手",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    现在你的非自动\n步枪造成的伤害+10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    现在你的非自动\n步枪造成的伤害+15%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    现在你的非自动\n步枪造成的伤害+20%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"专家级步枪手",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    现在你的非自动\n步枪造成的伤害+10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    现在你的非自动\n步枪造成的伤害+15%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    现在你的非自动\n步枪造成的伤害+20%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"大师级步枪手",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    现在你的非自动\n步枪造成的伤害+10%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    现在你的非自动\n步枪造成的伤害+15%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    现在你的非自动\n步枪造成的伤害+20%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"双向飞碟射击",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    你的散弹枪的精\n确度和弹药散步提升",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    你的散弹枪的精\n确度和弹药散步进一\n步提升",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    你的散弹枪的精\n确度和弹药散步极大\n提升",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"狙击手",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    在瞄准时获得更\n好的控制力，屏住呼\n吸时间延长25%",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    在瞄准时获得更\n好的控制力，屏住呼\n吸时间延长50%",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    在瞄准时获得更\n好的控制力，屏住呼\n吸时间延长75%",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"坦克杀手",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    使用步枪和手枪\n攻击时将无视目标12%\n的护甲，并有3%几率\n能使敌方陷入失衡状\n态",
		1
	);
	(*this->perception.rbegin())->addLevel(
		L"    使用步枪和手枪\n攻击时将无视目标24%\n的护甲，并有6%几率\n能使敌方陷入失衡状\n态",
		2
	);
	(*this->perception.rbegin())->addLevel(
		L"    使用步枪和手枪\n攻击时将无视目标36%\n的护甲，并有9%几率\n能使敌方陷入失衡状\n态",
		3
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"杂志收藏家",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    范围内有杂志时，\n会听见提示音",
		1
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"感知娃娃",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    范围内有娃娃时，\n会听见提示音",
		1
	);
	(*this->perception.rbegin())->finishAddingLevel();

	this->perception.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"寻宝高手",
		sf::Color::Color(88, 80, 53),
		this->perception.size()
	));
	(*this->perception.rbegin())->addLevel(
		L"    在范围内有瓶盖\n盒时，会听到定向提\n示音",
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
		L"超合金骨骼",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    你肢体受到的伤\n害现在减少30%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    你肢体受到的伤\n害现在减少60%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    你肢体现在完全\n不受伤害",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"通宵",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    你在夜间的饥饿\n和口渴耐性提高了20%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    你在夜间的饥饿\n和口渴耐性提高了40%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    你在夜间的饥饿\n和口渴耐性提高了60%",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"食人族",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    食用人类、尸鬼、\n超级变种人、辐尸人\n或是鼹鼠矿工的尸体\n可以恢复生命值和饥\n饿程度",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    食用人类、尸鬼、\n超级变种人、辐尸人\n或是鼹鼠矿工的尸体\n可以恢复更多的生命\n值和饥饿程度",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    食用人类、尸鬼、\n超级变种人、辐尸人\n或是鼹鼠矿工的尸体\n可以恢复极多的生命\n值和饥饿程度",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"嗜药恶魔",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    服用任何药物药\n效时间都增加30%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    服用任何药物药\n效时间都增加60%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    服用任何药物药\n效时间都增加100%",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"药物抗性",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    服用药物时，上\n瘾的机会降低一半",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    你获得对药物上\n瘾的完全免疫力",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"可乐爱好者",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    核子可乐增益倍\n增",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    核子可乐增益为\n原先三倍",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"单峰骆驼",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    所有饮料额外缓\n解25%的口渴程度",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    所有饮料额外缓\n解50%的口渴程度",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    所有饮料额外缓\n解75%的口渴程度",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"防火",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    受到的来自爆炸\n和火焰攻击的伤害减\n少15%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    受到的来自爆炸\n和火焰攻击的伤害减\n少30%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    受到的来自爆炸\n和火焰攻击的伤害减\n少75%",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"尸鬼体质",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    受到辐射时可以\n使你损失的生命值得\n到恢复",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    受到辐射时可以\n使你损失的生命值恢\n复率更高",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    受到辐射时可以\n使你损失的生命值恢\n复率更高",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"家里蹲",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    在营地或工坊中\n可以逐渐恢复生命值",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    在营地或工坊中\n可以提高生命值并获\n得肢体再生",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"铁甲衣",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    当你没有穿动力\n装甲时获得10伤害和\n能量抗性",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    当你没有穿动力\n装甲时获得20伤害和\n能量抗性",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    当你没有穿动力\n装甲时获得30伤害和\n能量抗性",
		3
	);
	(*this->endurance.rbegin())->addLevel(
		L"    当你没有穿动力\n装甲时获得40伤害和\n能量抗性",
		4
	);
	(*this->endurance.rbegin())->addLevel(
		L"    当你没有穿动力\n装甲时获得50伤害和\n能量抗性",
		5
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"百毒不侵",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    你因进食而患病\n的几率减少30%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    你因进食而患病\n的几率减少60%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    你因进食而患病\n的几率减少90%",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"铜肠铁胃",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    来自饮食的辐射\n降低30%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    来自饮食的辐射\n降低60%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    不会因为饮食而\n摄取辐射",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"赐命者",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    增加15点最大生\n命值上限",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    增加30点最大生\n命值上限",
		3
	);
	(*this->endurance.rbegin())->addLevel(
		L"    增加45点最大生\n命值上限",
		4
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"克制口腹之欲",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    服用药物时减少\n50%饥饿值惩罚",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    现在服用药物不\n会再造成饥饿",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"环境抗性",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    你因周边环境而\n患病的几率减少30%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    你因周边环境而\n患病的几率减少60%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    你因周边环境而\n患病的几率减少90%",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"夜之坚韧",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    晚上6点至早上6\n点，最大生命值+20",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    晚上6点至早上6\n点，最大生命值+40",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"光合作用",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    在早上6点到晚上\n6点之间获得生命值恢\n复",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    在早上6点到晚上\n6点之间获得更高生命\n值恢复",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"辐无敌",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    辐射程度越高，\n力量越高（最高5点力\n量）",
		1
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"抗辐射",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    现在辐射抗性+10",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    现在辐射抗性+20",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    现在辐射抗性+30",
		3
	);
	(*this->endurance.rbegin())->addLevel(
		L"    现在辐射抗性+40",
		4
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"精神百倍",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    在饱腹和饮水充\n足时增益提升",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    在饱腹和饮水充\n足时增益更佳",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"亡者归来",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    你被别的玩家复\n活时，可以在2分钟内\n获得+25%伤害加成",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    你被别的玩家复\n活时，可以在2分钟内\n获得+50%伤害加成",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"慢速代谢剂",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    所有食物额外缓\n解25%的饥饿程度",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    所有食物额外缓\n解50%的饥饿程度",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    所有食物额外缓\n解75%的饥饿程度",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"太阳能供电",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    早上6点至晚上6\n点期间，获得力量加\n成和耐力加成各1点",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    早上6点至晚上6\n点期间，获得力量加\n成和耐力加成各2点",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    早上6点至晚上6\n点期间，获得力量加\n成和耐力加成各3点",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"太阳之吻",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    在早上6点到下午\n6点之间可以缓慢恢复\n辐射伤害",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    在早上6点到下午\n6点之间可以快速恢复\n辐射伤害",
		2
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"解渴饮品",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    喝下液体引发疾\n病的概率降低30%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    喝下液体引发疾\n病的概率降低60%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    喝下液体引发疾\n病的概率降低90%",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"接种疫苗",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    你从其他生物感\n染到疾病的几率减少\n30%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    你从其他生物感\n染到疾病的几率减少\n60%",
		2
	);
	(*this->endurance.rbegin())->addLevel(
		L"    你从其他生物感\n染到疾病的几率减少\n90%",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"水男孩",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    游泳时你不会再\n受到辐射伤害，并且\n可以在水下呼吸",
		1
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"专职酒鬼",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    你绝不可能染上\n酒瘾",
		3
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"乖狗狗",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    吃狗粮可以获得\n三倍增益",
		1
	);
	(*this->endurance.rbegin())->finishAddingLevel();

	this->endurance.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"修复水力发电设施",
		sf::Color::Color(99, 167, 175),
		this->endurance.size()
	));
	(*this->endurance.rbegin())->addLevel(
		L"    药物产生的口渴\n程度降低50%",
		1
	);
	(*this->endurance.rbegin())->addLevel(
		L"    药物不会再导致\n口渴",
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
		L"动物朋友",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    把你的枪对准动\n物，会有25%的几率让\n它安静下来",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    把你的枪对准动\n物，会有50%的几率让\n它安静下来",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    把你的枪对准动\n物，会有75%的几率让\n它安静下来",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"保镖",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    除了你自己之外，\n每位队友将使你获得6\n伤害&能量抗性（最多\n18）",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    除了你自己之外，\n每位队友将使你获得8\n伤害&能量抗性（最多\n18）",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    除了你自己之外，\n每位队友将使你获得\n10伤害&能量抗性（最\n多18）",
		3
	);
	(*this->charisma.rbegin())->addLevel(
		L"    除了你自己之外，\n每位队友将使你获得\n12伤害&能量抗性（最\n多18）",
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
		L"    你复活的玩家将\n在15秒内获得生命恢\n复",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    你复活的玩家将\n在30秒内获得更高的\n生命恢复",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    你复活的玩家将\n在60秒内获得最高的\n生命恢复",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"充满魅力",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    除你以外的每一\n位队友为你提供1点魅\n力",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    除你以外的每一\n位队友为你提供2点魅\n力",
		2
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"军医",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    现在治疗针和消\n辐宁的药效变得更快\n了",
		2
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"友谊之火",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    队友在遭受你火\n焰攻击时，会暂时恢\n复生命值（不含手雷）",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    队友在遭受你火\n焰攻击时，会暂时恢\n复较多生命值（不含\n手雷）",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    队友在遭受你火\n焰攻击时，会暂时恢\n复更多生命值（不含\n手雷）",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"快乐露营者",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    身处己方队伍的\n工坊中时，饥饿与口\n渴增长速度放缓40%",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    身处己方队伍的\n工坊中时，饥饿与口\n渴增长速度放缓80%",
		2
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"逍遥自在",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    受到酒精影响时，\n你的运气+2",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    受到酒精影响时，\n你的运气+3",
		2
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"苛刻的交易",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    能在非玩家贩卖\n机器人那里获得更优\n惠的买卖价格",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    能在非玩家贩卖\n机器人那里获得非常\n优惠的买卖价格",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    在非玩家贩卖机\n器人那里的买卖价格\n比以前更优惠了",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"注射器",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    由你复活的玩家\n10分钟内行动点恢复\n+6",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    由你复活的玩家\n10分钟内行动点恢复\n+12",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    由你复活的玩家\n10分钟内行动点恢复\n+18",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"激励",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    当你处组队状态\n中，你和你的队友们\n可以获得5%的额外经\n验值",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    当你处组队状态\n中，你和你的队友们\n可以获得10%的额外经\n验值",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    当你处组队状态\n中，你和你的队友们\n可以获得15%的额外经\n验值",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"独行侠",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    独自冒险时，所\n受的伤害减少10%，同\n时行动点的恢复速度\n增加10%",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    独自冒险时，所\n受的伤害减少20%，同\n时行动点的恢复速度\n增加20%",
		3
	);
	(*this->charisma.rbegin())->addLevel(
		L"    独自冒险时，所\n受的伤害减少30%，同\n时行动点的恢复速度\n增加30%",
		4
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"过度慷慨",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    体内的辐射值将\n增加近身攻击对目标\n造成25点的辐射的几\n率",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    体内的辐射值将\n增加近身攻击对目标\n造成50点的辐射的几\n率",
		2
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"派对男孩",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    战前酒类的正面\n影响变为双倍",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    战前酒类的正面\n影响变为三倍",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"慈善家",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    你在进食或者喝\n水时会为队友缓解部\n分饥饿与口渴",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    你在进食或者喝\n水时会为队友缓解较\n多饥饿与口渴",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    你在进食或者喝\n水时会为队友缓解大\n量饥饿与口渴",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"蒙古大夫",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    用酒精复活其他\n玩家",
		1
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"辐射海绵",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    受辐射影响时，\n你可以周期性地为附\n近队友治疗80点辐射\n值",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    受辐射影响时，\n你可以周期性地为附\n近队友治疗140点辐射\n值",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    受辐射影响时，\n你可以周期性地为附\n近队友治疗200点辐射\n值",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"灵魂医者",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    复活其他玩家后5\n秒内你可以恢复生命\n值",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    复活其他玩家后7\n秒内你可以恢复生命\n值",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    复活其他玩家后\n10秒内你可以恢复生\n命值",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"小队机动",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    在小队中奔跑速\n度加快10%",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    在小队中奔跑速\n度加快20%",
		2
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"消音器",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    击中目标后，2秒\n内减少其10%的伤害输\n出",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    击中目标后，2秒\n内减少其20%的伤害输\n出",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    击中目标后，2秒\n内减少其30%的伤害输\n出",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"团队医护兵",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    你的治疗针现在\n也可以医疗附近的队\n友，效果是正常的50%",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    你的治疗针现在\n也可以医疗附近的队\n友，效果是正常的75%",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    你的治疗针现在\n也可以医疗附近的队\n友，效果是正常的\n100%",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"松肉锤",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    在你攻击后，你\n的目标在5秒内承受5%\n的额外伤害",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    在你攻击后，你\n的目标在7秒内承受7%\n的额外伤害",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    在你攻击后，你\n的目标在10秒内承受\n10%的额外伤害",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"吸血生物",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    血浆包现在可以\n缓解口渴，效果增加\n50%以上，并且不再产\n生辐射",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    血浆包现在可以\n更好地口渴，效果增\n加100%以上，并且不再\n产生辐射",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    血浆包现在可以\n显著地口渴，效果增\n加150%以上，并且不再\n产生辐射",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"废土低语者",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    把你的枪对准一\n些生物，会有25%的几\n率让它安静下来",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    把你的枪对准一\n些生物，会有50%的几\n率让它安静下来",
		2
	);
	(*this->charisma.rbegin())->addLevel(
		L"    把你的枪对准一\n些生物，会有75%的几\n率让它安静下来",
		3
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"旅行中介",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    进行快速移动时\n少付30%的瓶盖",
		1
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"卫生防疫",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    你的疾病被治愈\n时，有50%的几率可以\n为附近的队友治疗一\n种疾病",
		1
	);
	(*this->charisma.rbegin())->addLevel(
		L"    你的疾病被治愈\n时，必然可以为附近\n的队友治疗一种疾病",
		2
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"多多益善",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    如果队友也有变\n异，正面变异效果\n+25%",
		1
	);
	(*this->charisma.rbegin())->finishAddingLevel();

	this->charisma.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"治疗之手",
		sf::Color::Color(198, 116, 58),
		this->charisma.size()
	));
	(*this->charisma.rbegin())->addLevel(
		L"    由你复活的玩家\n将消除所有辐射值",
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
		L"装甲商",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    现在你可以制作\n高级护甲改装件（需\n要设计图）",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    现在制作装甲的\n材料消耗减少",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你制作的护甲耐\n久性提高",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"内置电池",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    能量武器弹药的\n重量减轻30%",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    能量武器弹药的\n重量减轻60%",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    能量武器弹药的\n重量减轻90%",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"承包商",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    工坊制造物品现\n在可以节约25%的材料",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    工坊制造物品现\n在可以节约50%的材料",
		2
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"破坏专家",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    你的爆炸物造成\n额外的20%伤害",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你的爆炸物造成\n额外的30%伤害",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你的爆炸物造成\n额外的40%伤害",
		3
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你的爆炸物造成\n额外的50%伤害",
		4
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你的爆炸物造成\n额外的60%伤害",
		5
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"急救箱",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    治疗针可额外恢\n复15%",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    治疗针可额外恢\n复30%",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    治疗针可额外恢\n复45%",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"修缮一新",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    你可以把护甲和\n动力护甲的状态修复\n到标准最大值的130%",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你可以把护甲和\n动力护甲的状态修复\n到标准最大值的160%",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你可以把护甲和\n动力护甲的状态修复\n到标准最大值的200%",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"枪械师",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    枪械损坏率降低\n10%，并且你可以制造\n等级1的枪械（需要设\n计图）",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    枪械损坏率降低\n20%，并且你可以制造\n等级2的枪械（需要设\n计图）",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    枪械损坏率降低\n30%，并且你可以制造\n等级3的枪械（需要设\n计图）",
		3
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    枪械损坏率降低\n40%，并且你可以制造\n等级4的枪械（需要设\n计图）",
		4
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    枪械损坏率降低\n50%，并且你可以制造\n等级5的枪械（需要设\n计图）",
		5
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"专业水管工",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    你的铁管武器损\n坏速度降低20%，修复\n花费也更低",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你的铁管武器损\n坏速度降低40%，修复\n花费也更低",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你的铁管武器损\n坏速度降低60%，修复\n花费也更低",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"临时武士",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    近战武器损坏率\n降低10%，并且你可以\n制造等级1的近战武器\n（需要设计图）",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    近战武器损坏率\n降低20%，并且你可以\n制造等级2的近战武器\n（需要设计图）",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    近战武器损坏率\n降低30%，并且你可以\n制造等级3的近战武器\n（需要设计图）",
		3
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    近战武器损坏率\n降低40%，并且你可以\n制造等级4的近战武器\n（需要设计图）",
		4
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    近战武器损坏率\n降低50%，并且你可以\n制造等级5的近战武器\n（需要设计图）",
		5
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"忍无可忍",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    生命值低于20%时，\n获得20伤害抗性，10%\n伤害提升以及15%的行\n动点数恢复",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    生命值低于20%时，\n获得30伤害抗性，15%\n伤害提升以及15%的行\n动点数恢复",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    生命值低于20%时，\n获得40伤害抗性，20%\n伤害提升以及15%的行\n动点数恢复",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"移动能源",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    所有动力装甲和\n机架的重量减轻25%",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    所有动力装甲和\n机架的重量减轻50%",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    所有动力装甲和\n机架的重量减轻75%",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"药剂师",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    消辐宁可消除超\n过30%辐射",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    消辐宁可消除超\n过60%辐射",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    消辐宁可去除两\n倍的辐射",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"动力师",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    现在你可以制作\n高级动力装甲改装件\n（需要设计图）",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    制作动力装甲的\n材料消耗减少",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你制作的动力装\n甲耐久性提高",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"动力使用者",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    聚变核心的持续\n时间延长30%",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    聚变核心的持续\n时间延长60%",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    现在聚变核心能\n持续两倍时间",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"机器人专家",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    黑入敌对机器人\n有25%的几率能让它平\n静下来",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    黑入敌对机器人\n有50%的几率能让它平\n静下来",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    黑入敌对机器人\n有75%的几率能让它平\n静下来",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"科学家",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    现在你已可以制\n作能量枪（需要设计\n图）",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你可以制作1级能\n量枪械改装件（需要\n设计图)",
		2
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"专家级科学家",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    你可以制作2级能\n量枪械改装件（需要\n设计图）",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    制作能量枪械消\n耗的材料更少",
		2
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"大师级科学家",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    你可以制作3级能\n量枪械改装件（需要\n设计图）",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你制作的能量枪\n耐久性提高",
		2
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"稳定",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    穿着动力装甲时，\n重型枪械获得更高精\n确度，并无视目标15%\n护甲",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    穿着动力装甲时，\n重型枪械精确度进一\n步提高，并无视目标\n30%护甲",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    穿着动力装甲时，\n重型枪械获得绝佳一\n精准度，并无视目标\n45%护甲",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"武器工匠",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    你可以修复任何\n武器到正常最大状态\n的130%",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你可以修复任何\n武器到正常最大状态\n的160%",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你可以修复任何\n武器到正常最大状态\n的200%",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"破坏者",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    你对工坊对象的\n伤害+40%",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你对工坊对象的\n伤害+80%",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你对工坊对象的\n伤害+120%",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"动力装甲修补匠",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    你的动力装甲损\n坏速度降低20%，修复\n花费也更低",
		1
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你的动力装甲损\n坏速度降低40%，修复\n花费也更低",
		2
	);
	(*this->intelligence.rbegin())->addLevel(
		L"    你的动力装甲损\n坏速度降低60%，修复\n花费也更低",
		3
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"拆解专家",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    拆解武器和护甲\n可以获得更多的部件",
		1
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"黑客",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    获得+1黑客技能，\n终端锁定时间减少",
		1
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"黑客专家",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    获得+1黑客技能，\n终端锁定时间减少",
		1
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"黑客大师",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    获得+1黑客技能，\n终端锁定时间减少",
		1
	);
	(*this->intelligence.rbegin())->finishAddingLevel();

	this->intelligence.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"化学家",
		sf::Color::Color(145, 145, 118),
		this->intelligence.size()
	));
	(*this->intelligence.rbegin())->addLevel(
		L"    制作药物时，获\n得双倍的量！",
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
		L"行动派男孩",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    行动点数恢复速\n度提高15%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    行动点数恢复速\n度提高30%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    行动点数恢复速\n度提高45%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"肾上腺素",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    30秒内每次击杀\n敌人获得+6%（最高\n36%）的伤害加成，每\n次击杀可以刷新计时",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    30秒内每次击杀\n敌人获得+7%（最高\n42%）的伤害加成，每\n次击杀可以刷新计时",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    30秒内每次击杀\n敌人获得+8%（最高\n48%）的伤害加成，每\n次击杀可以刷新计时",
		3
	);
	(*this->agility.rbegin())->addLevel(
		L"    30秒内每次击杀\n敌人获得+9%（最高\n54%）的伤害加成，每\n次击杀可以刷新计时",
		4
	);
	(*this->agility.rbegin())->addLevel(
		L"    30秒内每次击杀\n敌人获得+10%（最高\n60%）的伤害加成，每\n次击杀可以刷新计时",
		5
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"荒野求生",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    生命值低于20%时\n自动使用治疗针，每\n20秒能触发一次",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    生命值低于30%时\n自动使用治疗针，每\n20秒能触发一次",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    生命值低于40%时\n自动使用治疗针，每\n20秒能触发一次",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"机密行动",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    你的远程武器能\n造成额外15%的偷袭伤\n害",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    你的远程武器能\n造成额外30%的偷袭伤\n害",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    你的远程武器能\n造成额外50%的偷袭伤\n害",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"决死冲锋",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    生命值低于40%\n时，会消耗更多行动\n点数来加快10%的冲刺\n速度",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    生命值低于50%\n时，会消耗更多行动\n点数来加快20%的冲刺\n速度",
		2
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"狡猾",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    每次被击中可以\n避免10%的伤害，但要\n消耗30行动点",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    每次被击中可以\n避免20%的伤害，但要\n消耗30行动点",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    每次被击中可以\n避免30%的伤害，但要\n消耗30行动点",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"执法者",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    你的散弹枪有5%\n的概率造成失衡，有\n10%的概率造成致残",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    你的散弹枪有10%\n的概率造成失衡，有\n20%的概率造成致残",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    你的散弹枪有15%\n的概率造成失衡，有\n30%的概率造成致残",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"回避话题",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    未装备动力装甲\n时，每点敏捷+1点伤\n害和能量抗性（最高\n15点）",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    未装备动力装甲\n时，每点敏捷+2点伤\n害和能量抗性（最高\n30点）",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    未装备动力装甲\n时，每点敏捷+3点伤\n害和能量抗性（最高\n45点）",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"山羊腿",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    坠落伤害减少40%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    坠落伤害减少80%",
		2
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"游击队员",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    现在你的自动手\n枪造成的伤害+10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    现在你的自动手\n枪造成的伤害+15%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    现在你的自动手\n枪造成的伤害+20%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"专家级游击队员",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    现在你的自动手\n枪造成的伤害+10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    现在你的自动手\n枪造成的伤害+15%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    现在你的自动手\n枪造成的伤害+20%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"大师游击队员",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    现在你的自动手\n枪造成的伤害+10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    现在你的自动手\n枪造成的伤害+15%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    现在你的自动手\n枪造成的伤害+20%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"枪械武术",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    V.A.T.S.切换击\n杀目标时，对下一个\n目标造成的伤害+10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    V.A.T.S.切换击\n杀目标时会给之后的\n2个目标相继造成10%\n及20%的额外伤害",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    V.A.T.S.切换击\n杀目标时会给之后的\n3个目标相继造成10%、\n20%及30%的额外伤害",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"持枪飞奔者",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    装备手枪时奔跑\n速度增加10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    装备手枪时奔跑\n速度增加20%",
		2
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"神枪手",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    现在你的非自动\n手枪造成的伤害+10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    现在你的非自动\n手枪造成的伤害+15%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    现在你的非自动\n手枪造成的伤害+20%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"专家级神枪手",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    现在你的非自动\n手枪造成的伤害+10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    现在你的非自动\n手枪造成的伤害+15%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    现在你的非自动\n手枪造成的伤害+20%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"大师级神枪手",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    现在你的非自动\n手枪造成的伤害+10%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    现在你的非自动\n手枪造成的伤害+15%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    现在你的非自动\n手枪造成的伤害+20%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"保卫家园",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    你可以制作与解\n除标准陷阱，也可以\n制作标准炮塔（需要\n设计图）",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    你可以制作与解\n除高级陷阱，也可以\n制作高级炮塔（需要\n设计图）",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    你可以制作与解\n除专家级陷阱，也可\n以制作专家级炮塔\n（需要设计图）",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"马拉松运动员",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    冲刺消耗的行动\n点数减少20%（未使用\n动力装甲）",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    冲刺消耗的行动\n点数减少30%（未使用\n动力装甲）",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    冲刺消耗的行动\n点数减少40%（未使用\n动力装甲）",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"睡魔",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    你的消音武器能\n在夜晚造成额外50%的\n偷袭伤害",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    你的消音武器能\n在夜晚造成额外100%\n的偷袭伤害",
		2
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"现代叛逆",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    手枪腰射精准度\n+15%，肢体致残几率\n+4%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    手枪腰射精准度\n+30%，肢体致残几率\n+8%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    手枪腰射精准度\n+45%，肢体致残几率\n+12%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"移动标靶",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    未装备动力装甲\n时，冲刺时获得+15的\n伤害和能量抗性",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    未装备动力装甲\n时，冲刺时获得+30的\n伤害和能量抗性",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    未装备动力装甲\n时，冲刺时获得+45的\n伤害和能量抗性",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"忍者",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    使用近战武器进\n行潜行攻击可造成2.3\n倍伤害",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    使用近战武器进\n行潜行攻击可造成2.6\n倍伤害",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    使用近战武器进\n行潜行攻击可造成3倍\n伤害",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"轻装",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    减轻手枪25%的重\n量",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    减轻手枪50%的重\n量",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    减轻手枪75%的重\n量",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"秘密特工",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    隐形小子的持续\n时间变为二倍！",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    隐形小子的持续\n时间变为三倍！",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    隐形小子的持续\n时间变为四倍！",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"潜行",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    潜行时被侦测到\n的难度增加25%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    潜行时被侦测到\n的难度增加50%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    潜行时被侦测到\n的难度增加75%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"通径徒步旅行者",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    食物及饮品的重\n量减轻30%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    食物及饮品的重\n量减轻60%",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    食物及饮品的重\n量减轻90%",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"白色骑士",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    你的护甲损坏速\n度降低20%，修复花费\n也更低",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    你的护甲损坏速\n度降低40%，修复花费\n也更低",
		2
	);
	(*this->agility.rbegin())->addLevel(
		L"    你的护甲损坏速\n度降低60%，修复花费\n也更低",
		3
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"弹药匠",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    制作弹药时产量\n增加40%",
		1
	);
	(*this->agility.rbegin())->addLevel(
		L"    制作弹药时产量\n增加80%",
		2
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"逃脱艺术家",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    潜行甩掉敌人，\n跑步不再影响隐身状\n态",
		1
	);
	(*this->agility.rbegin())->finishAddingLevel();

	this->agility.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"轻盈脚步",
		sf::Color::Color(190, 135, 105),
		this->agility.size()
	));
	(*this->agility.rbegin())->addLevel(
		L"    在潜行时，不会\n触发地雷或地面陷阱",
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
		L"暴击强化",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    现在V.A.T.S.暴\n击伤害+50%",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    现在V.A.T.S.暴\n击伤害+75%",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    现在V.A.T.S.暴\n击伤害+100%",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"一团混乱",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    5%的额外伤害意\n味着你的敌人有一定\n的几率会被炸成血淋\n淋的肉泥",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    10%的额外伤害意\n味着你的敌人有一定\n的几率会被炸成血淋\n淋的肉泥",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    15%的额外伤害意\n味着你的敌人有一定\n的几率会被炸成血淋\n淋的肉泥",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"罐头小能手",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    有40%的几率能在\n食品容器中找到额外\n的罐头食品",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    有60%的几率能在\n食品容器中找到额外\n的罐头食品",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    有80%的几率能在\n食品容器中找到额外\n的罐头食品",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"瓶盖收集者",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    你会发现有超过\n33%的瓶盖藏在瓶盖藏\n匿点里",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    你会发现有超过\n66%的瓶盖藏在瓶盖藏\n匿点里",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    你会发现有超过\n100%的瓶盖藏在瓶盖\n藏匿点里",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"经典怪人",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    变异的负面影响\n减少25%",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    变异的负面影响\n减少50%",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    变异的负面影响\n减少75%",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"暴击领悟",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    暴击现在仅消耗\n85%的暴击计",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    暴击现在仅消耗\n70%的暴击计",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    暴击现在仅消耗\n55%的暴击计",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"幸运四叶草",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    在V.A.T.S.中的\n每次攻击命中都有几\n率将你的暴击计充满",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    在V.A.T.S.中的\n每次攻击命中都有较\n高的几率将你的暴击\n计充满",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    在V.A.T.S.中的\n每次攻击命中都有极\n大的几率将你的暴击\n计充满",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"死神的冲刺",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    在V.A.T.S.中的\n每次击杀都有15%的几\n率使行动点数全部恢\n复",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    在V.A.T.S.中的\n每次击杀都有25%的几\n率使行动点数全部恢\n复",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    在V.A.T.S.中的\n每次击杀都有35%的几\n率使行动点数全部恢\n复",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"垃圾盾",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    携带垃圾提升10\n点伤害和能量抗性\n（未装备动力装甲）",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    携带垃圾提升20\n点伤害和能量抗性\n（未装备动力装甲）",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    携带垃圾提升30\n点伤害和能量抗性\n（未装备动力装甲）",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"幸运签",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    攻击敌人时，你\n的武器有很小几率修\n复自身",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    攻击敌人时，你\n的武器有较大几率修\n复自身",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    攻击敌人时，你\n的武器有很大几率修\n复自身",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"时来运转",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    在遭受攻击时，\n装备中的装甲有较小\n几率能修复自身",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    在遭受攻击时，\n装备中的装甲有较大\n几率能修复自身",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    在遭受攻击时，\n装备中的装甲有很大\n几率能修复自身",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"神秘救助者",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    当你倒下时，会\n偶尔有神秘救助者出\n现把你复活",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    当你倒下时，会\n更频繁地有神秘救助\n者出现把你复活",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    当你倒下时，会\n经常有神秘救助者出\n现把你复活",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"神秘客",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    神秘客偶尔会出\n现在V.A.T.S.给予帮\n助",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    神秘客经常会出\n现在V.A.T.S.给予帮\n助",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    神秘客在V.A.T.\nS.中出现了很多次，\n他知道你的名字",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"神秘的肉",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    治疗针可以生成\n可食用肌肉组织，高\n辐射值会提高概率",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    治疗针生成更多\n可食用肌肉组织，高\n辐射值会提高概率",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    治疗针生成大量\n可食用肌肉组织，高\n辐射值会提高概率",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"一枪敌万军",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    重型枪械有4%的\n概率造成失衡，有4%\n的概率造成致残",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    重型枪械有8%的\n概率造成失衡，有8%\n的概率造成致残",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    重型枪械有12%的\n概率造成失衡，有12%\n的概率造成致残",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"制药公司",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    有40%的几率能在\n搜索药物容器时找到\n额外的急救药物",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    有60%的几率能在\n搜索药物容器时找到\n额外的急救药物",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    有80%的几率能在\n搜索药物容器时找到\n额外的急救药物",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"变态杀人狂",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    在V.A.T.S.中，\n每造成一次击杀，有\n5%的几率使你的暴击\n计充满",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    在V.A.T.S.中，\n每造成一次击杀，有\n10%的几率使你的暴击\n计充满",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    在V.A.T.S.中，\n每造成一次击杀，有\n15%的几率使你的暴击\n计充满",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"快手",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    有6%的几率可以\n在弹夹射空时立刻完\n成装填弹夹",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    有12%的几率可以\n在弹夹射空时立刻完\n成装填弹夹",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    有18%的几率可以\n在弹夹射空时立刻完\n成装填弹夹",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"跳弹",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    有6%的几率反射\n敌人的部分远程伤害\n（非PVP）",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    有12%的几率反射\n敌人的部分远程伤害\n（非PVP）",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    有18%的几率反射\n敌人的部分远程伤害\n（非PVP）",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"搜刮者",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    有40%的几率能在\n弹药箱中找到额外的\n弹药",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    有60%的几率能在\n弹药箱中找到额外的\n弹药",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    有80%的几率能在\n弹药箱中找到额外的\n弹药",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"走运",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    生命值低于30%的\n状态下，有15%的几率\n避免受到伤害（未装\n备动力装甲）",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    生命值低于30%的\n状态下，有30%的几率\n避免受到伤害（未装\n备动力装甲）",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    生命值低于30%的\n状态下，有45%的几率\n避免受到伤害（未装\n备动力装甲）",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"超级幸运儿",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    你在制作的时候，\n有10%的几率能制作出\n双份成品！",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    你在制作的时候，\n有20%的几率能制作出\n双份成品！",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    你在制作的时候，\n有30%的几率能制作出\n双份成品！",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"折磨者",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    你的步枪攻击有\n5%几率造成目标肢体\n残废",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    你的步枪攻击有\n10%几率造成目标肢体\n残废",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    你的步枪攻击有\n15%几率造成目标肢体\n残废",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"笑到最后",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    死亡时会从物品\n栏扔出一枚解除保险\n的手雷",
		1
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"盐巴保鲜",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    物品栏里的食物\n腐化速度减缓30%",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    物品栏里的食物\n腐化速度减缓60%",
		2
	);
	(*this->luck.rbegin())->addLevel(
		L"    物品栏里的食物\n腐化速度减缓90%",
		3
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"保姆",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    在复活其他玩家\n时，有50%的几率不消\n耗医疗针",
		1
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"博物馆长",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    娃娃和杂志的增\n益持续时间翻倍",
		1
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"土拨鼠",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    砍伐树木可获得\n两倍木材",
		1
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"追风者",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    在下雨或辐射风\n暴期间获得生命恢复",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    在下雨或辐射风\n暴期间获得高速生命恢复",
		2
	);
	(*this->luck.rbegin())->finishAddingLevel();

	this->luck.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"顽固基因",
		sf::Color::Color(148, 144, 164),
		this->luck.size()
	));
	(*this->luck.rbegin())->addLevel(
		L"    减少从辐射中变\n异的概率，同时也减\n少消辐宁治疗变异的\n概率",
		1
	);
	(*this->luck.rbegin())->addLevel(
		L"    不会从辐射中变\n异，消辐宁也无法治\n愈变异",
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
		L"传奇力量",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    获得1点力量和1\n点力量辅助能力点数。\n辅助能力点数上限为\n15",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得2点力量和2\n点力量辅助能力点数。\n辅助能力点数上限为\n15",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得3点力量和3\n点力量辅助能力点数。\n辅助能力点数上限为\n15",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得5点力量和5\n点力量辅助能力点数。\n辅助能力点数上限为\n15",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"传奇感知",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    获得1点感知和1\n点感知辅助能力点数。\n辅助能力点数上限为\n15",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得2点感知和2\n点感知辅助能力点数。\n辅助能力点数上限为\n15",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得3点感知和3\n点感知辅助能力点数。\n辅助能力点数上限为\n15",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得5点感知和5\n点感知辅助能力点数。\n辅助能力点数上限为\n15",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"传奇耐力",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    获得1点耐力和1\n点耐力辅助能力点数。\n辅助能力点数上限为\n15",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得2点耐力和2\n点耐力辅助能力点数。\n辅助能力点数上限为\n15",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得3点耐力和3\n点耐力辅助能力点数。\n辅助能力点数上限为\n15",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得5点耐力和5\n点耐力辅助能力点数。\n辅助能力点数上限为\n15",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"传奇魅力",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    获得1点魅力和1\n点魅力辅助能力点数。\n辅助能力点数上限为\n15",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得2点魅力和2\n点魅力辅助能力点数。\n辅助能力点数上限为\n15",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得3点魅力和3\n点魅力辅助能力点数。\n辅助能力点数上限为\n15",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得5点魅力和5\n点魅力辅助能力点数。\n辅助能力点数上限为\n15",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"传奇智力",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    获得1点智力和1\n点智力辅助能力点数。\n辅助能力点数上限为\n15",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得2点智力和2\n点智力辅助能力点数。\n辅助能力点数上限为\n15",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得3点智力和3\n点智力辅助能力点数。\n辅助能力点数上限为\n15",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得5点智力和5\n点智力辅助能力点数。\n辅助能力点数上限为\n15",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"传奇敏捷",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    获得1点敏捷和1\n点敏捷辅助能力点数。\n辅助能力点数上限为\n15",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得2点敏捷和2\n点敏捷辅助能力点数。\n辅助能力点数上限为\n15",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得3点敏捷和3\n点敏捷辅助能力点数。\n辅助能力点数上限为\n15",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得5点敏捷和5\n点敏捷辅助能力点数。\n辅助能力点数上限为\n15",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"传奇幸运",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    获得1点幸运和1\n点幸运辅助能力点数。\n辅助能力点数上限为\n15",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得2点幸运和2\n点幸运辅助能力点数。\n辅助能力点数上限为\n15",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得3点幸运和3\n点幸运辅助能力点数。\n辅助能力点数上限为\n15",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    获得5点幸运和5\n点幸运辅助能力点数。\n辅助能力点数上限为\n15",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"动力甲重启",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    身穿动力装甲时\n阵亡，有15％几率自\n动满血复活",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    身穿动力装甲时\n阵亡，有20％几率自\n动满血复活",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    身穿动力装甲时\n阵亡，有30％几率自\n动满血复活",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    身穿动力装甲时\n阵亡，有40％几率自\n动满血复活",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"动力跑者",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    在动力装甲模式\n下，冲刺消耗的行动\n点数减少20%",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    在动力装甲模式\n下，冲刺消耗的行动\n点数减少30%",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    在动力装甲模式\n下，冲刺消耗的行动\n点数减少40%",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    在动力装甲模式\n下，冲刺消耗的行动\n点数减少50%",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"弹药工厂",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    制作弹药时产量\n增加50%",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    制作弹药时产量\n增加75%",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    制作弹药时产量\n增加100%",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    制作弹药时产量\n增加150%",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"暴躁药剂师",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    每小时生成1份战\n斗强化药剂。最多可\n达3份",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    每50分钟生成1份\n战斗强化药剂。最多\n可达4份",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    每40分钟生成1份\n战斗强化药剂。最多\n可达5份",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    每40分钟生成2份\n战斗强化药剂。最多\n可达5份",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"横劈竖砍",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    在V.A.T.S.中，\n近战攻击有20％几率\n造成区域伤害",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    在V.A.T.S.中，\n近战攻击有30％几率\n造成区域伤害",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    在V.A.T.S.中，\n近战攻击有40％几率\n造成区域伤害",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    在V.A.T.S.中，\n近战攻击有50％几率\n造成区域伤害",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"舍己为人",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    当你处于组队状\n态中，且敌人攻击你\n时，他们将承受10%\n的额外伤害",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    当你处于组队状\n态中，且敌人攻击你\n时，他们将承受20%\n的额外伤害",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    当你处于组队状\n态中，且敌人攻击你\n时，他们将承受30%\n的额外伤害",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    当你处于组队状\n态中，且敌人攻击你\n时，他们将承受40%\n的额外伤害",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"汗流浃背",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    当穿戴整套匹配\n的护甲时，+50毒素伤\n害抗性",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    当穿戴整套匹配\n的护甲时，+100毒素\n伤害抗性",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    当穿戴整套匹配\n的护甲时，+150毒素\n伤害抗性",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    当穿戴整套匹配\n的护甲时，+200毒素\n伤害抗性",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"潜行大师",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    自动解锁0级终\n端和锁。开锁和黑客\n技能+3",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    自动解锁1级终\n端和锁。开锁和黑客\n技能+3",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    自动解锁2级终\n端和锁。开锁和黑客\n技能+3",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    自动解锁3级终\n端和锁。开锁和黑客\n技能+3",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"激情四溢",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    当穿戴整套匹配\n的护甲时，+50火焰伤\n害抗性",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    当穿戴整套匹配\n的护甲时，+100火焰\n伤害抗性",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    当穿戴整套匹配\n的护甲时，+150火焰\n伤害抗性",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    当穿戴整套匹配\n的护甲时，+200火焰\n伤害抗性",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"爆炸感染",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    遭投掷爆炸物击\n杀的敌人有20%的几率\n会爆炸",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    遭投掷爆炸物击\n杀的敌人有30%的几率\n会爆炸",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    遭投掷爆炸物击\n杀的敌人有40%的几率\n会爆炸",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    遭投掷爆炸物击\n杀的敌人有50%的几率\n会爆炸",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"爆裂掌",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    徒手时，有5%几\n率可在命中时触发爆\n炸",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    徒手时，有10%几\n率可在命中时触发爆\n炸",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    徒手时，有15%几\n率可在命中时触发爆\n炸",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    徒手时，有20%几\n率可在命中时触发爆\n炸",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"生存捷径",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    每30分钟生成1份\n辅助性求生药物。上\n限为5份",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    每25分钟生成1份\n辅助性求生药物。上\n限为6份",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    每20分钟生成1份\n辅助性求生药物。上\n限为7份",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    每20分钟生成2份\n辅助性求生药物。上\n限为10份",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"电击吸收",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    敌人的能量攻击\n有10%几率为你的动力\n装甲里的聚变核心充\n能",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    敌人的能量攻击\n有13%几率为你的动力\n装甲里的聚变核心充\n能",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    敌人的能量攻击\n有16%几率为你的动力\n装甲里的聚变核心充\n能",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    敌人的能量攻击\n有20%几率为你的动力\n装甲里的聚变核心充\n能",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"血债血偿",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    成功格挡近战攻\n击时回复1点生命值和\n1点行动点数，持续15\n秒",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    成功格挡近战攻\n击时回复2点生命值和\n2点行动点数，持续15\n秒",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    成功格挡近战攻\n击时回复3点生命值和\n3点行动点数，持续15\n秒",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    成功格挡近战攻\n击时回复4点生命值和\n4点行动点数，持续15\n秒",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"血祭",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    你死后，队友将\n获得+25伤害抗性，并\n在8秒内回复40生命\n值",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    你死后，队友将\n获得+30伤害抗性，并\n在10秒内回复50生命\n值",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    你死后，队友将\n获得+35伤害抗性，并\n在12秒内回复60生命\n值",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    你死后，队友将\n获得+40伤害抗性，并\n在14秒内回复70生命\n值",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"辐射为何",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    +50辐射抗性，每\n秒回复1点辐射值",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    +75辐射抗性，每\n秒回复2点辐射值",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    +100辐射抗性，\n每秒回复3点辐射值",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    +300辐射抗性，\n每秒回复6点辐射值",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"遥远烟火",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    遭远程武器击杀\n的敌人有10%几率会爆\n炸",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    遭远程武器击杀\n的敌人有13%几率会爆\n炸",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    遭远程武器击杀\n的敌人有16%几率会爆\n炸",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    遭远程武器击杀\n的敌人有20%几率会爆\n炸",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"附带伤害",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    遭近战武器击杀\n的敌人有10%几率会爆\n炸",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    遭近战武器击杀\n的敌人有13%几率会爆\n炸",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    遭近战武器击杀\n的敌人有16%几率会爆\n炸",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    遭近战武器击杀\n的敌人有20%几率会爆\n炸",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

	this->legend.push_back(new Card(
		0,
		0,
		185.4f,
		300.f,
		this->font,
		L"附骨之疽",
		sf::Color::Color(115, 62, 191),
		this->legend.size()
	));
	(*this->legend.rbegin())->addLevel(
		L"    10秒内，在潜行\n状态下对目标造成的\n远程伤害提升10%",
		1
	);
	(*this->legend.rbegin())->addLevel(
		L"    10秒内，在潜行\n状态下对目标造成的\n远程伤害提升20%",
		2
	);
	(*this->legend.rbegin())->addLevel(
		L"    10秒内，在潜行\n状态下对目标造成的\n远程伤害提升30%",
		3
	);
	(*this->legend.rbegin())->addLevel(
		L"    10秒内，在潜行\n状态下对目标造成的\n远程伤害提升40%",
		4
	);
	(*this->legend.rbegin())->finishAddingLevel();

}