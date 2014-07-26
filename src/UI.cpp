#include "UI.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>

#include "serialization/XMLSerializer.h"
#include "creation/WindowLoader.h"
#include "creation/TextureFactory.h"
#include "utility/Helpers.h"
#include "ThrowHandlerErrorPolicy.h"
#include "rendering/SDLRenderer.h"

namespace sdl_gui {
UI::UI(SDL_Renderer *renderer) : m_renderer(renderer), m_has_initialized_ttf(false), m_dragging(Drag_Status::NOT_DRAGGING),
		m_window_has_focus(false), m_handler_error_policy{new ThrowHandlerErrorPolicy{}},
		m_factory{new creation::TextureFactory{renderer}} {

	set_handedness(Handedness::RIGHT);

	if (!TTF_WasInit()) {
		if (TTF_Init()) {
			throw std::runtime_error(std::string("Failed to initialize font support: ") + TTF_GetError());
		}
		m_has_initialized_ttf = true;
	}

}

UI::~UI() {
	if (m_has_initialized_ttf) {
		TTF_Quit();
	}
}

void UI::set_handedness(Handedness h) {
	if (h == Handedness::RIGHT) {
		m_mouse_buttons = { SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT, SDL_BUTTON_LMASK, SDL_BUTTON_RMASK };
	} else {
		m_mouse_buttons = { SDL_BUTTON_RIGHT, SDL_BUTTON_LEFT, SDL_BUTTON_RMASK, SDL_BUTTON_LMASK };
	}
}

void UI::set_renderer(SDL_Renderer *renderer) {
	m_renderer = renderer;

	auto renderer_ptr = std::static_pointer_cast<rendering::Renderer>(
			std::make_shared<rendering::SDLRenderer>(renderer)
			);

	for (auto &window : m_windows) {
		window->set_renderer(renderer_ptr);
	}
}

void UI::update(const SDL_Event &event) {
	if (m_windows.empty()) {
		return;
	}

	switch (event.type) {

	case SDL_MOUSEBUTTONDOWN:
		handle_click(event);
		break;
	case SDL_MOUSEBUTTONUP:
		m_dragging = Drag_Status::NOT_DRAGGING;
		handle_click(event);
		break;

	case SDL_MOUSEMOTION:
		handle_motion(event);

		break;

	default:
		break;
	}
}

void UI::draw() {
	for (auto &window : m_windows) {
		window->draw();
	}
}

void UI::load_window(const std::string &file_name) {
	std::shared_ptr<Window> window{new Window{}};
	auto renderer_ptr = initialize_window(window);

	serialization::XMLSerializer serializer{file_name};
	creation::WindowLoader loader{serializer, renderer_ptr, window.get(), m_factory};
	loader.load();

	m_windows.push_back(window);
}

void UI::add_window(std::shared_ptr<Window> window) {
	initialize_window(window);
	m_windows.push_back(window);

}

std::shared_ptr<rendering::Renderer> UI::initialize_window(std::shared_ptr<Window> window) {
	auto renderer_ptr = std::static_pointer_cast<rendering::Renderer>(
				std::make_shared<rendering::SDLRenderer>(m_renderer)
				);
	window->set_renderer(renderer_ptr);
	window->set_handler_manager(this);
	return renderer_ptr;
}

void UI::handle_click(const SDL_Event &event) {

	if (event.button.button == m_mouse_buttons.action_button) {
		if (update_active_window(event.button.x, event.button.y)) {
			if (event.button.state == SDL_RELEASED) {
				m_windows.back()->on_mouse_up(event.button.x, event.button.y);
			} else if (event.button.state == SDL_PRESSED) {
				m_windows.back()->on_mouse_down(event.button.x, event.button.y);
			}
		}
	}
}

void UI::handle_motion(const SDL_Event &event) {
	bool action_button_pressed = event.motion.state & m_mouse_buttons.action_button_mask;

	if ( action_button_pressed && m_dragging == Drag_Status::DRAGGING) {
		m_windows.back()->on_drag(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
	} else if (action_button_pressed && m_dragging == Drag_Status::NOT_DRAGGING) {
		if (update_active_window(event.motion.x, event.motion.y)) {
			m_windows.back()->on_drag(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
			m_dragging = Drag_Status::DRAGGING;
		} else {
			m_dragging = Drag_Status::FAILED_DRAG;
		}
	} else {
		m_windows.back()->on_mouse_over(event.motion.x, event.motion.y);
	}
}

/**
 * Returns true if there was a window under the cursor, false otherwise
 */
bool UI::update_active_window(int x, int y) {

	for (auto iter = m_windows.rbegin(); iter != m_windows.rend(); ++iter) {
		SDL_Rect r = (*iter)->absolute_dimension();
		if (utility::point_inside_rect({x, y}, r)) {

			m_window_has_focus = true;
			auto window = *iter;
			if (iter != m_windows.rbegin()) {
				m_windows.back()->on_losing_focus();
				(*iter)->on_gaining_focus();
			}
			m_windows.erase(--(iter.base()));
			m_windows.push_back(window);

			return true;
		 }
	}

	if (m_window_has_focus == true) {
		m_window_has_focus = false;
		m_windows.back()->on_losing_focus();
	}

	return false;
}

void UI::call_handler(const std::string &handler_name) {
	if (m_handlers.count(handler_name) == 0) {
		m_handler_error_policy->on_missing_handler(handler_name);
		return;
	}

	m_handlers[handler_name]();
}

}
