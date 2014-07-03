#include "UI.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "../serialization/XMLSerializer.h"
namespace SDL_GUI {
UI::UI(SDL_Renderer &renderer) : m_renderer(renderer) {

}

UI::~UI() {
}

UI UI::make_ui(SDL_Renderer &renderer) {
	return UI{renderer};
}

void UI::draw() {
	for (auto &window : m_windows) {
		window->draw(&m_renderer);
	}
}

void UI::load_window(const std::string &file_name) {
	try {
		std::shared_ptr<Window> window{new Window{}};
		XMLSerializer serializer{file_name};
		window->load(serializer, &m_renderer);
		m_windows.push_back(std::move(window));

	} catch (const std::exception &ex) {
		std::cout << std::string("exception: ") + ex.what() << "\n";
	}
}

}
