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
#include "Typedefs.h"

namespace sdl_gui {

namespace creation {
	class WindowLoader;
}

class WindowBase {
public:
	WindowBase();
	virtual ~WindowBase();

	virtual void draw(SDL_Renderer *renderer);

	virtual void on_click(Sint16 mouse_x, Sint16 mouse_y);

	virtual void on_drag(Sint16 mouse_x, Sint16 mouse_y, Sint16 dx, Sint16 dy);

	SDL_Rect dimension() { return m_dimension; }
	void add_child(std::unique_ptr<WindowBase> child);
	void set_parent(WindowBase *parent) { m_parent = parent; }


protected:
	friend class creation::WindowLoader;
	SDL_Rect m_dimension;
	SDL_Color m_color;

	texture_ptr m_background;

	WindowBase *m_parent;
	std::vector<std::unique_ptr<WindowBase>> m_children;
	WindowBase *child_under_coordinates(Sint16 x, Sint16 y);

};

} /* namespace SDL_GUI */

#endif /* WINDOWBASE_H_ */
