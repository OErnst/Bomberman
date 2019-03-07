#pragma once

// A collection of useful visitors.
#include "Bomb.h"
#include "BonusItem.h"
#include "Config.h"
#include "Flame.h"
#include "ObjectVisitorSkeleton.h"
#include "Player.h"
#include "Wall.h"

struct DeadPlayerDetector : ConstObjectVisitorSkeleton {
	bool detected = false;
	void operator()(Player const &player) override {
		detected = detected || player.isDead();
	}
};

struct IsBomb : ConstObjectVisitorSkeleton {
	bool detected = false;
	void operator()(Bomb const & /*bomb*/) override { detected = true; };
};

struct Killer : public IObjectVisitor {

	void operator()(Bomb &bomb) override { bomb.explosion(); }

	void operator()(Flame & /*flame*/) override { ; }

	void operator()(Player & /*player*/) override { ; }

	void operator()(BonusItem &bonusItem) override { bonusItem.destroy(); }

	void operator()(Wall & /*wall*/) override { ; }
};

struct DamageDetection : public IObjectVisitor {
	Position position = {};
	bool isWall = false;
	bool isBrick = false;
	explicit DamageDetection(const Position &position)
	    : position(position) {}

	void operator()(Bomb & /*bomb*/) override { ; }

	void operator()(Flame & /*flame*/) override { ; }

	void operator()(Player & /*player*/) override { ; }

	void operator()(BonusItem &bonusItem) override {
		if (bonusItem.position() != position) {
			return;
		}
		bonusItem.destroy();
	}

	void operator()(Wall &wall) override {
		if (wall.position() != position) {
			return;
		}
		if (wall.isBrick()) {
			isBrick = true;
			wall.destroy();
		} else {
			isWall = true;
		}
	}
};

struct CollisionDetector : public IObjectVisitor {
	bool isBonus = false;
	BonusItem *bonusItem = nullptr;
	bool canMove = true;
	Position &player1;
	Position &current;
	Position blockPosition = {};
	bool isDeadNew = false;
	bool isDeadCurrent = false;
	int blockCount = 0;
	CollisionDetector(Position &player, Position &current)
	    : player1(player)
	    , current(current) {}

	void operator()(Bomb &bomb) override {
		if (overlap(bomb.position(), current)) {
			return;
		}
		if (overlap(bomb.position(), player1)) {
			canMove = false;
			blockPosition = bomb.position();
			blockCount++;
		}
	}

	void operator()(Flame &flame) override {
		if (overlap(flame.position(), player1)) {
			isDeadNew = true;
		}
		if (overlap(flame.position(), current)) {
			isDeadCurrent = true;
		}
	}

	void operator()(Player & /*player*/) override { ; }

	void operator()(BonusItem &bonusItem) override {
		if (overlap(bonusItem.position(), player1)) {
			this->bonusItem = &bonusItem;
			isBonus = true;
		}
	}

	void operator()(Wall &wall) override {
		if (overlap(wall.position(), player1)) {
			canMove = false;
			blockPosition = wall.position();
			blockCount++;
		}
	}
};
