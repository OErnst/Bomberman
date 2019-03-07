#pragma once

#include "Bonus.h"
#include "GameObjectBase.h"
#include "IObjectVisitor.h"
#include "Playground.h"

enum class Bonus;

// (brick, wood, stone, ...)
class Wall : public GameObjectBase {
public:
	explicit Wall(Playground &playground);

	/* < IGameObject > */
	void visit(IObjectVisitor &visitor) override;
	void visit(IConstObjectVisitor &visitor) const override;
	void position(Position const &value) override;
	Position const &position() const override;
	TextureRef const &texture() const override;
	void texture(TextureRef const &texture) override;
	/* </IGameObject > */

	/**
   * @brief Sets the kind of bonus which drops from the wall when destroyed.
   */
	void bonus(Bonus value);

	/**
   * @brief Sets whether the wall is destroyable or not.
   */
	void destroy();
	void destroyable(bool value);
	bool isBrick() const { return isDestroyable; };

private:
	Bonus bonus_ = Bonus::None;
	Position position_{};
	TextureRef texture_;
	bool isDestroyable = false;
	Playground &playground;
};
