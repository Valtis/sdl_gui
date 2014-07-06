#include "UI.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "../serialization/XMLSerializer.h"
namespace SDL_GUI {
UI::UI(SDL_Renderer &renderer) : m_renderer(renderer), m_button_down(false) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	m_old_mouse_position = {x, y };
}

UI::~UI() {
}

UI UI::make_ui(SDL_Renderer &renderer) {
	return UI{renderer};
}

void UI::update(const SDL_Event &event) {
	switch (event.type) {

	case SDL_MOUSEBUTTONDOWN:
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			m_old_mouse_position = { x, y };
		}
		m_button_down = true;
		break;
	case SDL_MOUSEBUTTONUP:
		m_button_down = false;
		break;


	// for whatever reason, mousemotion struct occasionally contains nonzero relative values even if mouse is not moving
	// which kinda breaks everything. Instead we store the old mouse position and calculate the relative motion that way
	// if this is fixable (e.g. it is because of a bad assumption somewhere), feel free to get rid of the workaround
	case SDL_MOUSEMOTION:

		if (m_button_down) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			m_windows.back()->on_drag(x, y,
					x - m_old_mouse_position.x, y - m_old_mouse_position.y);
			m_old_mouse_position = { x, y };
		}


		break;

	default:
		break;
	}
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
		m_windows.push_back(window);

	} catch (const std::exception &ex) {
		std::cout << std::string("exception: ") + ex.what() << "\n";
	}
}

}
