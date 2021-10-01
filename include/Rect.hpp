#pragma once

#include <cstdint>

namespace Framework {
	template<typename T>
	struct Rect {
		T x, y, w, h;
	};

	typedef Rect<int32_t> RectInt;
	typedef Rect<float> RectFloat;

	// Used for equality checking
	template<typename T>
	bool equals(Rect<T> r1, Rect<T> r2);
}