#pragma once

#include <SDL\SDL.h>
#include <iostream>

class Keyboard {

	private:

		Keyboard() {
			keystate = nullptr;
			numberOfKeys = 0;
		}

		~Keyboard() {
		};

	public:

	static Keyboard& Instance() {
		static Keyboard instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	// Singleton
	Keyboard(Keyboard const&) = delete;
	void operator=(Keyboard const&) = delete;

	void Initialise(const Uint8* currentState, unsigned int numberOfKeys) {
		this->keystate = currentState;
		this->numberOfKeys = numberOfKeys;

		keystateHold = new Uint8[numberOfKeys];
		keystatePressed = new Uint8[numberOfKeys];
		keystateLifted = new Uint8[numberOfKeys];

		memset(keystateHold, 0, numberOfKeys);
		memset(keystatePressed, 0, numberOfKeys);
		memset(keystateLifted, 0, numberOfKeys);
	}

	void Update() {
		for (unsigned int i = 0; i < numberOfKeys; ++i) {
			keystateLifted[i] = !keystate[i] & keystateHold[i];
			keystateHold[i] &= keystate[i];
			keystatePressed[i] = keystate[i] & !keystateHold[i];
		}
	}

	inline void Clear() {
		for (unsigned int i = 0; i < numberOfKeys; ++i) {
			keystateHold[i] = keystate[i];
		}
	}

	//TO-DO: Could this be optimised and not be O(N)?
	inline bool AnyKey() {
		for (unsigned int i = 0; i < numberOfKeys; ++i) {
			if (keystateHold[i])
				return true;
		}
		return false;
	}

	inline bool GetKey(SDL_Scancode key) {
		return keystate[key] && ~0;
	}

	inline bool GetKeyHold(SDL_Scancode key) {
		return keystate[key] && ~0;
	}

	inline bool GetKeyDown(SDL_Scancode key) {
		return keystatePressed[key] && ~0;
	}

	inline bool GetKeyUp(SDL_Scancode key) {
		return keystateLifted[key] && ~0;
	}

	protected:
	const Uint8* keystate;
	Uint8* keystateHold;
	Uint8* keystatePressed;
	Uint8* keystateLifted;
	unsigned int numberOfKeys;
};