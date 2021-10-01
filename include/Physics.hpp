#pragma once

#include <cstdint>

#include "Point.hpp"
#include "Rect.hpp"

namespace Framework {
	// Intersections

	// Rect and Rect
	template<typename T>
	bool intersects_inclusive(Rect<T> r1, Rect<T> r2);
	template<typename T>
	bool intersects_exclusive(Rect<T> r1, Rect<T> r2);

	// Rect and Point
	template<typename T>
	bool intersects_inclusive(Rect<T> r, Point<T> p);
	template<typename T>
	bool intersects_exclusive(Rect<T> r, Point<T> p);

	// Point and Point can be done with:
	// equals(p1, p2)
}