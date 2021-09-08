#include "Constants.hpp"

// Constants

namespace SPRITE {
	const uint8_t SCALE = 1;
	
	const uint8_t SIZE = 8;
	const uint8_t SIZE_HALF = SIZE / 2;
}

namespace TEXT {
	const uint8_t SCALE = 2;
	
	const uint8_t SPACE_WIDTH = 1;
	
	const uint8_t FLOAT_PRECISION = 2;
	
}

namespace TILE_ID {
	namespace PLAYER {
		const uint16_t JUMPING = 0;
		const uint16_t RUNNING = 1;
	}

	namespace SOMETHING_ELSE {
		
	}
}

namespace WINDOW {
	const uint16_t WIDTH = 960;
	const uint16_t HEIGHT = 640;

	 const uint16_t SCALED_WIDTH = WIDTH / SPRITE::SCALE;
	 const uint16_t SCALED_HEIGHT = HEIGHT / SPRITE::SCALE;

	 //const uint16_t SCALED_WIDTH_HALF = SCALED_WIDTH / 2;
	 //const uint16_t SCALED_HEIGHT_HALF = SCALED_HEIGHT / 2;

	 //const uint16_t TEXT_SCALED_WIDTH = WIDTH / SPRITE::TEXT_SCALE;
	 //const uint16_t TEXT_SCALED_HEIGHT = HEIGHT / SPRITE::TEXT_SCALE;

	 //const uint16_t TEXT_SCALED_WIDTH_HALF = TEXT_SCALED_WIDTH / 2;
	 //const uint16_t TEXT_SCALED_HEIGHT_HALF = TEXT_SCALED_HEIGHT / 2;

	// const uint8_t FPS = 120;
	// const float MIN_DT = 1.0f / FPS;
}

namespace GAME {
	//const uint8_t LEVEL_COUNT = 0; // This one may need to be declared in Game.cpp instead, if using as an array size

	namespace SCORE {
		
	}

	namespace ENVIRONMENT {
		namespace GRAVITY {
			const float ACCELERATION = 0.0f;
			const float MAX = 0.0f;
		}
	}

	namespace PLAYER {
		const float ACCELERATION = 0.0f;
		const float DECELERATION = 0.0f;
		const float VELOCITY_MAX = 0.0f;

		const float JUMP_STRENGTH = 0.0f;
	}
}

namespace COLOURS {
	const Colour BLACK = Colour(0x00, 0x00, 0x00);
	const Colour WHITE = Colour(0xFF, 0xFF, 0xFF);
}

namespace STRINGS {
	const std::string APP_TITLE = "";

	const std::string ON = "";
	const std::string OFF = "";

	const std::string COLON_SPACE = "";

	namespace MENU {
		namespace TITLE {
			const std::string HEADING = "";

			const std::string OPTION_PLAY = "";
			const std::string OPTION_SETTINGS = "";
			const std::string OPTION_QUIT = "";
		}

		namespace SETTINGS {
			const std::string HEADING = "";

			const std::string OPTION_MUSIC = "";
			const std::string OPTION_SFX = "";
			const std::string OPTION_BACK = "";
		}

		namespace LEVEL_SELECT {
			const std::string HEADING = "";

			const std::string OPTION_BACK = "";
		}

		namespace LEVEL_PAUSED {
			const std::string HEADING = "";

			const std::string OPTION_RESUME = "";
			const std::string OPTION_EXIT = "";
		}

		namespace LEVEL_COMPLETED {
			const std::string HEADING = "";

			const std::string OPTION_CONTINUE = "";
		}
	}
}

namespace FILES {
	const std::string SPRITESHEET = "";

	const std::string FONT_SHEET = "";
}

namespace DELAY {
	const float TRANSITION_FADE_LENGTH = 0.0f;

	const float MENU_INTRO_LENGTH = 0.0f;
	const float MENU_INTRO_FADE_LENGTH = 0.0f;

	const float MENU_BEZIER_LENGTH = 0.0f;
}

// Timer IDs (are set later in program)
namespace TIMER_ID {
	const uint8_t UNINITIALISED = 0;

	uint8_t INTRO_LENGTH = UNINITIALISED;

	uint8_t MENU_TRANSITION_FADE = UNINITIALISED;
	uint8_t MENU_BEZIER_TEXT = UNINITIALISED;
}

// Nodes for bezier transitions
// namespace BEZIER {
	// float bezier_x(std::vector<Node> nodes, float ratio) = 0;
// }