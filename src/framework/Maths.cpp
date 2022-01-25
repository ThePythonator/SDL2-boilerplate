#include "Maths.hpp"

namespace Framework {
	const float PI = 3.14159265f;
	//const float EPSILON = 0.0001f; // todo: check if reasonable

	float length_squared(vec2 v) {
		return linalg::length2(v);
	}

	vec2 normalise(vec2 v) {
		return linalg::normalize(v);
	}

	float deg_to_rad(float degrees) {
		return PI * degrees / 180.0f;
	}
	float rad_to_deg(float radians) {
		return 180.0f * radians / PI;
	}

	mat22 rotation_matrix(float angle) {
		// Anticlockwise rotation
		float s = std::sin(angle);
		float c = std::cos(angle);
		return mat22{ {c, s}, {-s, c} };
	}

	vec2 perpendicular_acw(vec2 vector) {
		return vec2{ -vector.y, vector.x };
	}

	vec2 perpendicular_cw(vec2 vector) {
		return vec2{ vector.y, -vector.x };
	}
}