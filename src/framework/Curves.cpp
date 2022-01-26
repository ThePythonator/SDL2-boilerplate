#include "Curves.hpp"

namespace Framework {
	namespace Curves {
		int linear(int start, int end, float t) {
			return static_cast<int>(linear(static_cast<float>(start), static_cast<float>(end), t));
		}

		float linear(float start, float end, float t) {
			return start + t * (end - start);
		}

		vec2 linear(vec2 start, vec2 end, float t) {
			return start + t * (end - start);
		}

		vec2 bezier(std::vector<vec2> control_points, float t) {
			// TODO
			return control_points[0];
		}
	}
}