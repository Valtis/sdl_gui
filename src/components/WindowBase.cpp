#include "WindowBase.h"
#include "../utility/Helpers.h"
#include "../HandlerManager.h"
#include "../utility/Helpers.h"
namespace sdl_gui {

WindowBase::WindowBase() : m_dimension{0, 0, 0, 0}, m_color{0, 0, 0, 0},
		m_background{nullptr, SDL_DestroyTexture}, m_parent(nullptr), m_renderer(nullptr),
		m_handler_manager(nullptr), m_focused_child(nullptr) {

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


void WindowBase::draw() {
	draw(m_background);
}

void WindowBase::draw(const texture_ptr &texture) {
	if (m_renderer == nullptr && texture == nullptr) {
		return;
	}

	do_draw(texture, absolute_dimension());

	for (const auto &child : m_children) {
		child->draw();
	}
}

void WindowBase::do_draw(const texture_ptr &texture, SDL_Rect destination_rect) {

	SDL_Rect source_rect = {0, 0, relative_dimension().w, relative_dimension().h };
	utility::clip_draw_rectangles(get_draw_area(), source_rect, destination_rect);

	m_renderer->draw(texture, &source_rect, &destination_rect);
}

SDL_Rect WindowBase::get_draw_area() {
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
	auto child = child_under_coordinates(mouse_x, mouse_y);
	if (child != nullptr) {
		child->on_mouse_down(mouse_x, mouse_y);
	} else {
		call_handler(Handler_Type::ON_MOUSE_DOWN);
	}

}

void WindowBase::on_mouse_up(Sint32 mouse_x, Sint32 mouse_y) {
	auto child = child_under_coordinates(mouse_x, mouse_y);
	if (child != nullptr) {
		child->on_mouse_up(mouse_x, mouse_y);
	} else {
		call_handler(Handler_Type::ON_CLICK);
	}
}

void WindowBase::on_mouse_over(Sint32 mouse_x, Sint32 mouse_y) {
	auto child = child_under_coordinates(mouse_x, mouse_y);
    if (child != nullptr) {
    	child->on_mouse_over(mouse_x, mouse_y);
	} else {
		call_handler(Handler_Type::ON_MOUSE_OVER);
	}
}

void WindowBase::on_drag(Sint32 mouse_x, Sint32 mouse_y, Sint32 dx, Sint32 dy) {
	auto child = child_under_coordinates(mouse_x, mouse_y);
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


WindowBase *WindowBase::child_under_coordinates(Sint16 x, Sint16 y) {
	for (const auto &child : m_children) {
		if (utility::point_inside_rect({x, y}, child->absolute_dimension())) {
			if (m_focused_child != child.get() && m_focused_child != nullptr) {
				m_focused_child->on_losing_focus();
			}
				m_focused_child = child.get();

			return child.get();
		}
	}

	if (m_focused_child != nullptr) {
		m_focused_child->on_losing_focus();
	}
	m_focused_child = nullptr;

	return nullptr;
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

WindowBase *WindowBase::get_child_by_name(const std::string &name) {
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
