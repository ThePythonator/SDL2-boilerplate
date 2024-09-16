#pragma once

#include "BaseStage.hpp"
#include "Font.hpp"
#include "Timer.hpp"

#include "Constants.hpp"

#include "GameStages.hpp"

class IntroStage : public Framework::BaseStage {
public:
	void start();

	bool update(float dt);
	void render();

private:
	Framework::Timer intro_timer;
	Framework::Text intro_text;
};

class TitleStage : public Framework::BaseStage {
public:
	void start();

	bool update(float dt);
	void render();

private:
	Framework::Timer _timer;
};
