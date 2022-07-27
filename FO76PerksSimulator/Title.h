#ifndef TITLE_H
#define TITLE_H

#include"Thumbnail.h"

enum _SPECIAL{
	_Strenth = 0,
	_Perception,
	_Endurance,
	_Charisma,
	_Intelligence,
	_Agility,
	_Luck,
	_Legend
};

class Title {
public:

	Title(sf::Font* font);
	~Title();

	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget& target);

	void addThumbnail(Perk& perk, int SPECIAL);

	void updateVectors(sf::Vector2f& mousePos);
	void updateThumbnailPosition();
	void updateRemovement();
	void updatePoints();
	void updateTotalLastPoint();
	void updateLeastPoint();
	void updatePointstoText();
	void updateHeight();
	void updateBoolean();

	void renderSprites(sf::RenderTarget& target);
	void renderVectors(sf::RenderTarget& target);
	void renderPointTexts(sf::RenderTarget& target);

	void initTextures();
	void initPoint();
	void initUsedPoint();
	void initLeastPoint();
	void initTexts();

	float getHeight();
	sf::Sprite* getIcon(const std::string& name);

private:

	float height;

	std::map<std::string, sf::Texture>textures;
	std::map<std::string, sf::Sprite>sprites;

	int max_point;
	int total_last_point;
	std::map<std::string, int>point;
	std::map<std::string, int>used_point;
	std::map<std::string, int>least_point;

	std::map<std::string, sf::Text>texts;

	std::vector<Thumbnail*>strenth;
	std::vector<Thumbnail*>perception;
	std::vector<Thumbnail*>endurance;
	std::vector<Thumbnail*>charisma;
	std::vector<Thumbnail*>intelligence;
	std::vector<Thumbnail*>agility;
	std::vector<Thumbnail*>luck;
	std::vector<Thumbnail*>legend;

	sf::Text total_last_point_text1;
	sf::Text total_last_point_text2;

	sf::Font* font;
	bool readyForPress;
};

#endif