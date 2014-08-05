#include <iostream>
#include <memory>
#include <functional>
#include <SDL2/SDL.h>
#include <fstream>

#include "src/UI.h"
#include "src/UIComponents.h"
#include "src/components/Button.h"
#include "src/components/TextLabel.h"
#include "src/components/TextBox.h"


using namespace sdl_gui;


typedef std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_ptr;
typedef std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_ptr;

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << "\n";
	}


	window_ptr window{SDL_CreateWindow("A Window",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
			0), SDL_DestroyWindow};

	if (window == nullptr) {
		std::cout << "Failed to create SDL window: " << SDL_GetError() << "\n";
	}

	renderer_ptr renderer{
			SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer};

	if (renderer == nullptr) {
		std::cout << "Failed to create SDL renderer: " << SDL_GetError() << "\n";
	}
	try {
		UI ui{renderer.get()};
		ui.load_window("foobar.xml");
		ui.load_window("bazqux.xml");
		ui.load_window("abcd.xml");
		ui.set_handedness(Handedness::RIGHT);

		ui.register_handler("my_handler", [](UIComponents components, WindowBase *caller){
			std::cout << "button on_click handler was called!\n";
		});

		ui.register_handler("set_label_text", [](UIComponents components, WindowBase *caller) {
			Button *button = dynamic_cast<Button *>(caller);
			if (button) {
				std::string text = button->get_text();
				auto l = components.get_by_name<TextLabel *>("label3");
				if (l) {
					l->set_text(text);
				}

			}
		});


		ui.register_handler("save", [](UIComponents components, WindowBase *caller) {
			auto text_box = components.get_by_name<TextBox *>("my_textbox");
			auto text = text_box->get_text();

			std::ofstream file("saved_text.txt");
			file << text;

		});

		ui.register_handler("load", [](UIComponents components, WindowBase *caller) {

			std::ifstream file("saved_text.txt");
			std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

			auto text_box = components.get_by_name<TextBox *>("my_textbox");
			text_box->set_text(text);

		});


		bool is_running = true;
		while (is_running) {
			SDL_Event event;
			event.type = -1;
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
	} catch (const std::exception &ex) {
		std::cout << "Following exception was thrown: " << ex.what() << "\n";
	}
	SDL_Quit();
	return 0;
}
