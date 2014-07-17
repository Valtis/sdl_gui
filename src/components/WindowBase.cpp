#include "WindowBase.h"
#include "../utility/Helpers.h"
#include "../HandlerManager.h"

namespace sdl_gui {

WindowBase::WindowBase() : m_dimension{0, 0, 0, 0}, m_color{0, 0, 0, 0},
		m_background{nullptr, SDL_DestroyTexture}, m_parent(nullptr), m_renderer(nullptr),
		m_handler_manager(nullptr) {

}

WindowBase::~WindowBase() {
	// do not delete the renderer, parent or HandlerManager; this class does not own these pointers
}

void WindowBase::set_renderer(SDL_Renderer *renderer) {
	 m_renderer = renderer;
	 for (const auto &child : m_children) {
		 child->set_renderer(renderer);
	 }
}


void WindowBase::draw() {
	if (m_renderer == nullptr && m_background == nullptr) {
		return;
	}

	do_draw(absolute_dimension());

	for (const auto &child : m_children) {
		child->draw();
	}
}

void WindowBase::do_draw(SDL_Rect destination_rect) {
	if (m_parent != nullptr) {
		SDL_RenderCopy(m_renderer, m_background.get(), nullptr, &destination_rect);
	} else {
		SDL_RenderCopy(m_renderer, m_background.get(), nullptr, &destination_rect);
	}
}
/**
 * Returns rect where x/y-coordinates are actual screen coordinates
 */
SDL_Rect WindowBase::absolute_dimension() {
	SDL_Rect r = m_dimension;

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
SDL_Rect WindowBase::relative_dimension() {
	return m_dimension;
}


void WindowBase::add_child(std::unique_ptr<WindowBase> child) {
	child->set_parent(this);
	child->set_renderer(m_renderer);
	child->m_handler_manager = m_handler_manager;
	m_children.push_back(std::move(child));
}

void WindowBase::on_click(Sint16 mouse_x, Sint16 mouse_y) {
	auto child = child_under_coordinates(mouse_x, mouse_y);
	if (child != nullptr) {
		child->on_click(mouse_x, mouse_y);
	} else {
		call_handler(HandlerType::ON_CLICK);
	}
}


void WindowBase::on_drag(Sint16 mouse_x, Sint16 mouse_y, Sint16 dx, Sint16 dy) {
	auto child = child_under_coordinates(mouse_x, mouse_y);
	if (child != nullptr) {
		child->on_drag(mouse_x, mouse_y, dx, dy);
	}
}


WindowBase *WindowBase::child_under_coordinates(Sint16 x, Sint16 y) {
	for (const auto &child : m_children) {
		if (utility::point_inside_rect({x, y}, child->relative_dimension())) {
			return child.get();
		}
	}

	return nullptr;
}

void WindowBase::set_handler(HandlerType type, const std::string &handler_name) {
	if (!handler_name.empty()) {
		m_handlers[type] = handler_name;
	}
}


void WindowBase::call_handler(HandlerType type) {
	if (m_handlers.count(type) != 0 && m_handler_manager != nullptr) {
		m_handler_manager->call_handler(m_handlers[type]);
	}
}


} /* namespace SDL_GUI */
