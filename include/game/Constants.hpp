#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Colour.hpp"

#include "Maths.hpp"

namespace WINDOW {
	extern const Framework::vec2 SIZE;
	extern const Framework::vec2 SIZE_HALF;
	
	extern const char* TITLE;

	extern const float TARGET_FPS;
	extern const float TARGET_DT;

	extern const float MAX_DT;
}

namespace STRINGS {

}

namespace PATHS {
	extern const uint8_t DEPTH;

	namespace IMAGES {
		extern const std::string LOCATION;

		extern const std::string MAIN_SPRITESHEET;
		extern const std::string FONT_SPRITESHEET;
	}

	namespace SAVE_DATA {
		
	}
}

namespace GRAPHICS_OBJECTS {
	// enum inside its own namespace allows multiple repeated names in the enums, without needing enum class and all the casting
	namespace IMAGES {
		enum IMAGES {
			MAIN_SPRITESHEET,
			FONT_SPRITESHEET,

			TOTAL_IMAGES
		};
	}

	namespace SPRITESHEETS {
		enum SPRITESHEETS {
			MAIN_SPRITESHEET,
			FONT_SPRITESHEET,

			TOTAL_SPRITESHEETS
		};
	}

	namespace FONTS {
		enum FONTS {
			MAIN_FONT,

			TOTAL_FONTS
		};
	}

	namespace TRANSITIONS {
		enum TRANSITIONS {
			FADE_TRANSITION,
			TOTAL_TRANSITIONS
		};
	}
}

namespace FONTS {
	namespace SIZE {
		extern const uint8_t MAIN_FONT;
	}

	namespace SCALE {
		extern const uint8_t MAIN_FONT;
	}

	namespace SPACING {
		extern const uint8_t MAIN_FONT;
	}
}
namespace COLOURS {
	extern const Framework::Colour BLACK;
	extern const Framework::Colour WHITE;
}

namespace TIMINGS {
	
}

namespace TRANSITIONS {
	extern const float FADE_TIME;
}

namespace SPRITE {
	extern const uint8_t SIZE;
	extern const uint8_t SIZE_HALF;
	extern const uint8_t SCALE;
	extern const uint8_t UI_SCALE;

	namespace INDEX {
		
	}
}

namespace CURVES {
	namespace BEZIER {
		
	}
}

namespace BUTTONS {
	extern const uint8_t NONE;

	namespace TITLE {
		enum TITLE {
			PLAY,
			SETTINGS,
			QUIT,

			TOTAL
		};
	}

	namespace PAUSED {
		enum PAUSED {
			RESUME,
			EXIT,

			TOTAL
		};
	}
}

namespace GAME {
	
}