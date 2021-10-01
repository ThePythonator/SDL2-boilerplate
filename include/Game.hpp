#pragma once

#include "BaseGame.hpp"

#include "TitleStage.hpp"

class Game : public Framework::BaseGame {
public:
	Game();

private:
	void start();
	void end();

	//void update(float dt);
	//void render();

	void load_data();
	void clear_data();
};