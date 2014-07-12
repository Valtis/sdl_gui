#include "UI.h"
#include <SDL2/SDL.h>
#include <algorithm>

#include "../serialization/XMLSerializer.h"
#include "utility/Helpers.h"

namespace sdl_gui {
UI::UI(SDL_Renderer &renderer) : m_renderer(renderer), m_dragging(Drag_Status::NOT_DRAGGING) {
	set_handedness(Handedness::RIGHT);
}

UI::~UI() {
}

UI UI::make_ui(SDL_Renderer &renderer) {
	return UI{renderer};
}

void UI::set_handedness(Handedness h) {
	if (h == Handedness::RIGHT) {
		m_mouse_buttons = { SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT };
	} else {
		m_mouse_buttons = { SDL_BUTTON_RIGHT, SDL_BUTTON_LEFT };
	}
}

void UI::update(const SDL_Event &event) {
	switch (event.type) {

	case SDL_MOUSEBUTTONDOWN:

		break;
	case SDL_MOUSEBUTTONUP:
		m_dragging = Drag_Status::NOT_DRAGGING;
		handle_click(event);
		break;

	case SDL_MOUSEMOTION:
		handle_drag(event);

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
	std::shared_ptr<Window> window{new Window{}};
	XMLSerializer serializer{file_name};
	window->load(serializer, &m_renderer);
	m_windows.push_back(window);
}

void UI::handle_click(const SDL_Event &event) {

	if (event.button.button == m_mouse_buttons.action_button) {
		if (update_active_window(event.button.x, event.button.y)) {
			SDL_Rect r = m_windows.back()->dimension();
			m_windows.back()->on_click(relative_x(event.button.x, r),
					relative_y(event.button.y, r));
		}
	}
}

void UI::handle_drag(const SDL_Event &event) {
	auto state = SDL_GetMouseState(nullptr, nullptr);

	if ((state & SDL_BUTTON(m_mouse_buttons.action_button)) && m_dragging != Drag_Status::FAILED_DRAG) {
		if (update_active_window(event.motion.x, event.motion.y)) {
			m_windows.back()->on_drag(event.motion.x, event.motion.yrel, event.motion.xrel, event.motion.yrel);
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
		if (utility::point_inside_rect({x, y}, r)) {
			auto window = *iter;
			m_windows.erase(--(iter.base()));
			m_windows.push_back(window);

			return true;
		 }
	}


	return false;
}

}
