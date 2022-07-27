#include "Title.h"

Title::Title(sf::Font* font) :font{ font }, max_point{ 56 }, total_last_point{ 49 }, height{ 182 } {
	this->initTextures();
	this->initPoint();
	this->initUsedPoint();
	this->initLeastPoint();
	this->initTexts();
}

Title::~Title() {
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
}

void Title::update(sf::Vector2f mousePos) {
	this->updateVectors(mousePos);
	this->updateRemovement();
	this->updateLeastPoint();
	this->updateThumbnailPosition();
	this->updatePoints();
	this->updateTotalLastPoint();
	this->updatePointstoText();
	this->updateHeight();
	this->updateBoolean();
}

void Title::render(sf::RenderTarget& target) {
	this->renderSprites(target);
	this->renderVectors(target);
	this->renderPointTexts(target);
}

void Title::addThumbnail(Perk& perk, int SPECIAL) {
	switch (SPECIAL) {
	case _Strenth: {
		for (size_t i{ 0 }; i < this->strenth.size(); i++) {
			if (this->strenth[i]->getKey() == perk.getKey() && (this->strenth[i]->getCost() >= perk.getCost() || (!(used_point["Strenth"] - this->strenth[i]->getCost() + perk.getCost() > 15) && total_last_point >= (perk.getCost() - this->strenth[i]->getCost())))) {
				this->used_point["Strenth"] -= this->strenth[i]->getCost();
				this->strenth.erase(this->strenth.begin() + i);
			}
		}

		int cost = perk.getCost();
		if (!(cost + used_point["Strenth"] > 15) && !(cost + used_point["Strenth"] - point["Strenth"] > total_last_point)) {
			used_point["Strenth"] += cost;
			this->strenth.push_back(new Thumbnail(perk));
		}

		break;
	}
	case _Perception: {
		for (size_t i{ 0 }; i < this->perception.size(); i++) {
			if (this->perception[i]->getKey() == perk.getKey() && (this->perception[i]->getCost() >= perk.getCost() || (!(used_point["Perception"] - this->perception[i]->getCost() + perk.getCost() > 15) && total_last_point >= (perk.getCost() - this->perception[i]->getCost())))) {
				this->used_point["Perception"] -= this->perception[i]->getCost();
				this->perception.erase(this->perception.begin() + i);
			}
		}

		int cost = perk.getCost();
		if (!(cost + used_point["Perception"] > 15) && !(cost + used_point["Perception"] - point["Perception"] > total_last_point)) {
			used_point["Perception"] += cost;
			this->perception.push_back(new Thumbnail(perk));
		}
		break;
	}
	case _Endurance: {
		for (size_t i{ 0 }; i < this->endurance.size(); i++) {
			if (this->endurance[i]->getKey() == perk.getKey() && (this->endurance[i]->getCost() >= perk.getCost() || (!(used_point["Endurance"] - this->endurance[i]->getCost() + perk.getCost() > 15) && total_last_point >= (perk.getCost() - this->endurance[i]->getCost())))) {
				this->used_point["Endurance"] -= this->endurance[i]->getCost();
				this->endurance.erase(this->endurance.begin() + i);
			}
		}

		int cost = perk.getCost();
		if (!(cost + used_point["Endurance"] > 15) && !(cost + used_point["Endurance"] - point["Endurance"] > total_last_point)) {
			used_point["Endurance"] += cost;
			this->endurance.push_back(new Thumbnail(perk));
		}
		break;
	}
	case _Charisma: {
		for (size_t i{ 0 }; i < this->charisma.size(); i++) {
			if (this->charisma[i]->getKey() == perk.getKey() && (this->charisma[i]->getCost() >= perk.getCost() || (!(used_point["Charisma"] - this->charisma[i]->getCost() + perk.getCost() > 15) && total_last_point >= (perk.getCost() - this->charisma[i]->getCost())))) {
				this->used_point["Charisma"] -= this->charisma[i]->getCost();
				this->charisma.erase(this->charisma.begin() + i);
			}
		}

		int cost = perk.getCost();
		if (!(cost + used_point["Charisma"] > 15) && !(cost + used_point["Charisma"] - point["Charisma"] > total_last_point)) {
			used_point["Charisma"] += cost;
			this->charisma.push_back(new Thumbnail(perk));
		}
		break;
	}
	case _Intelligence: {
		for (size_t i{ 0 }; i < this->intelligence.size(); i++) {
			if (this->intelligence[i]->getKey() == perk.getKey() && (this->intelligence[i]->getCost() >= perk.getCost() || (!(used_point["Intelligence"] - this->intelligence[i]->getCost() + perk.getCost() > 15) && total_last_point >= (perk.getCost() - this->intelligence[i]->getCost())))) {
				this->used_point["Intelligence"] -= this->intelligence[i]->getCost();
				this->intelligence.erase(this->intelligence.begin() + i);
			}
		}

		int cost = perk.getCost();
		if (!(cost + used_point["Intelligence"] > 15) && !(cost + used_point["Intelligence"] - point["Intelligence"] > total_last_point)) {
			used_point["Intelligence"] += cost;
			this->intelligence.push_back(new Thumbnail(perk));
		}
		break;
	}
	case _Agility: {
		for (size_t i{ 0 }; i < this->agility.size(); i++) {
			if (this->agility[i]->getKey() == perk.getKey() && (this->agility[i]->getCost() >= perk.getCost() || (!(used_point["Agility"] - this->agility[i]->getCost() + perk.getCost() > 15) && total_last_point >= (perk.getCost() - this->agility[i]->getCost())))) {
				this->used_point["Agility"] -= this->agility[i]->getCost();
				this->agility.erase(this->agility.begin() + i);
			}
		}

		int cost = perk.getCost();
		if (!(cost + used_point["Agility"] > 15) && !(cost + used_point["Agility"] - point["Agility"] > total_last_point)) {
			used_point["Agility"] += cost;
			this->agility.push_back(new Thumbnail(perk));
		}
		break;
	}
	case _Luck: {
		for (size_t i{ 0 }; i < this->luck.size(); i++) {
			if (this->luck[i]->getKey() == perk.getKey() && (this->luck[i]->getCost() >= perk.getCost() || (!(used_point["Luck"] - this->luck[i]->getCost() + perk.getCost() > 15) && total_last_point >= (perk.getCost() - this->luck[i]->getCost())))) {
				this->used_point["Luck"] -= this->luck[i]->getCost();
				this->luck.erase(this->luck.begin() + i);
			}
		}

		int cost = perk.getCost();
		if (!(cost + used_point["Luck"] > 15) && !(cost + used_point["Luck"] - point["Luck"] > total_last_point)) {
			used_point["Luck"] += cost;
			this->luck.push_back(new Thumbnail(perk));
		}
		break;
	}
	case _Legend: {
		for (size_t i{ 0 }; i < this->legend.size(); i++) {
			if (this->legend[i]->getKey() == perk.getKey()) {
				this->used_point["Legend"]--;
				this->legend.erase(this->legend.begin() + i);
			}
		}
		if (used_point["Legend"] < 6) {
			used_point["Legend"]++;
			this->legend.push_back(new Thumbnail(perk));
		}
		break;
	}
	}
	this->updateTotalLastPoint();
}

void Title::updateVectors(sf::Vector2f& mousePos) {
	for (auto& i : this->strenth) {
		i->update(mousePos);
	}
	for (auto& i : this->perception) {
		i->update(mousePos);
	}
	for (auto& i : this->endurance) {
		i->update(mousePos);
	}
	for (auto& i : this->charisma) {
		i->update(mousePos);
	}
	for (auto& i : this->intelligence) {
		i->update(mousePos);
	}
	for (auto& i : this->agility) {
		i->update(mousePos);
	}
	for (auto& i : this->luck) {
		i->update(mousePos);
	}
	for (auto& i : this->legend) {
		i->update(mousePos);
	}
}

void Title::updateThumbnailPosition() {
	for (size_t i{ 0 }; i < strenth.size(); i++) {
		strenth[i]->setPosition(120 - (strenth[i]->getWidth() / 2), 92 + (strenth[i]->getHeight() * (i + 1)));
	}
	for (size_t i{ 0 }; i < perception.size(); i++) {
		perception[i]->setPosition(360 - (perception[i]->getWidth() / 2), 92 + (perception[i]->getHeight() * (i + 1)));
	}
	for (size_t i{ 0 }; i < endurance.size(); i++) {
		endurance[i]->setPosition(600 - (endurance[i]->getWidth() / 2), 92 + (endurance[i]->getHeight() * (i + 1)));
	}
	for (size_t i{ 0 }; i < charisma.size(); i++) {
		charisma[i]->setPosition(840 - (charisma[i]->getWidth() / 2), 92 + (charisma[i]->getHeight() * (i + 1)));
	}
	for (size_t i{ 0 }; i < intelligence.size(); i++) {
		intelligence[i]->setPosition(1080 - (intelligence[i]->getWidth() / 2), 92 + (intelligence[i]->getHeight() * (i + 1)));
	}
	for (size_t i{ 0 }; i < agility.size(); i++) {
		agility[i]->setPosition(1320 - (agility[i]->getWidth() / 2), 92 + (agility[i]->getHeight() * (i + 1)));
	}
	for (size_t i{ 0 }; i < luck.size(); i++) {
		luck[i]->setPosition(1560 - (luck[i]->getWidth() / 2), 92 + (luck[i]->getHeight() * (i + 1)));
	}
	for (size_t i{ 0 }; i < legend.size(); i++) {
		legend[i]->setPosition(1800 - (legend[i]->getWidth() / 2), 92 + (legend[i]->getHeight() * (i + 1)));
	}
}

void Title::updateRemovement() {
	if (this->readyForPress) {
		for (size_t i{ 0 }; i < strenth.size(); i++) {
			if (strenth[i]->isPressed()) {
				int cost = strenth[i]->getCost();
				if (used_point["Strenth"] - cost < least_point["Strenth"]) {
					used_point["Strenth"] -= cost;
					point["Strenth"] = least_point["Strenth"];
				}
				else {
					used_point["Strenth"] -= cost;
					point["Strenth"] = used_point["Strenth"];
				}
				delete strenth[i];
				strenth.erase(strenth.begin() + i);
			}
		}
		for (size_t i{ 0 }; i < perception.size(); i++) {
			if (perception[i]->isPressed()) {
				int cost = perception[i]->getCost();
				if (used_point["Perception"] - cost < least_point["Perception"]) {
					used_point["Perception"] -= cost;
					point["Perception"] = least_point["Perception"];
				}
				else {
					used_point["Perception"] -= cost;
					point["Perception"] = used_point["Perception"];
				}
				delete perception[i];
				perception.erase(perception.begin() + i);
			}
		}
		for (size_t i{ 0 }; i < endurance.size(); i++) {
			if (endurance[i]->isPressed()) {
				int cost = endurance[i]->getCost();
				if (used_point["Endurance"] - cost < least_point["Endurance"]) {
					used_point["Endurance"] -= cost;
					point["Endurance"] = least_point["Endurance"];
				}
				else {
					used_point["Endurance"] -= cost;
					point["Endurance"] = used_point["Endurance"];
				}
				delete endurance[i];
				endurance.erase(endurance.begin() + i);
			}
		}
		for (size_t i{ 0 }; i < charisma.size(); i++) {
			if (charisma[i]->isPressed()) {
				int cost = charisma[i]->getCost();
				if (used_point["Charisma"] - cost < least_point["Charisma"]) {
					used_point["Charisma"] -= cost;
					point["Charisma"] = least_point["Charisma"];
				}
				else {
					used_point["Charisma"] -= cost;
					point["Charisma"] = used_point["Charisma"];
				}
				delete charisma[i];
				charisma.erase(charisma.begin() + i);
			}
		}
		for (size_t i{ 0 }; i < intelligence.size(); i++) {
			if (intelligence[i]->isPressed()) {
				int cost = intelligence[i]->getCost();
				if (used_point["Intelligence"] - cost < least_point["Intelligence"]) {
					used_point["Intelligence"] -= cost;
					point["Intelligence"] = least_point["Intelligence"];
				}
				else {
					used_point["Intelligence"] -= cost;
					point["Intelligence"] = used_point["Intelligence"];
				}
				delete intelligence[i];
				intelligence.erase(intelligence.begin() + i);
			}
		}
		for (size_t i{ 0 }; i < agility.size(); i++) {
			if (agility[i]->isPressed()) {
				int cost = agility[i]->getCost();
				if (used_point["Agility"] - cost < least_point["Agility"]) {
					used_point["Agility"] -= cost;
					point["Agility"] = least_point["Agility"];
				}
				else {
					used_point["Agility"] -= cost;
					point["Agility"] = used_point["Agility"];
				}
				delete agility[i];
				agility.erase(agility.begin() + i);
			}
		}
		for (size_t i{ 0 }; i < luck.size(); i++) {
			if (luck[i]->isPressed()) {
				int cost = luck[i]->getCost();
				if (used_point["Luck"] - cost < least_point["Luck"]) {
					used_point["Luck"] -= cost;
					point["Luck"] = least_point["Luck"];
				}
				else {
					used_point["Luck"] -= cost;
					point["Luck"] = used_point["Luck"];
				}
				delete luck[i];
				luck.erase(luck.begin() + i);
			}
		}
		for (size_t i{ 0 }; i < legend.size(); i++) {
			if (legend[i]->isPressed()) {
				used_point["Legend"]--;
				delete legend[i];
				legend.erase(legend.begin() + i);
			}
		}
	}
}

void Title::updatePoints() {
	for (auto& i : point) {
		if (least_point.at(i.first) > used_point.at(i.first)) {
			i.second = least_point.at(i.first);
		}
		else i.second = used_point.at(i.first);
	}
}

void Title::updateTotalLastPoint() {
	this->total_last_point = this->max_point -
		point["Strenth"] -
		point["Perception"] -
		point["Endurance"] -
		point["Charisma"] -
		point["Intelligence"] -
		point["Agility"] -
		point["Luck"];
}

void Title::updateLeastPoint() {
	this->max_point = 56;
	this->least_point["Strenth"] = 1;
	this->least_point["Perception"] = 1;
	this->least_point["Endurance"] = 1;
	this->least_point["Charisma"] = 1;
	this->least_point["Intelligence"] = 1;
	this->least_point["Agility"] = 1;
	this->least_point["Luck"] = 1;

	for (auto& i : this->legend) {
		if (i->getKey() == 0) {
			switch (i->getCost()) {
			case 4:
				this->max_point += 5;
				this->least_point["Strenth"] += 5;
				break;
			default:
				this->max_point += i->getCost();
				this->least_point["Strenth"] += i->getCost();
				break;
			}
		}
		if (i->getKey() == 1) {
			switch (i->getCost()) {
			case 4:
				this->max_point += 5;
				this->least_point["Perception"] += 5;
				break;
			default:
				this->max_point += i->getCost();
				this->least_point["Perception"] += i->getCost();
				break;
			}
		}
		if (i->getKey() == 2) {
			switch (i->getCost()) {
			case 4:
				this->max_point += 5;
				this->least_point["Endurance"] += 5;
				break;
			default:
				this->max_point += i->getCost();
				this->least_point["Endurance"] += i->getCost();
				break;
			}
		}
		if (i->getKey() == 3) {
			switch (i->getCost()) {
			case 4:
				this->max_point += 5;
				this->least_point["Charisma"] += 5;
				break;
			default:
				this->max_point += i->getCost();
				this->least_point["Charisma"] += i->getCost();
				break;
			}
		}
		if (i->getKey() == 4) {
			switch (i->getCost()) {
			case 4:
				this->max_point += 5;
				this->least_point["Intelligence"] += 5;
				break;
			default:
				this->max_point += i->getCost();
				this->least_point["Intelligence"] += i->getCost();
				break;
			}
		}
		if (i->getKey() == 5) {
			switch (i->getCost()) {
			case 4:
				this->max_point += 5;
				this->least_point["Agility"] += 5;
				break;
			default:
				this->max_point += i->getCost();
				this->least_point["Agility"] += i->getCost();
				break;
			}
		}
		if (i->getKey() == 6) {
			switch (i->getCost()) {
			case 4:
				this->max_point += 5;
				this->least_point["Luck"] += 5;
				break;
			default:
				this->max_point += i->getCost();
				this->least_point["Luck"] += i->getCost();
				break;
			}
		}
	}
}

void Title::updatePointstoText() {

	texts["Strenth"].setString(std::to_string(point["Strenth"]));
	
	texts["Perception"].setString(std::to_string(point["Perception"]));

	texts["Endurance"].setString(std::to_string(point["Endurance"]));

	texts["Charisma"].setString(std::to_string(point["Charisma"]));
	
	texts["Intelligence"].setString(std::to_string(point["Intelligence"]));
	
	texts["Agility"].setString(std::to_string(point["Agility"]));

	texts["Luck"].setString(std::to_string(point["Luck"]));
	
	texts["Legend"].setString(std::to_string(point["Legend"]));

	total_last_point_text2.setString(std::to_string(total_last_point));
}

void Title::updateHeight() {
	size_t max{ 0 };
	int longest_class{ _Strenth };
	if (max < strenth.size()) {
		max = strenth.size();
		longest_class = _Strenth;
	}
	if (max < perception.size()) {
		max = perception.size();
		longest_class = _Perception;
	}
	if (max < endurance.size()) {
		max = endurance.size();
		longest_class = _Endurance;
	}
	if (max < charisma.size()) {
		max = charisma.size();
		longest_class = _Charisma;
	}
	if (max < intelligence.size()) {
		max = intelligence.size();
		longest_class = _Intelligence;
	}
	if (max < agility.size()) {
		max = agility.size();
		longest_class = _Agility;
	}
	if (max < luck.size()) {
		max = luck.size();
		longest_class = _Luck;
	}
	if (max < legend.size()) {
		max = legend.size();
		longest_class = _Legend;
	}
	if (max == 0) {
		this->height = 120.f;
	}
	else {
		switch (longest_class) {
		case _Strenth: {
			this->height = (*strenth.rbegin())->getPosition().y + (*strenth.rbegin())->getHeight();
			break;
		}
		case _Perception: {
			this->height = (*perception.rbegin())->getPosition().y + (*perception.rbegin())->getHeight();
			break;
		}
		case _Endurance: {
			this->height = (*endurance.rbegin())->getPosition().y + (*endurance.rbegin())->getHeight();
			break;
		}
		case _Charisma: {
			this->height = (*charisma.rbegin())->getPosition().y + (*charisma.rbegin())->getHeight();
			break;
		}
		case _Intelligence: {
			this->height = (*intelligence.rbegin())->getPosition().y + (*intelligence.rbegin())->getHeight();
			break;
		}
		case _Agility: {
			this->height = (*agility.rbegin())->getPosition().y + (*agility.rbegin())->getHeight();
			break;
		}
		case _Luck: {
			this->height = (*luck.rbegin())->getPosition().y + (*luck.rbegin())->getHeight();
			break;
		}
		case _Legend: {
			this->height = (*legend.rbegin())->getPosition().y + (*legend.rbegin())->getHeight();
			break;
		}
		}
	}

	this->height += 5.f;
}

void Title::updateBoolean() {
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->readyForPress = true;
	else this->readyForPress = false;
}

void Title::renderSprites(sf::RenderTarget& target) {
	for (auto& i : this->sprites) {
		target.draw(i.second);
	}
}

void Title::renderVectors(sf::RenderTarget& target) {
	for (auto& i : this->strenth) {
		i->render(target);
	}
	for (auto& i : this->perception) {
		i->render(target);
	}
	for (auto& i : this->endurance) {
		i->render(target);
	}
	for (auto& i : this->charisma) {
		i->render(target);
	}
	for (auto& i : this->intelligence) {
		i->render(target);
	}
	for (auto& i : this->agility) {
		i->render(target);
	}
	for (auto& i : this->luck) {
		i->render(target);
	}
	for (auto& i : this->legend) {
		i->render(target);
	}
}

void Title::renderPointTexts(sf::RenderTarget& target) {
	for (auto& i : texts) {
		target.draw(i.second);
	}
	target.draw(total_last_point_text1);
	target.draw(total_last_point_text2);
}

void Title::initTextures() {

	textures["Strenth"].loadFromFile("Recources\\S.png");
	sprites["Strenth"].setTexture(textures.at("Strenth"));
	sprites["Strenth"].setTextureRect(sf::IntRect(0, 0, 151, 72));
	sprites["Strenth"].setPosition(44.5, 20);

	textures["Perception"].loadFromFile("Recources\\P.png");
	sprites["Perception"].setTexture(textures.at("Perception"));
	sprites["Perception"].setTextureRect(sf::IntRect(0, 0, 151, 72));
	sprites["Perception"].setPosition(284.5, 20);


	textures["Endurance"].loadFromFile("Recources\\E.png");
	sprites["Endurance"].setTexture(textures.at("Endurance"));
	sprites["Endurance"].setTextureRect(sf::IntRect(0, 0, 151, 72));
	sprites["Endurance"].setPosition(524.5, 20);


	textures["Charisma"].loadFromFile("Recources\\C.png");
	sprites["Charisma"].setTexture(textures.at("Charisma"));
	sprites["Charisma"].setTextureRect(sf::IntRect(0, 0, 151, 72));
	sprites["Charisma"].setPosition(764.5, 20);


	textures["Intelligence"].loadFromFile("Recources\\I.png");
	sprites["Intelligence"].setTexture(textures.at("Intelligence"));
	sprites["Intelligence"].setTextureRect(sf::IntRect(0, 0, 151, 72));
	sprites["Intelligence"].setPosition(1004.5, 20);


	textures["Agility"].loadFromFile("Recources\\A.png");
	sprites["Agility"].setTexture(textures.at("Agility"));
	sprites["Agility"].setTextureRect(sf::IntRect(0, 0, 151, 72));
	sprites["Agility"].setPosition(1244.5, 20);


	textures["Luck"].loadFromFile("Recources\\L.png");
	sprites["Luck"].setTexture(textures.at("Luck"));
	sprites["Luck"].setTextureRect(sf::IntRect(0, 0, 151, 72));
	sprites["Luck"].setPosition(1484.5, 20);


	textures["Legend"].loadFromFile("Recources\\Legend.png");
	sprites["Legend"].setTexture(textures.at("Legend"));
	sprites["Legend"].setTextureRect(sf::IntRect(0, 0, 72, 72));
	sprites["Legend"].setPosition(1764, 25);

}

void Title::initPoint() {
	point["Strenth"] = 1;
	point["Perception"] = 1;
	point["Endurance"] = 1;
	point["Charisma"] = 1;
	point["Intelligence"] = 1;
	point["Agility"] = 1;
	point["Luck"] = 1;
	point["Legend"] = 6;
}

void Title::initUsedPoint() {
	used_point["Strenth"] = 0;
	used_point["Perception"] = 0;
	used_point["Endurance"] = 0;
	used_point["Charisma"] = 0;
	used_point["Intelligence"] = 0;
	used_point["Agility"] = 0;
	used_point["Luck"] = 0;
	used_point["Legend"] = 0;
}

void Title::initLeastPoint() {
	this->least_point["Strenth"] = 1;
	this->least_point["Perception"] = 1;
	this->least_point["Endurance"] = 1;
	this->least_point["Charisma"] = 1;
	this->least_point["Intelligence"] = 1;
	this->least_point["Agility"] = 1;
	this->least_point["Luck"] = 1;
	this->least_point["Legend"] = 6;
}

void Title::initTexts() {
	texts["Strenth"].setFont(*this->font);
	texts["Strenth"].setString(std::to_string(point["Strenth"]));
	texts["Strenth"].setCharacterSize(20);
	texts["Strenth"].setFillColor(sf::Color::Black);
	texts["Strenth"].setPosition(
		120 - texts["Strenth"].getGlobalBounds().width / 2,
		95
	);

	texts["Perception"].setFont(*this->font);
	texts["Perception"].setString(std::to_string(point["Perception"]));
	texts["Perception"].setCharacterSize(20);
	texts["Perception"].setFillColor(sf::Color::Black);
	texts["Perception"].setPosition(
		360 - texts["Perception"].getGlobalBounds().width / 2,
		95
	);

	texts["Endurance"].setFont(*this->font);
	texts["Endurance"].setString(std::to_string(point["Endurance"]));
	texts["Endurance"].setCharacterSize(20);
	texts["Endurance"].setFillColor(sf::Color::Black);
	texts["Endurance"].setPosition(
		600 - texts["Endurance"].getGlobalBounds().width / 2,
		95
	);

	texts["Charisma"].setFont(*this->font);
	texts["Charisma"].setString(std::to_string(point["Charisma"]));
	texts["Charisma"].setCharacterSize(20);
	texts["Charisma"].setFillColor(sf::Color::Black);
	texts["Charisma"].setPosition(
		840 - texts["Charisma"].getGlobalBounds().width / 2,
		95
	);

	texts["Intelligence"].setFont(*this->font);
	texts["Intelligence"].setString(std::to_string(point["Intelligence"]));
	texts["Intelligence"].setCharacterSize(20);
	texts["Intelligence"].setFillColor(sf::Color::Black);
	texts["Intelligence"].setPosition(
		1080 - texts["Intelligence"].getGlobalBounds().width / 2,
		95
	);

	texts["Agility"].setFont(*this->font);
	texts["Agility"].setString(std::to_string(point["Agility"]));
	texts["Agility"].setCharacterSize(20);
	texts["Agility"].setFillColor(sf::Color::Black);
	texts["Agility"].setPosition(
		1320 - texts["Agility"].getGlobalBounds().width / 2,
		95
	);

	texts["Luck"].setFont(*this->font);
	texts["Luck"].setString(std::to_string(point["Luck"]));
	texts["Luck"].setCharacterSize(20);
	texts["Luck"].setFillColor(sf::Color::Black);
	texts["Luck"].setPosition(
		1560 - texts["Luck"].getGlobalBounds().width / 2,
		95
	);

	texts["Legend"].setFont(*this->font);
	texts["Legend"].setString(std::to_string(point["Legend"]));
	texts["Legend"].setCharacterSize(20);
	texts["Legend"].setFillColor(sf::Color::Black);
	texts["Legend"].setPosition(
		1800 - texts["Legend"].getGlobalBounds().width / 2,
		95
	);

	total_last_point_text1.setFont(*this->font);
	total_last_point_text1.setString(L"剩余属性点：");
	total_last_point_text1.setCharacterSize(20);
	total_last_point_text1.setFillColor(sf::Color::Black);
	total_last_point_text1.setPosition(
		960 - total_last_point_text1.getGlobalBounds().width / 2,
		0
	);

	total_last_point_text2.setFont(*this->font);
	total_last_point_text2.setString(std::to_string(total_last_point));
	total_last_point_text2.setCharacterSize(20);
	total_last_point_text2.setFillColor(sf::Color::Black);
	total_last_point_text2.setPosition(
		total_last_point_text1.getPosition().x + total_last_point_text1.getGlobalBounds().width,
		0
	);
}

float Title::getHeight() {
	return height;
}

sf::Sprite* Title::getIcon(const std::string& name) {
	return &sprites.at(name);
}