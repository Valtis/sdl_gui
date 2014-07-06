#include "UI.h"
#include <SDL2/SDL.h>
#include <algorithm>

#include "../serialization/XMLSerializer.h"
namespace SDL_GUI {
UI::UI(SDL_Renderer &renderer) : m_renderer(renderer), m_dragging(Drag_Status::NOT_DRAGGING) {

}

UI::~UI() {
}

UI UI::make_ui(SDL_Renderer &renderer) {
	return UI{renderer};
}

void UI::update(const SDL_Event &event) {
	switch (event.type) {

	case SDL_MOUSEBUTTONDOWN:

		break;
	case SDL_MOUSEBUTTONUP:
		m_dragging = Drag_Status::NOT_DRAGGING;
		break;


	// for whatever reason, mousemotion struct occasionally contains nonzero relative values even if mouse is not moving
	// which kinda breaks everything. Instead we store the old mouse position and calculate the relative motion that way
	// if this is fixable (e.g. it is because of a bad assumption somewhere), feel free to get rid of the workaround
	case SDL_MOUSEMOTION:
		handle_drag();

		break;

	default:
		break;
	}
	update_mouse_position();
}

void UI::draw() {
	for (auto &window : m_windows) {
		window->draw(&m_renderer);
	}
}

void UI::load_window(const std::string &file_name) {
	std::shared_ptr<Window> window{new Window{}};
	XMLSerializer serializer{file_name};
	window->load(serializer, &m_renderer);
	m_windows.push_back(window);
}


void UI::handle_drag() {
	int x, y;
	auto state = SDL_GetMouseState(&x, &y);

	if ((state & SDL_BUTTON(SDL_BUTTON_LEFT)) && m_dragging != Drag_Status::FAILED_DRAG) {


		if (update_active_window(x, y)) {
			m_windows.back()->on_drag(x, y,
						x - m_old_mouse_position.x, y - m_old_mouse_position.y);

			m_old_mouse_position = { x, y };
			m_dragging = Drag_Status::DRAGGING;
		} else {
			m_dragging = Drag_Status::FAILED_DRAG;
		}
	}
}

/**
 * Returns true if there was a window under the cursor, false otherwise
 */
bool UI::update_active_window(int x, int y) {

	for (auto iter = m_windows.rbegin(); iter != m_windows.rend(); ++iter) {
		SDL_Rect r = (*iter)->dimension();
		if (x > r.x && x < r.x + r.w
				&& y > r.y && y < r.y + r.h) {
			std::iter_swap(iter, (m_windows.end()-1));

			return true;
		 }
	}


	return false;
}


void UI::update_mouse_position() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	m_old_mouse_position = { x, y };
}

}
