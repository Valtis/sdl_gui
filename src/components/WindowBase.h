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

enum class Handler_Type { ON_MOUSE_DOWN, ON_CLICK, ON_MOUSE_OVER, ON_MOUSE_EXIT, ON_DRAG, ON_LOSING_FOCUS, ON_GAINING_FOCUS, ON_KEY_DOWN, ON_KEY_UP, ON_TEXT_INPUT};

class WindowBase {
public:
	WindowBase();
	virtual ~WindowBase();

	void set_renderer(rendering::Renderer *renderer);

	virtual void draw() const;

	virtual void on_mouse_down(Sint32 mouse_x, Sint32 mouse_y);
	virtual void on_mouse_up(Sint32 mouse_x, Sint32 mouse_y);
	virtual void on_mouse_over(Sint32 mouse_x, Sint32 mouse_y);
	virtual void on_mouse_exit(Sint32 mouse_x, Sint32 mouse_y);

	virtual void on_drag(Sint32 mouse_x, Sint32 mouse_y, Sint32 dx, Sint32 dy);
	virtual void on_losing_focus();
	virtual void on_gaining_focus();
	virtual void on_text_input(std::string input);
	virtual void on_key_down(SDL_Keycode code);


	virtual SDL_Rect relative_dimension() const;
	virtual void set_relative_dimension(SDL_Rect dimension) {
		m_dimension = dimension;
	}

	SDL_Rect absolute_dimension() const;

	void add_child(std::unique_ptr<WindowBase> child);
	void set_parent(WindowBase *parent) {
		m_parent = parent;
	}

	void set_handler_manager(HandlerManager *manager) {
		m_handler_manager = manager;
	}

	void set_handler(Handler_Type type, const std::string &handler_name);

	std::string get_name() const {
		return m_name;
	}

	void set_name(std::string name) {
		m_name = name;
	}


	WindowBase *get_child_by_name(const std::string &name) const ;

protected:
	void draw(const texture_ptr &ptr) const;
	SDL_Rect get_draw_area() const ;
	friend class creation::WindowLoader;

	WindowBase *child_under_coordinates(Sint32 x, Sint32 y);
	WindowBase *child_under_coordinates_update_focused(Sint32 x, Sint32 y);
	WindowBase *child_under_coordinates_update_hovered(Sint32 x, Sint32 y);
	void update_child(WindowBase *new_child, WindowBase **current_child);

	void do_draw(const texture_ptr &ptr, SDL_Rect destination_rect) const;
	void call_handler(Handler_Type type);


	std::string m_name;
	SDL_Rect m_dimension;
	SDL_Color m_color;
	texture_ptr m_background;
	WindowBase *m_parent;
	rendering::Renderer *m_renderer;
	HandlerManager *m_handler_manager;

	std::vector<std::unique_ptr<WindowBase>> m_children;
	WindowBase *m_focused_child;
	WindowBase *m_hovered_child;
	std::map<Handler_Type, std::string> m_handlers;

	// currently does not change the color of the window after initialization
	// as this requires creation of new base texture
	void set_color(const SDL_Color &color) {
		m_color = color;
	}

private:
	void update_child(WindowBase *new_child, WindowBase **current_child,
			std::function<void(WindowBase *)> new_child_func, std::function<void(WindowBase *)> current_child_func);
};

} /* namespace SDL_GUI */

#endif /* WINDOWBASE_H_ */
