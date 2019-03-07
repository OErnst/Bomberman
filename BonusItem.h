#pragma once
#include "Bonus.h"
#include "GameObjectBase.h"
#include "Playground.h"
enum class Bonus;

class BonusItem : public GameObjectBase {
public:
	BonusItem(Playground &);
	void destroy();
	/* < IGameObject > */
	void visit(IObjectVisitor &visitor) override;
	void visit(IConstObjectVisitor &visitor) const override;
	void position(Position const &value) override;
	Position const &position() const override;
	TextureRef const &texture() const override;
	void texture(TextureRef const &texture) override;
	/* </IGameObject > */

	/**
   * @brief Sets the kind of bonus.
   */
	void bonus(Bonus value);
	void setPosition(const Position &position1);
	Bonus getBonus();

private:
	Position position_{};
	TextureRef texture_;
	Bonus bonus_ = Bonus::None;
	Playground &playground;
};
