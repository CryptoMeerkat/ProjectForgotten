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
		delete keystate;
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
	/// <summary>Gets a key state of the given key.</summary>
	///
	/// <param name="key">The SDL keycode.</param>
	///
	/// <returns>True if the key is currently down OR hold. This state is also called pressed.</returns>
	///-------------------------------------------------------------------------------------------------
	inline bool GetKey(SDL_Scancode key) {
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