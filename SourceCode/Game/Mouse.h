#pragma once

#include <SDL/SDL.h>
#include <glm/vec2.hpp>
#include <iostream>


//TO-DO: check https://wiki.libsdl.org/SDL_SetRelativeMouseMode
class Mouse {
	


	private:


	///-------------------------------------------------------------------------------------------------
	/// <summary>Default constructor private due to Singleton.</summary>
	///-------------------------------------------------------------------------------------------------
	Mouse() {
		//A memset might be useful here instead
		for (int i = 0; i < Button::MAX; ++i) {
			buttonState[i] = false;
			buttonHoldState[i] = false;
			buttonClickState[i] = false;
		}

	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>Destructor.</summary>
	///-------------------------------------------------------------------------------------------------
	~Mouse() {
	};


	public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>Gets the Singleton instance of this keybaord.</summary>
	///
	/// <returns>The Singleton</returns>
	///-------------------------------------------------------------------------------------------------
	static Mouse& Instance() {
		static Mouse instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>Deleted due to Singleton.</summary>
	///
	/// <param name="parameter1">The copy constructor parameter.</param>
	///-------------------------------------------------------------------------------------------------
	Mouse(Mouse const&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Assignment operator is deleted due to Singleton.</summary>
	///
	/// <param name="parameter1">The assignment operator parameter.</param>
	///-------------------------------------------------------------------------------------------------
	void operator=(Mouse const&) = delete;

	public:

	enum Button {
		LEFT, RIGHT, MIDDLE, MAX
	};

	inline bool ButtonDown(Button b) {
		return buttonState[b];
	}

	inline bool ButtonHold(Button b) {
		return buttonHoldState[b];
	}

	inline bool ButtonClicked(Button b) {
		return buttonClickState[b];
	}

	inline void SetAbsolutePosition(glm::vec2 pos) {
		absolutePosition = pos;
	}

	inline glm::vec2 GetAbsolutePosition() const {
		return absolutePosition;
	}

	inline glm::vec2 GetRelativePosition() const {
		return relativePosition;
	}

	inline void Clear() {
		relativePosition = glm::vec2();

		//TO-DO: A memcpy might be useful in this case
		for (int i = 0; i < Button::MAX; ++i) {
			buttonHoldState[i] = buttonState[i];
			//buttonClickState[i] = false;
		}
	}

	void Mouse::Update(float deltaTime) //int currentX, int currentY, int deltaX, int deltaY)
	{
		int absoluteX, absoluteY;
		Uint32 currentAbsoluteState = SDL_GetMouseState(&absoluteX, &absoluteY);

		int relativeX, relativeY;
		Uint32 currentRelativeState = SDL_GetRelativeMouseState(&relativeX, &relativeY);

		/*std::cout << "Delta: " << Vector2(relativeX, relativeY) << std::endl;
		std::cout << "Absolute: " << Vector2(absoluteX, absoluteY) << std::endl << std::endl << std::endl;*/
		//std::cout << "Absolute: " << Vector2(absoluteX, absoluteY) << std::endl << std::endl << std::endl;

		buttonState[Button::LEFT] = currentAbsoluteState & SDL_BUTTON(SDL_BUTTON_LEFT);
		buttonState[Button::RIGHT] = currentAbsoluteState & SDL_BUTTON(SDL_BUTTON_RIGHT);
		buttonState[Button::MIDDLE] = currentAbsoluteState & SDL_BUTTON(SDL_BUTTON_MIDDLE);

		for (int i = 0; i < Button::MAX; ++i) {
			buttonHoldState[i] &= buttonState[i];
			buttonClickState[i] = buttonState[i] & !buttonHoldState[i];
		}

		//std::cout << "Left state: " << buttonState[Button::LEFT] << std::endl;
		//std::cout << "Left hold state: " << buttonHoldState[Button::LEFT] << std::endl;

		relativePosition.x = relativeX; // -absolutePosition.x;
		relativePosition.y = relativeY; // -absolutePosition.y;
		relativePosition *= sensitivity;

		absolutePosition.x = absoluteX;
		absolutePosition.y = absoluteY;

		//std::cout << "Delta: " << relativePosition << std::endl;

		/*absolutePosition.x = currentX;
		absolutePosition.y = currentY;
		relativePosition.x = deltaX;
		relativePosition.y = deltaY;*/

		/*absolutePosition.x = std::fmaxf(absolutePosition.x, 0.0f);
		absolutePosition.x = std::fminf(absolutePosition.x, Symphony::Screen::Width());
		absolutePosition.y = std::fmaxf(absolutePosition.y, 0.0f);
		absolutePosition.y = std::fminf(absolutePosition.y, Symphony::Screen::Height());*/

		//std::cout << relativePosition << std::endl;

		/*relativePosition.x = (currentX - absolutePosition.x) * sensitivity;
		relativePosition.y = (currentY - absolutePosition.y) * sensitivity;
		absolutePosition += relativePosition;*/
	}


	protected:
	//Current mouse absolute position
	glm::vec2 absolutePosition, relativePosition;

	bool buttonState[Button::MAX];
	bool buttonHoldState[Button::MAX];
	bool buttonClickState[Button::MAX];

	float sensitivity = 0.005f; //0.25f

};