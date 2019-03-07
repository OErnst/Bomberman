#include "Player.h"
#include "Bomb.h"
#include "Config.h"
#include "Visitors.h"
#include <iostream>
class Flame;
using namespace std;
Player::Player(Playground &playground1)
    : playground(playground1) { ; }

void Player::visit(IObjectVisitor &visitor) { visitor.operator()(*this); }

void Player::visit(IConstObjectVisitor &visitor) const {
	visitor.operator()(*this);
}

void Player::position(Position const &value) { position_ = value; }

Position const &Player::position() const { return position_; }

TextureRef const &Player::texture() const { return texture_; }

void Player::texture(TextureRef const &texture) { texture_ = texture; }

void Player::move(Direction direction, int ticks) {
	// The function `Vector toVector(Direction direction);`
	// from `Geometry.h` could be helpful.
	vector = toVector(direction);
	tick = ticks;
	moving = true;
	moveSet = true;
}

bool Player::isMoving() const { return moving; }

bool Player::isDead() const { return dead; }

void Player::bomb() {
	IsBomb isBomb;
	playground.visitAll(isBomb, Playground::Overlapping(round(position())));
	if (bombMax > usedBombs && !isBomb.detected) {
		Bomb &bomb = playground.createBomb();
		bomb.position(round(position()));
		bomb.setPlayer(*this);
		bomb.setPower(powerOfBombs);
		usedBombs++;
	}
}

void Player::gameTick() {
	if (lastPoison) {
		if (!moveSet) {
			vector.x = -vector.x;
			vector.y = -vector.y;
		}

		lastPoison = false;
	}
	if (poisonTime > 0 && moveSet) {
		vector.x = -vector.x;
		vector.y = -vector.y;
		moveSet = false;
	}
	if (poisonTime > 0) {
		--poisonTime;
		if (poisonTime == 0) {
			lastPoison = true;
		}
	}
	auto newOne = position_ + vector;
	CollisionDetector cd(newOne, position_);
	playground.visitAll(cd);

	movingPart(cd, newOne);

	if ((cd.isDeadCurrent && position() != newOne) || (cd.isDeadNew && position() == newOne)) {
		dead = true;
		playground.killPlayer(*this);
	}
	if (cd.isBonus && position() == newOne) { // SAME HERE nebo vlastně ne
		if (cd.bonusItem->getBonus() == Bonus::BombRange) {
			++powerOfBombs;
		} else if (cd.bonusItem->getBonus() == Bonus::BombMax) {
			++bombMax;
		} else if (cd.bonusItem->getBonus() == Bonus::Poison) {
			poisonTime = Config::poisonTime;
		}
		playground.removeNow(*cd.bonusItem);
	}
}

void Player::decrementUsedBombs() {
	if (usedBombs > 0) {
		--usedBombs;
	}
}

void Player::movingPart(CollisionDetector &cd, Position newOne) {
	if (isMoving()) {
		if (!cd.canMove && !isCentered(position()) && cd.blockCount == 1) {
			Vector direction = { 0, 0 };
			if (vector.x == 1 || vector.x == -1) {
				direction.x = 0;
				direction.y = position().from.y - cd.blockPosition.from.y;
				direction.y /= direction.y > 0 ? direction.y : -direction.y;
			} else {
				direction.y = 0;
				direction.x = position().from.x - cd.blockPosition.from.x;
				direction.x /= direction.x > 0 ? direction.x : -direction.x;
			}
			newOne = position_ + direction;
			cd.canMove = true;
		}
		if (playground.isValid(newOne) && cd.canMove) {
			position_ = newOne;
		}

		--tick;
		if (tick == 0) {
			moving = false;
		}
	}
}
