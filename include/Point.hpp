#pragma once

#include <cstdint>

namespace Framework {
	template<typename T>
	struct Point {
		T x, y;
	};

	typedef Point<int32_t> PointInt;
	typedef Point<float> PointFloat;

	// Used for equality checking
	template<typename T>
	bool equals(Point<T> p1, Point<T> p2);
}