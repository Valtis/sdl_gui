
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

	virtual void on_drag(Sint16 mouse_x, Sint16 mouse_y, Sint16 dx, Sint16 dy);
	virtual void on_mouse_up(Sint16 mouse_x, Sint16 mouse_y) override;

private:
	friend class creation::WindowLoader;
	std::string m_title;
	bool m_child_is_being_dragged;

};

}

#endif /* WINDOW_H_ */
