#include "Constants.hpp"

namespace WINDOW {
	const Framework::vec2 SIZE = Framework::vec2{ 1024, 768 };
	const Framework::vec2 SIZE_HALF = SIZE / 2;

	const char* TITLE = "Bucket, Inc.";

	const float TARGET_FPS = 60.0f;
	const float TARGET_DT = 1.0f / TARGET_FPS;

	const float MAX_DT = 0.05f;
}

namespace STRINGS {

}

namespace PATHS {
	const uint8_t DEPTH = 4;
	namespace IMAGES {
		const std::string LOCATION = "images/";

		const std::string MAIN_SPRITESHEET = "demo_spritesheet.png";
		const std::string FONT_SPRITESHEET = "font.png";
	}
}

namespace SAVE_DATA {

}

namespace FONTS {
	namespace SIZE {
		const uint8_t MAIN_FONT = 16;
	}

	namespace SCALE {
		const uint8_t MAIN_FONT = 4;
	}

	namespace SPACING {
		const uint8_t MAIN_FONT = 1;
	}
}

namespace COLOURS {
	const Framework::Colour BLACK{ 0x00, 0x00, 0x00 };
	const Framework::Colour WHITE{ 0xFF, 0xFF, 0xFF };
}

namespace TIMINGS {

}

namespace TRANSITIONS {
	const float FADE_TIME = 1.0f;
}

namespace SPRITE {
	const uint8_t SIZE = 16;
	const uint8_t SIZE_HALF = SIZE / 2;
	const uint8_t SCALE = 4;
	const uint8_t UI_SCALE = 4;
	
	namespace INDEX {
	}
}

namespace BUTTONS {
	const uint8_t NONE = 255;
}

namespace GAME {
}