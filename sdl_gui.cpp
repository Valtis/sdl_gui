#include <iostream>
#include <memory>
#include <functional>
#include <SDL2/SDL.h>

#include "ui/UI.h"
#include "serialization/XMLSerializer.h"
#include "serialization/ParseException.h"

using namespace SDL_GUI;

void event_loop() {
	SDL_Event event;
	while (SDL_WaitEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return;
			break;
		default:
			break;
		}
	}
}

int abc() {
	int a = 5;
	return a;
}

int sdl_testing() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			fprintf(stderr, "Error initializing SDL:  %s\n", SDL_GetError());
			return 1;
	}


	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window(SDL_CreateWindow("A Window",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
			0), SDL_DestroyWindow);

	if (window == nullptr) {
		fprintf(stderr, "Failed creating window:  %s\n", SDL_GetError());
				return 1;
	}

	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer(
			SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);


	UI ui = UI::make_ui(*renderer);




	event_loop();
	SDL_Quit();
	return 0;
}

int main() {

// sdl_testing();

	try {
		auto serializer = std::unique_ptr<Serializer>{new XMLSerializer{"foobar.xml"}};
		auto visitor = [](const Node &node) {
			std::cout << node.name() << "\n";
		};

		serializer->accept(visitor);


	} catch (const std::exception &ex) {
		std::cout << std::string("exception: ") + ex.what() << "\n";
	}


	return 0;
}
