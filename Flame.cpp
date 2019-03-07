#include "Flame.h"
#include "IObjectVisitor.h"
#include "Visitors.h"

Flame::Flame(Playground &playground)
    : playground(playground) { ; }

void Flame::visit(IObjectVisitor &visitor) { visitor.operator()(*this); }

void Flame::visit(IConstObjectVisitor &visitor) const {
	visitor.operator()(*this);
}

void Flame::position(Position const &value) { position_ = value; }

Position const &Flame::position() const { return position_; }

TextureRef const &Flame::texture() const { return texture_; }

void Flame::texture(TextureRef const &texture) { texture_ = texture; }

void Flame::setPosition(const Position &position) { position_ = position; }

void Flame::gameTick() {
	--flameTime;

	Killer killer;
	playground.visitAll(killer, Playground::Overlapping(position()));

	if (flameTime == 0) {

		playground.remove(*this);
	}
}
