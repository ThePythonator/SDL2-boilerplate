#include "Graphics.hpp"

namespace Framework {
	Graphics::Graphics() {

	}

	void Graphics::fill(const Colour& colour) {
		set_colour(colour);
		// RenderClear doesn't do alpha
		//SDL_RenderClear(renderer);

		// So we draw a rectangle over the window instead
		SDL_RenderFillRect(renderer, NULL);
	}

	void Graphics::fill(const Colour& colour, uint8_t alpha) {
		fill(Colour(colour, alpha));
	}

	void Graphics::render_line(const vec2& start, const vec2& end, const Colour& colour) {
		set_colour(colour);
		SDL_RenderDrawLine(renderer, static_cast<int>(start.x), static_cast<int>(start.y), static_cast<int>(end.x), static_cast<int>(end.y));
	}

	void Graphics::render_poly(const std::vector<vec2> points, const Colour& colour) {
		for (uint16_t i = 0; i < points.size(); i++) {
			// Get next index (for end point)
			uint8_t next_i = i + 1 < points.size() ? i + 1 : 0;

			render_line(points[i], points[next_i], colour);
		}
	}

	void Graphics::render_poly(const std::vector<vec2> points, const vec2& offset, const Colour& colour) {
		for (uint16_t i = 0; i < points.size(); i++) {
			// Get next index (for end point)
			uint8_t next_i = i + 1 < points.size() ? i + 1 : 0;

			render_line(points[i] + offset, points[next_i] + offset, colour);
		}
	}

	void Graphics::render_rect(const Rect& rect, const Colour& colour) {
		render_poly({rect.topleft(), rect.topright(), rect.bottomright(), rect.bottomleft()}, colour);
	}

	void Graphics::render_circle(const vec2& centre, float radius, const Colour& colour) {
		set_colour(colour);
		SDLUtils::SDL_RenderDrawCircle(renderer, static_cast<int>(centre.x), static_cast<int>(centre.y), static_cast<int>(radius));
	}

	void Graphics::set_renderer(SDL_Renderer* _renderer) {
		renderer = _renderer;
	}

	SDL_Renderer* Graphics::get_renderer() {
		return renderer;
	}

	void Graphics::set_colour(const Colour& colour) {
		SDLUtils::SDL_SetRenderDrawColor(renderer, colour);
	}
}