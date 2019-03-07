#include "Bomb.h"
#include "Bonus.h"
#include "BonusItem.h"
#include "Flame.h"
#include "Player.h"
#include "Wall.h"

#include "GameObjectFactory.h"

GameObjectFactory::GameObjectFactory(Playground &playground)
    : playground(playground) {}

std::unique_ptr<Wall> GameObjectFactory::createBrick() const {
	// Brick is a destroyable wall.
	// It can be destroed by an explosion of a bomb.
	auto brick = std::make_unique<Wall>(Wall(playground));
	brick->destroyable(true);

	TextureRef texture{ "brick_gray0.png" };
	brick->texture(texture);
	return brick;
}

std::unique_ptr<Wall> GameObjectFactory::createStone() const {
	// Stone is a non-destroyable wall.
	auto stone = std::make_unique<Wall>(Wall(playground));
	TextureRef texture{ "stone2_gray0.png" };
	stone->texture(texture);
	return stone;
}

std::unique_ptr<Flame> GameObjectFactory::createFlame() const {
	auto flame = std::make_unique<Flame>(Flame(playground));
	TextureRef texture{ "conjure_flame.png" };
	flame->texture(texture);
	return flame;
}

std::unique_ptr<Player> GameObjectFactory::createPlayer() const {
	auto player = std::make_unique<Player>(Player(playground));
	TextureRef texture{ "human.png" };
	player->texture(texture);
	return player;
}

std::unique_ptr<Bomb> GameObjectFactory::createBomb() const {
	auto bomb = std::make_unique<Bomb>(Bomb(playground));
	TextureRef texture{ "delayed_fireball.png" };
	bomb->texture(texture);
	return bomb;
}

std::unique_ptr<BonusItem>
GameObjectFactory::createBonusItem(Bonus bonus) const {
	auto bonusItem = std::make_unique<BonusItem>(BonusItem(playground));
	bonusItem->bonus(bonus);
	TextureRef texture = [&] {
		switch (bonus) {
		case Bonus::Poison:
			return TextureRef{ "potion_bubbly.png" };
		default:
			return TextureRef{ "sticky_flame.png" };
		}
	}();
	bonusItem->texture(texture);

	return bonusItem;
}
