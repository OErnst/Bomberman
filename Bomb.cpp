#include "Bomb.h"
#include "Flame.h"
#include "Geometry.h"
#include "ObjectVisitorSkeleton.h"
#include "Visitors.h"
#include <vector>

Bomb::Bomb(Playground &playground)
    : playground(playground) {}

void Bomb::visit(IObjectVisitor &visitor) { visitor.operator()(*this); }

void Bomb::visit(IConstObjectVisitor &visitor) const {
	visitor.operator()(*this);
}

void Bomb::position(Position const &value) { position_ = value; }

Position const &Bomb::position() const { return position_; }

TextureRef const &Bomb::texture() const { return texture_; }

void Bomb::texture(TextureRef const &texture) { texture_ = texture; }

void Bomb::gameTick() {
	--bombTime;
	if (bombTime == 0) {

		explosion();
	}
}

void Bomb::setPlayer(Player &player1) { player = &player1; }

void Bomb::setPower(int pow) { power = pow; }

void Bomb::explosion() {
	if (player != nullptr) {
		player->decrementUsedBombs();
	}
	std::vector<Vector> vector = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
	Flame &flame1 = playground.createFlame();
	flame1.setPosition(position_);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < power; ++j) {
			const Position &position = next(position_, vector[i], j + 1);
			DamageDetection dd(position);
			playground.visitAll(dd);
			if (!dd.isWall && !dd.isBrick && playground.isValid(position)) {
				Flame &flame = playground.createFlame();
				flame.setPosition(position);
			} else {
				break;
			}
		}
	}
	playground.remove(*this);
}
