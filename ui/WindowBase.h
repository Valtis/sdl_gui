/*
 * WindowBase.h
 *
 *  Created on: 3.7.2014
 *      Author: valtis
 */

#ifndef WINDOWBASE_H_
#define WINDOWBASE_H_
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <map>
#include "Typedefs.h"

namespace sdl_gui {

class HandlerManager;

namespace creation {
	class WindowLoader;
}

enum class HandlerType { ON_CLICK };

class WindowBase {
public:
	WindowBase();
	virtual ~WindowBase();

	void set_renderer(SDL_Renderer *renderer);

	virtual void draw();

	virtual void on_click(Sint16 mouse_x, Sint16 mouse_y);

	virtual void on_drag(Sint16 mouse_x, Sint16 mouse_y, Sint16 dx, Sint16 dy);

	SDL_Rect relative_dimension();
	void set_relative_dimension(SDL_Rect dimension) { m_dimension = dimension; }
	SDL_Rect absolute_dimension();

	void add_child(std::unique_ptr<WindowBase> child);
	void set_parent(WindowBase *parent) {
		m_parent = parent;
	}

	void set_handler_manager(HandlerManager *manager) {
		m_handler_manager = manager;
	}

	void set_handler(HandlerType type, const std::string &handler_name);

protected:
	friend class creation::WindowLoader;
	WindowBase *child_under_coordinates(Sint16 x, Sint16 y);
	void do_draw(SDL_Rect destination_rect);
	void call_handler(HandlerType type);



	SDL_Rect m_dimension;
	SDL_Color m_color;
	texture_ptr m_background;
	WindowBase *m_parent;
	SDL_Renderer *m_renderer;
	HandlerManager *m_handler_manager;

	std::vector<std::unique_ptr<WindowBase>> m_children;
	std::map<HandlerType, std::string> m_handlers;
};

} /* namespace SDL_GUI */

#endif /* WINDOWBASE_H_ */
