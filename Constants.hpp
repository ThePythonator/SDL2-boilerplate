#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "Colour.hpp"
#include "Bezier.hpp"
#include "Entity.hpp"

// Constants

namespace SPRITE {
	extern const uint8_t SCALE;
	
	extern const uint8_t SIZE;
	extern const uint8_t SIZE_HALF;
}

namespace TEXT {
	extern const uint8_t SCALE;
	
	extern const uint8_t SPACE_WIDTH;
	
	extern const uint8_t FLOAT_PRECISION;
	
}

namespace TILE_ID {
	namespace PLAYER {
		extern const uint16_t JUMPING;
		extern const uint16_t RUNNING;
	}

	namespace SOMETHING_ELSE {
		
	}
}

namespace WINDOW {
	extern const uint16_t WIDTH;
	extern const uint16_t HEIGHT;

	// extern const uint16_t SCALED_WIDTH;
	// extern const uint16_t SCALED_HEIGHT;

	// extern const uint16_t SCALED_WIDTH_HALF;
	// extern const uint16_t SCALED_HEIGHT_HALF;

	// extern const uint16_t TEXT_SCALED_WIDTH;
	// extern const uint16_t TEXT_SCALED_HEIGHT;

	// extern const uint16_t TEXT_SCALED_WIDTH_HALF;
	// extern const uint16_t TEXT_SCALED_HEIGHT_HALF;

	// extern const uint8_t FPS;
	// extern const float MIN_DT = 1.0f / FPS;
}

namespace GAME {
	//extern const uint8_t LEVEL_COUNT; // This one may need to be declared in Game.cpp instead, if using as an array size

	namespace SCORE {
		
	}

	namespace ENVIRONMENT {
		namespace GRAVITY {
			extern const float ACCELERATION;
			extern const float MAX;
		}
	}

	namespace PLAYER {
		extern const float ACCELERATION;
		extern const float DECELERATION;
		extern const float VELOCITY_MAX;

		extern const float JUMP_STRENGTH;
	}
}

namespace COLOURS {
	extern const Colour BLACK;
	extern const Colour WHITE;
}

namespace STRINGS {
	extern const std::string APP_TITLE;

	extern const std::string ON;
	extern const std::string OFF;

	extern const std::string COLON_SPACE;

	namespace MENU {
		namespace TITLE {
			extern const std::string HEADING;

			extern const std::string OPTION_PLAY;
			extern const std::string OPTION_SETTINGS;
			extern const std::string OPTION_QUIT;
		}

		namespace SETTINGS {
			extern const std::string HEADING;

			extern const std::string OPTION_MUSIC;
			extern const std::string OPTION_SFX;
			extern const std::string OPTION_BACK;
		}

		namespace LEVEL_SELECT {
			extern const std::string HEADING;

			extern const std::string OPTION_BACK;
		}

		namespace LEVEL_PAUSED {
			extern const std::string HEADING;

			extern const std::string OPTION_RESUME;
			extern const std::string OPTION_EXIT;
		}

		namespace LEVEL_COMPLETED {
			extern const std::string HEADING;

			extern const std::string OPTION_CONTINUE;
		}
	}
}

namespace FILES {
	extern const std::string SPRITESHEET;

	extern const std::string FONT_SHEET;
}

namespace DELAY {
	extern const float TRANSITION_FADE_LENGTH;

	extern const float MENU_INTRO_LENGTH;
	extern const float MENU_INTRO_FADE_LENGTH;

	extern const float MENU_BEZIER_LENGTH;
}

// Timer IDs (are set later in program)
namespace TIMER_ID {
	extern const uint8_t UNINITIALISED;

	extern uint8_t INTRO_LENGTH;

	extern uint8_t MENU_TRANSITION_FADE;
	extern uint8_t MENU_BEZIER_TEXT;
}

// Nodes for bezier transitions
// namespace BEZIER {
	// float bezier_x(std::vector<Node> nodes, float ratio);
// }