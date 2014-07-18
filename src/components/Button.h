#ifndef BUTTON_H_
#define BUTTON_H_

#include "WindowBase.h"
#include <string>

namespace sdl_gui {

namespace creation {
	class TextureFactory;
}

class Button : public WindowBase {
public:
	Button(const creation::TextureFactory &factory);
	Button(const creation::TextureFactory &factory, std::string text);
	virtual ~Button();

	virtual void draw() override;

	virtual void on_drag(Sint16 mouse_x, Sint16 mouse_y, Sint16 dx, Sint16 dy) override {} // do nothing if dragged

	void set_text(std::string text);
	std::string get_text() { return m_text; }

private:
	friend class creation::WindowLoader;
	std::string m_text;
};

} /* namespace SDL_GUI */

#endif /* BUTTON_H_ */