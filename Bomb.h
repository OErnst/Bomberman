#pragma once

#include "Config.h"
#include "GameObjectBase.h"
#include "Player.h"
#include "Playground.h"

class Bomb : public GameObjectBase {
public:
	explicit Bomb(Playground &playground);
	/* < IGameObject > */
	void visit(IObjectVisitor &visitor) override;
	void visit(IConstObjectVisitor &visitor) const override;
	void position(Position const &value) override;
	Position const &position() const override;
	TextureRef const &texture() const override;
	void texture(TextureRef const &texture) override;
	void gameTick() override;
	void setPlayer(Player &player1);
	/* </IGameObject > */
	void setPower(int pow);
	void explosion();

private:
	Playground &playground;
	Position position_{};
	TextureRef texture_;
	Player *player = nullptr;
	int bombTime = Config::bombTime; // z configu
	int power = 1;
};
