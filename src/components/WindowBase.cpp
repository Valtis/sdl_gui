#include "WindowBase.h"
#include "../utility/Helpers.h"
#include "../HandlerManager.h"
#include "../utility/Helpers.h"
namespace sdl_gui {

WindowBase::WindowBase() : m_dimension{0, 0, 0, 0}, m_color{0, 0, 0, 0},
		m_background{nullptr, SDL_DestroyTexture}, m_parent(nullptr), m_renderer(nullptr),
		m_handler_manager(nullptr), m_focused_child(nullptr), m_hovered_child(nullptr) {

}

WindowBase::~WindowBase() {
	// do not delete any naked pointers here; this class does not own any of these
}

void WindowBase::set_renderer(rendering::Renderer *renderer) {
	 m_renderer = renderer;
	 for (const auto &child : m_children) {
		 child->set_renderer(renderer);
	 }
}


void WindowBase::draw() const {
	draw(m_background);
}

void WindowBase::draw(const texture_ptr &texture) const {
	if (m_renderer == nullptr && texture == nullptr) {
		return;
	}

	do_draw(texture, absolute_dimension());

	for (const auto &child : m_children) {
		child->draw();
	}
}

void WindowBase::do_draw(const texture_ptr &texture, SDL_Rect destination_rect) const {
	SDL_Rect source_rect = {0, 0, relative_dimension().w, relative_dimension().h };
	utility::clip_draw_rectangles(get_draw_area(), source_rect, destination_rect);

	m_renderer->draw(texture, &source_rect, &destination_rect);
}

SDL_Rect WindowBase::get_draw_area() const {
	if (m_parent == nullptr) {
		return absolute_dimension();
	}

	SDL_Rect r;
	SDL_Rect parent_area = m_parent->get_draw_area();
	SDL_Rect own_area = absolute_dimension();
	SDL_IntersectRect(&parent_area, &own_area, &r);
	return r;
}


/**
 * Returns rect where x/y-coordinates are actual screen coordinates
 */
SDL_Rect WindowBase::absolute_dimension() const {
	SDL_Rect r = relative_dimension();

	if (m_parent == nullptr) {
		return r;
	} else {
		SDL_Rect parent_dimension = m_parent->absolute_dimension();
		r.x += parent_dimension.x;
		r.y += parent_dimension.y;
		return r;
	}
}
/**
 * Returns rect where x/y-coordinates are relative to its parents coordinates
 */
SDL_Rect WindowBase::relative_dimension() const {
	return m_dimension;
}


void WindowBase::add_child(std::unique_ptr<WindowBase> child) {
	child->set_parent(this);
	child->set_renderer(m_renderer);
	child->m_handler_manager = m_handler_manager;
	m_children.push_back(std::move(child));
}

void WindowBase::on_mouse_down(Sint32 mouse_x, Sint32 mouse_y) {
	auto child = child_under_coordinates_update_focused(mouse_x, mouse_y);
	if (child != nullptr) {
		child->on_mouse_down(mouse_x, mouse_y);
	} else {
		call_handler(Handler_Type::ON_MOUSE_DOWN);
	}

}

void WindowBase::on_mouse_up(Sint32 mouse_x, Sint32 mouse_y) {
	auto child = child_under_coordinates_update_focused(mouse_x, mouse_y);
	if (child != nullptr) {
		child->on_mouse_up(mouse_x, mouse_y);
	} else {
		call_handler(Handler_Type::ON_CLICK);
	}
}

void WindowBase::on_mouse_over(Sint32 mouse_x, Sint32 mouse_y) {
	auto child = child_under_coordinates_update_hovered(mouse_x, mouse_y);
    if (child != nullptr) {
    	child->on_mouse_over(mouse_x, mouse_y);
	} else {
		call_handler(Handler_Type::ON_MOUSE_OVER);
	}
}

void WindowBase::on_mouse_exit(Sint32 mouse_x, Sint32 mouse_y) {
	auto child = child_under_coordinates(mouse_x, mouse_y);
	if (child != nullptr) {
		child->on_mouse_exit(mouse_x, mouse_y);
	}

	call_handler(Handler_Type::ON_MOUSE_EXIT);

}

void WindowBase::on_drag(Sint32 mouse_x, Sint32 mouse_y, Sint32 dx, Sint32 dy) {
	auto child = child_under_coordinates_update_focused(mouse_x, mouse_y);
	if (child != nullptr) {
		child->on_drag(mouse_x, mouse_y, dx, dy);
	} else {
		call_handler(Handler_Type::ON_DRAG);
	}
}

void WindowBase::on_losing_focus() {
	for (const auto &child : m_children) {
		child->on_losing_focus();
	}
	call_handler(Handler_Type::ON_LOSING_FOCUS);
}

void WindowBase::on_gaining_focus() {
	for (const auto &child : m_children) {
		child->on_gaining_focus();
	}
	call_handler(Handler_Type::ON_GAINING_FOCUS);
}

void WindowBase::on_key_down(SDL_Keycode code) {
	if (m_focused_child) {
		m_focused_child->on_key_down(code);
	} else {
		call_handler(Handler_Type::ON_KEY_DOWN);
	}
}

void WindowBase::on_text_input(std::string text) {
	if (m_focused_child) {
		m_focused_child->on_text_input(text);
	} else {
		call_handler(Handler_Type::ON_TEXT_INPUT);
	}
}

WindowBase *WindowBase::child_under_coordinates_update_focused(Sint32 x, Sint32 y) {
	WindowBase *child = child_under_coordinates(x, y);
	update_child(child, &m_focused_child,
			[](WindowBase *b) { b->on_gaining_focus(); },
			[](WindowBase *b) { b->on_losing_focus(); }
			);
	return child;
}


WindowBase *WindowBase::child_under_coordinates_update_hovered(Sint32 x, Sint32 y) {
	WindowBase *child = child_under_coordinates(x, y);
	update_child(child, &m_hovered_child,
			[=](WindowBase *b) { b->on_mouse_over(x, y); },
			[=](WindowBase *b) { b->on_mouse_exit(x, y); }
			);
	return child;
}

WindowBase *WindowBase::child_under_coordinates(Sint32 x, Sint32 y) {
	for (const auto &child : m_children) {
		if (utility::point_inside_rect({x, y}, child->absolute_dimension())) {
			return child.get();
		}
	}
	return nullptr;
}

void WindowBase::update_child(WindowBase *new_child, WindowBase **current_child,
		std::function<void(WindowBase *)> new_child_func, std::function<void(WindowBase *)> current_child_func) {
	if (*current_child != new_child) {
		if (*current_child != nullptr) {
			current_child_func(*current_child);
		}

		if (new_child != nullptr) {
			new_child_func(new_child);
		}
		*current_child = new_child;
	}
}

void WindowBase::set_handler(Handler_Type type, const std::string &handler_name) {
	if (!handler_name.empty()) {
		m_handlers[type] = handler_name;
	}
}


void WindowBase::call_handler(Handler_Type type) {
	if (m_handlers.count(type) != 0 && m_handler_manager != nullptr) {
		m_handler_manager->call_handler(m_handlers[type], this);
	}
}

WindowBase *WindowBase::get_child_by_name(const std::string &name) const {
	for (const auto &child : m_children) {
		if (child->get_name() == name) {
			return child.get();
		}
	}

	for (const auto &child : m_children) {
		WindowBase *base = child->get_child_by_name(name);
		if (base) {
			return base;
		}
	}

	return nullptr;
}


} /* namespace SDL_GUI */
