#include "Button.hpp"

namespace Framework {
	Button::Button() {

	}

	Button::Button(Rect rect, ButtonImages images, Text text, uint8_t id) {
		_render_rect = rect;
		_collider_rect = rect;

		_images = images;
		_text = text;
		_id = id;
		// TODO: support different images for hover
	}

	Button::Button(Rect render_rect, Rect collider_rect, ButtonImages images, Text text, uint8_t id) {
		_render_rect = render_rect;
		_collider_rect = collider_rect;

		_initial_position = render_rect.position;

		_images = images;
		_text = text;
		_id = id;
		// TODO: support different images for hover
	}

	Button::ButtonState Button::state() {
		return _state;
	}

	bool Button::pressed() {
		return _state == ButtonState::JUST_PRESSED;
	}

	bool Button::down() {
		return _state == ButtonState::JUST_PRESSED || _state == ButtonState::STILL_DOWN;
	}

	void Button::update(InputHandler* input) {
		if (_state == ButtonState::JUST_PRESSED) {
			_state = ButtonState::STILL_DOWN;
		}
		else if (_state == ButtonState::JUST_RELEASED) {
			_state = ButtonState::STILL_UP;
		}

		// THIS VERSION DOESN'T RELEASE WHEN CURSOR MOVES OFF IT
		/*if (input->just_up(MouseHandler::MouseButton::LEFT)) {
			_state = ButtonState::JUST_RELEASED;
		}
		else if (input->just_down(MouseHandler::MouseButton::LEFT)) {
			if (colliding(_collider_rect, input->mouse_position())) {
				_state = ButtonState::JUST_PRESSED;
			}
		}*/

		// THIS VERSION RELEASES WHEN CURSOR MOVES OFF IT
		if (colliding(_collider_rect, input->get_mouse()->position())) {
			if (input->just_up(MouseHandler::MouseButton::LEFT)) {
				_state = ButtonState::JUST_RELEASED;
			}
			else if (input->just_down(MouseHandler::MouseButton::LEFT)) {
				_state = ButtonState::JUST_PRESSED;
			}
		}
		else if (down()) {
			_state = ButtonState::JUST_RELEASED;
		}
	}

	void Button::render() {
		(down() ? _images.selected : _images.unselected)->render(_render_rect);
		_text.render(_render_rect.centre());
	}

	void Button::set_position(vec2 position) {
		_render_rect.position = position;
	}

	uint8_t Button::get_id() {
		return _id;
	}

	vec2 Button::initial_position() {
		return _initial_position;
	}
}