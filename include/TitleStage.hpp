#pragma once

#include "BaseStage.hpp"

class TitleStage : public Framework::BaseStage {
public:
	TitleStage();

	void update(float dt);
	void render();//Graphics graphics??
};