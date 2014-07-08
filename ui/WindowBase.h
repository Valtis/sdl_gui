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
#include <Typedefs.h>

namespace sdl_gui {

class WindowBase {
public:
	WindowBase();
	virtual ~WindowBase();

	virtual void draw(SDL_Renderer *renderer);

	virtual void on_click(Uint16 mouse_x, Uint16 mouse_y);

	virtual void on_drag(Sint16 mouse_x, Sint16 mouse_y, Sint16 dx, Sint16 dy);

	SDL_Rect dimension() { return m_dimension; }

protected:
	SDL_Rect m_dimension;
	SDL_Color m_color;

	texture_ptr m_background;

};

} /* namespace SDL_GUI */

#endif /* WINDOWBASE_H_ */
