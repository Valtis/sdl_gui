#include <iostream>
#include <memory>
#include <functional>
#include <SDL2/SDL.h>

#include "ui/UI.h"
#include "ui/Window.h"
#include "serialization/XMLSerializer.h"


using namespace sdl_gui;


typedef std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_ptr;
typedef std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_ptr;

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			throw std::runtime_error(SDL_GetError());
	}


	window_ptr window{SDL_CreateWindow("A Window",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
			0), SDL_DestroyWindow};

	if (window == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}

	renderer_ptr renderer{
			SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer};

	if (renderer == nullptr) {
		throw std::runtime_error(SDL_GetError());
	}

	UI ui = UI::make_ui(*renderer);
	ui.load_window("foobar.xml");
	ui.load_window("bazqux.xml");
	ui.set_handedness(Handedness::RIGHT);

	SDL_Event event;
	bool is_running = true;
	while (is_running) {
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				is_running = false;
				break;
			default:
				break;
			}
		}


		SDL_SetRenderDrawColor(renderer.get(), 150, 150, 255, 255);
		SDL_RenderClear(renderer.get());

		ui.update(event);
		ui.draw();
		SDL_RenderPresent(renderer.get());
	}

	SDL_Quit();
	return 0;
}
