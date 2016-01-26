
#include "SDL.h"

class Window {

	public:

	Window(int width = 0, int height = 0) {
		this->window = nullptr;
		this->mouseFocus = false;
		this->keyboardFocus = false;
		this->fullScreen = false;
		this->minimized = false;
		this->initialized = false;
		this->width = width;
		this->height = height;

		initalize();
	}

	~Window() {
		SDL_GL_DeleteContext(windowContext);
		SDL_DestroyWindow(window);
	}

	const SDL_GLContext& getContext() {
		return windowContext;
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>Swaps the buffers of this window.</summary>
	///-------------------------------------------------------------------------------------------------
	void SwapBuffers() {
		SDL_GL_SwapWindow(window);
	}

	bool isInitialized() {
		return initialized;
	}

	private:

	///-------------------------------------------------------------------------------------------------
	/// <summary>Initalizes the window with all attributes.
	/// 		 Sets the initializes variable to the state of the window
	/// 		 initialization.</summary>
	///-------------------------------------------------------------------------------------------------
	void initalize() {

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

		/* Turn on double buffering with a 24bit Z buffer.
		* You may need to change this to 16 or 32 for your system */
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // maybe higher depth buffer
		
		/* This makes our buffer swap syncronized with the monitor's vertical refresh */
		SDL_GL_SetSwapInterval(1);

		window = SDL_CreateWindow("SDL Tutorial",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

		if (window != NULL) {
			mouseFocus = true;
			keyboardFocus = true;
			windowContext = SDL_GL_CreateContext(window);
		}

		initialized = window != NULL;
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>The OpenGL context handle.</summary>
	///-------------------------------------------------------------------------------------------------
	SDL_GLContext windowContext;

	///-------------------------------------------------------------------------------------------------
	/// <summary>The window.</summary>
	///-------------------------------------------------------------------------------------------------
	SDL_Window* window;

	int width;

	int height;

	bool mouseFocus;

	bool keyboardFocus;

	bool fullScreen;

	bool minimized;

	bool initialized;

};