#ifndef WINDOWBASE_H_
#define WINDOWBASE_H_
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <map>
#include "../Typedefs.h"
#include "../rendering/Renderer.h"

namespace sdl_gui {

class HandlerManager;

namespace creation {
	class WindowLoader;
}

enum class Handler_Type { ON_MOUSE_DOWN, ON_CLICK, ON_MOUSE_OVER, ON_DRAG, ON_LOSING_FOCUS, ON_GAINING_FOCUS };

class WindowBase {
public:
	WindowBase();
	virtual ~WindowBase();

	void set_renderer(std::shared_ptr<rendering::Renderer> renderer);

	virtual void draw();


	virtual void on_mouse_down(Sint32 mouse_x, Sint32 mouse_y);
	virtual void on_mouse_up(Sint32 mouse_x, Sint32 mouse_y);
	virtual void on_mouse_over(Sint32 mouse_x, Sint32 mouse_y);
	virtual void on_drag(Sint32 mouse_x, Sint32 mouse_y, Sint32 dx, Sint32 dy);
	virtual void on_losing_focus();
	virtual void on_gaining_focus();

	virtual SDL_Rect relative_dimension() const;
	void set_relative_dimension(SDL_Rect dimension) { m_dimension = dimension; }
	SDL_Rect absolute_dimension() const;

	void add_child(std::unique_ptr<WindowBase> child);
	void set_parent(WindowBase *parent) {
		m_parent = parent;
	}

	void set_handler_manager(HandlerManager *manager) {
		m_handler_manager = manager;
	}

	void set_handler(Handler_Type type, const std::string &handler_name);

	std::string get_name() {
		return m_name;
	}

	WindowBase *get_child_by_name(const std::string &name);

protected:

	void draw(const texture_ptr &ptr);
	SDL_Rect get_draw_area();
	friend class creation::WindowLoader;
	WindowBase *child_under_coordinates(Sint16 x, Sint16 y);
	void do_draw(const texture_ptr &ptr, SDL_Rect destination_rect);
	void call_handler(Handler_Type type);


	std::string m_name;
	SDL_Rect m_dimension;
	SDL_Color m_color;
	texture_ptr m_background;
	WindowBase *m_parent;
	std::shared_ptr<rendering::Renderer> m_renderer;
	HandlerManager *m_handler_manager;

	std::vector<std::unique_ptr<WindowBase>> m_children;
	WindowBase *m_focused_child;
	std::map<Handler_Type, std::string> m_handlers;
};

} /* namespace SDL_GUI */

#endif /* WINDOWBASE_H_ */
