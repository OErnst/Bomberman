#include "Wall.h"
#include "BonusItem.h"
Wall::Wall(Playground &playground)
    : playground(playground) {}

void Wall::visit(IObjectVisitor &visitor) { visitor.operator()(*this); }

void Wall::visit(IConstObjectVisitor &visitor) const {
	visitor.operator()(*this);
}

void Wall::position(Position const &value) { position_ = value; }

Position const &Wall::position() const { return position_; }

TextureRef const &Wall::texture() const { return texture_; }

void Wall::texture(TextureRef const &texture) { texture_ = texture; }

void Wall::bonus(Bonus value) { bonus_ = value; }

void Wall::destroyable(bool value) { isDestroyable = value; }

void Wall::destroy() {

	playground.remove(*this);
	if (bonus_ != Bonus::None) {
		std::cout << "wtf\n";
		BonusItem &bonusItem = playground.createBonusItem(bonus_);
		bonusItem.setPosition(position());
		bonusItem.bonus(bonus_);
	}
}
