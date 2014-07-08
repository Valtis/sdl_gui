#include "UI.h"
#include <SDL2/SDL.h>
#include <algorithm>

#include "../serialization/XMLSerializer.h"
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

void UI::handle_click(const SDL_Event &event) {

	if (event.button.button == m_mouse_buttons.action_button) {
		if (update_active_window(event.button.x, event.button.y)) {
			SDL_Rect r = m_windows.back()->dimension();
			m_windows.back()->on_click(relative_x(event.button.x, r),
					relative_y(event.button.y, r));
		}
	}
}

void UI::handle_drag() {
	int x, y;
	auto state = SDL_GetMouseState(&x, &y);

	if ((state & SDL_BUTTON(m_mouse_buttons.action_button)) && m_dragging != Drag_Status::FAILED_DRAG) {


		if (update_active_window(x, y)) {
			SDL_Rect r = m_windows.back()->dimension();
			m_windows.back()->on_drag(relative_x(x,r), relative_y(y, r),
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
