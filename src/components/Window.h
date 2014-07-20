
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

	virtual void on_drag(Sint32 mouse_x, Sint32 mouse_y, Sint32 dx, Sint32 dy);
	virtual void on_mouse_up(Sint32 mouse_x, Sint32 mouse_y) override;

private:
	friend class creation::WindowLoader;
	std::string m_title;
	bool m_child_is_being_dragged;

};

}

#endif /* WINDOW_H_ */
