#pragma once

#include <SDL\SDL.h>
#include <iostream>

///-------------------------------------------------------------------------------------------------
/// <summary>A keyboard Singleton class to manage keyboard inputs.</summary>
///-------------------------------------------------------------------------------------------------
class Keyboard {


	private:


	///-------------------------------------------------------------------------------------------------
	/// <summary>Default constructor private due to Singleton.</summary>
	///-------------------------------------------------------------------------------------------------
	Keyboard() {
		keystate = nullptr;
		numberOfKeys = 0;
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>Destructor.</summary>
	///-------------------------------------------------------------------------------------------------
	~Keyboard() {
		// the key state should not be deleted, as SDL takes care of that memory
		delete keystateHold;
		delete keystateDown;
		delete keystateUp;
	};


	public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>Gets the Singleton instance of this keybaord.</summary>
	///
	/// <returns>The Singleton</returns>
	///-------------------------------------------------------------------------------------------------
	static Keyboard& Instance() {
		static Keyboard instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>Deleted due to Singleton.</summary>
	///
	/// <param name="parameter1">The copy constructor parameter.</param>
	///-------------------------------------------------------------------------------------------------
	Keyboard(Keyboard const&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Assignment operator is deleted due to Singleton.</summary>
	///
	/// <param name="parameter1">The assignment operator parameter.</param>
	///-------------------------------------------------------------------------------------------------
	void operator=(Keyboard const&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Initializes the keyboard.</summary>
	///
	/// <param name="currentState">The keybaord state of SDL.</param>
	/// <param name="numberOfKeys">Number of keys on this input.</param>
	///-------------------------------------------------------------------------------------------------
	void Initialise(const Uint8* currentState, unsigned int numberOfKeys) {
		this->keystate = currentState;
		this->numberOfKeys = numberOfKeys;

		keystateHold = new Uint8[numberOfKeys];
		keystateDown = new Uint8[numberOfKeys];
		keystateUp = new Uint8[numberOfKeys];

		memset(keystateHold, 0, numberOfKeys);
		memset(keystateDown, 0, numberOfKeys);
		memset(keystateUp, 0, numberOfKeys);
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>Used to update the keybaord states.
	/// 		 Required side effect is, that the keystate of SDL was updated in the meanwhile.</summary>
	///-------------------------------------------------------------------------------------------------
	void Update() {

		for (unsigned int i = 0; i < numberOfKeys; ++i) {
			// key up:
			// - the current state is NOT active AND it was hold before
			// - OR the current state is NOT active AND it was down before
			keystateUp[i] = (!keystate[i] & keystateHold[i]) | (!keystate[i] & keystateDown[i]);
			// key hold:
			// - hold gets "activated" as soon as: the current key IS active AND was down in the previous frame
			// - hold stays "activated" when: the current state IS active AND it was hold in the previous frame
			// => (the previous frame was EITHER hold OR down) AND now the key IS active
			// (it should never occur that a key is hold and down)
			keystateHold[i] = (keystateDown[i] | keystateHold[i]) & keystate[i];
			// key down:
			// - the previous frame was NOT down
			// - the current state IS active
			// - the current frame is NOT hold (otherwise a long hold will end in a osciallation for the down state)
			keystateDown[i] = !keystateDown[i] & keystate[i] & !keystateHold[i];
		}

	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>Returns whether the given key is either hold or down.</summary>
	///
	/// <param name="key">The SDL keycode.</param>
	///
	/// <returns>True if the given key is either hold or down.</returns>
	///-------------------------------------------------------------------------------------------------
	inline bool GetKeyPressed(SDL_Scancode key) {
		return keystate[key] && ~0;
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>Gets if the given key is hold.</summary>
	///
	/// <param name="key">The SDL keycode.</param>
	///
	/// <returns>True if the given key is at least pressed for two update frames.</returns>
	///-------------------------------------------------------------------------------------------------
	inline bool GetKeyHold(SDL_Scancode key) {
		return keystateHold[key] && ~0;
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>Returns whether the given key is down.</summary>
	///
	/// <param name="key">The SDL keycode.</param>
	///
	/// <returns>True if the given key is down. This will always be true for the maximum of one frame
	/// 	in a row.</returns>
	///-------------------------------------------------------------------------------------------------
	inline bool GetKeyDown(SDL_Scancode key) {
		return keystateDown[key] && ~0;
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>Gets whether the given key is up.</summary>
	///
	/// <param name="key">The SDL keycode.</param>
	///
	/// <returns>True is the given key was released in the previous frame and is now not active any
	/// 	more.</returns>
	///-------------------------------------------------------------------------------------------------
	inline bool GetKeyUp(SDL_Scancode key) {
		return keystateUp[key] && ~0;
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>All key redefinitions from SDL to have them independant in the code from SDL keywords.</summary>
	///-------------------------------------------------------------------------------------------------
	static const SDL_Scancode KEY_0 = SDL_SCANCODE_0;
	static const SDL_Scancode KEY_1 = SDL_SCANCODE_1;
	static const SDL_Scancode KEY_2 = SDL_SCANCODE_2;
	static const SDL_Scancode KEY_3 = SDL_SCANCODE_3;
	static const SDL_Scancode KEY_4 = SDL_SCANCODE_4;
	static const SDL_Scancode KEY_5 = SDL_SCANCODE_5;
	static const SDL_Scancode KEY_6 = SDL_SCANCODE_6;
	static const SDL_Scancode KEY_7 = SDL_SCANCODE_7;
	static const SDL_Scancode KEY_8 = SDL_SCANCODE_8;
	static const SDL_Scancode KEY_9 = SDL_SCANCODE_9;

	static const SDL_Scancode KEY_A = SDL_SCANCODE_A;
	static const SDL_Scancode KEY_B = SDL_SCANCODE_B;
	static const SDL_Scancode KEY_C = SDL_SCANCODE_C;
	static const SDL_Scancode KEY_D = SDL_SCANCODE_D;
	static const SDL_Scancode KEY_E = SDL_SCANCODE_E;
	static const SDL_Scancode KEY_F = SDL_SCANCODE_F;
	static const SDL_Scancode KEY_G = SDL_SCANCODE_G;
	static const SDL_Scancode KEY_H = SDL_SCANCODE_H;
	static const SDL_Scancode KEY_I = SDL_SCANCODE_I;
	static const SDL_Scancode KEY_J = SDL_SCANCODE_J;
	static const SDL_Scancode KEY_K = SDL_SCANCODE_K;
	static const SDL_Scancode KEY_L = SDL_SCANCODE_L;
	static const SDL_Scancode KEY_M = SDL_SCANCODE_M;
	static const SDL_Scancode KEY_N = SDL_SCANCODE_N;
	static const SDL_Scancode KEY_O = SDL_SCANCODE_O;
	static const SDL_Scancode KEY_P = SDL_SCANCODE_P;
	static const SDL_Scancode KEY_Q = SDL_SCANCODE_Q;
	static const SDL_Scancode KEY_R = SDL_SCANCODE_R;
	static const SDL_Scancode KEY_S = SDL_SCANCODE_S;
	static const SDL_Scancode KEY_T = SDL_SCANCODE_T;
	static const SDL_Scancode KEY_U = SDL_SCANCODE_U;
	static const SDL_Scancode KEY_V = SDL_SCANCODE_V;
	static const SDL_Scancode KEY_W = SDL_SCANCODE_W;
	static const SDL_Scancode KEY_X = SDL_SCANCODE_X;
	static const SDL_Scancode KEY_Y = SDL_SCANCODE_Y;
	static const SDL_Scancode KEY_Z = SDL_SCANCODE_Z;


	protected:


	///-------------------------------------------------------------------------------------------------
	/// <summary>The keystate is the pointer to the SDL keyboard states.</summary>
	///-------------------------------------------------------------------------------------------------
	const Uint8* keystate;

	///-------------------------------------------------------------------------------------------------
	/// <summary>The keystate hold contains the keys which are not only down for one frame, but for
	/// 	several frames. After a key was down, but is still pressed on it will be handled as hold.
	/// 	HOLD AND DOWN STATE ARE EITHER OR AND CANNOT OCCUR AT THE SAME TIME!</summary>
	///-------------------------------------------------------------------------------------------------
	Uint8* keystateHold;

	///-------------------------------------------------------------------------------------------------
	/// <summary>The keystate down is always active for only one single frame. It occurs when the key
	/// 	was not pressed before, but is now pressed. As soon at it is pressed for two frames, it
	/// 	will change its state to hold.</summary>
	///-------------------------------------------------------------------------------------------------
	Uint8* keystateDown;

	///-------------------------------------------------------------------------------------------------
	/// <summary>The keystate up contains the key, which were currently released and are now not
	/// 	active any more. This will only be fired for one single frame.</summary>
	///-------------------------------------------------------------------------------------------------
	Uint8* keystateUp;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Number of keys on the input, which is most likly a keyboard.</summary>
	///-------------------------------------------------------------------------------------------------
	unsigned int numberOfKeys;

};