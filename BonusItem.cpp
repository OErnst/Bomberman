#include "BonusItem.h"
#include "IObjectVisitor.h"

BonusItem::BonusItem(Playground &playground)
    : playground(playground) { ; }

void BonusItem::visit(IObjectVisitor &visitor) { visitor.operator()(*this); }

void BonusItem::visit(IConstObjectVisitor &visitor) const {
	visitor.operator()(*this);
}

void BonusItem::position(Position const &value) { position_ = value; }

Position const &BonusItem::position() const { return position_; }

TextureRef const &BonusItem::texture() const { return texture_; }

void BonusItem::texture(TextureRef const &texture) { texture_ = texture; }

void BonusItem::bonus(Bonus value) { bonus_ = value; }

void BonusItem::destroy() { playground.remove(*this); }

void BonusItem::setPosition(const Position &position1) {
	position_ = position1;
}

Bonus BonusItem::getBonus() { return bonus_; }
