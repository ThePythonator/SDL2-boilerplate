#pragma once

#include "BaseStage.hpp"

#include "Constants.hpp"

#include "GameStages.hpp"

class TitleStage : public Framework::BaseStage {
public:
	void start();

	bool update(float dt);
	void render();

private:
	Framework::Timer _timer;
};
