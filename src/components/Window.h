
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

	void draw() const override;
	virtual void on_losing_focus() override;
	virtual void on_gaining_focus() override;

	bool has_focus() {
		return m_has_focus;
	}


private:
	friend class creation::WindowLoader;
	std::string m_title;
	bool m_child_is_being_dragged;
	bool m_has_focus;
	texture_ptr m_no_focus_overlay;
};

}

#endif /* WINDOW_H_ */
