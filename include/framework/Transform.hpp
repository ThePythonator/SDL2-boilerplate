#pragma once

#include "Maths.hpp"

namespace Framework {
	enum class SpriteTransform {
		NONE,

		FLIP_HORIZONTAL,
		FLIP_VERTICAL,

		SWAP_XY,

		ROTATE_90_ACW,
		ROTATE_180_ACW,
		ROTATE_270_ACW,

		ROTATE_90_CW = ROTATE_270_ACW,
		ROTATE_180_CW = ROTATE_180_ACW,
		ROTATE_270_CW = ROTATE_90_ACW,

		ROTATE_180 = ROTATE_180_ACW
	};

	ImageFlip transform_to_imageflip(SpriteTransform transform);
	float transform_to_angle(SpriteTransform transform);
}