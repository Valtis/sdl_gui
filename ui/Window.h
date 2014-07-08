
#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
#include "WindowBase.h"

namespace sdl_gui {

class Serializer;

class Window : public WindowBase {
public:
	Window();
	Window(int x, int y);

	virtual ~Window();

	void load(Serializer &serializer, SDL_Renderer *renderer);

	virtual void on_drag(Sint16 mouse_x, Sint16 mouse_y, Sint16 dx, Sint16 dy);

private:
	std::string m_title;

};

}

#endif /* WINDOW_H_ */
