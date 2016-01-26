#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

#include <iostream>
#include "SDL.h"

int main() {
	
	if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)) {
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		exit(-1);
	}

	
	std::cout << "hello" << std::endl;



	int x; std::cin >> x;

	SDL_Quit();

	return 0;
}