#pragma once

namespace Framework {
	enum class KeyState {
		STILL_UP, // Key isn't pressed (has already been up for at least one frame)
		JUST_RELEASED, // Key has just been released
		STILL_DOWN, // Key is pressed (has already been down for at least one frame)
		JUST_PRESSED // Key has been pressed that frame
	};

	// KeyName is used to get the index of a key in KeyUnion by its name
	enum class KeyName {
		UP, DOWN, LEFT, RIGHT,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
		SPACE, RETURN, ESCAPE, BACKSPACE, DELETE,

		KEY_COUNT
	};

	struct Keys {
		KeyState UP, DOWN, LEFT, RIGHT,
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
			SPACE, RETURN, ESCAPE, BACKSPACE, DELETE;
	};

	union KeyUnion {
		Keys keys;
		KeyState key_array[KEY_COUNT];
	};

	bool is_up(KeyState key_state); // Returns true if STILL_UP or JUST_RELEASED
	bool is_down(KeyState key_state); // Returns true if STILL_DOWN or JUST_PRESSED
	bool just_up(KeyState key_state); // Returns true if JUST_RELEASED
	bool just_down(KeyState key_state); // Returns true if JUST_PRESSED

	void update(KeyUnion& key_handler);

	//void update_key(KeyUnion& key_handler, const SDL_Event& sdl_event); // should be handled by input??

	void set_key(KeyUnion& key_handler, KeyName key_name, KeyState key_state);

	// Idea: encapsulate key_handler (KeyUnion instance) in class

	// class Keyboard??

}