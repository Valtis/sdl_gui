#ifndef BUTTON_H_
#define BUTTON_H_

#include "WindowBase.h"
#include <string>

namespace sdl_gui {

namespace creation {
	class TextureFactory;
}
enum class ButtonGraphics : int  { HOVER_OVER, PRESSED_DOWN, DEFAULT };
class Button : public WindowBase {
public:
	Button(const creation::TextureFactory &factory);
	Button(const creation::TextureFactory &factory, std::string text);
	virtual ~Button();

	virtual void draw() override;
	virtual void on_mouse_over(Sint16 mouse_x, Sint16 mouse_y) override;
	virtual void on_mouse_down(Sint16 mouse_x, Sint16 mouse_y) override;
	virtual void on_mouse_up(Sint16 mouse_x, Sint16 mouse_y) override;

	virtual void on_losing_focus() override;
	virtual void on_drag(Sint16 mouse_x, Sint16 mouse_y, Sint16 dx, Sint16 dy) override {} // do nothing if dragged

	void set_text(std::string text);
	std::string get_text() { return m_text; }

private:
	friend class creation::WindowLoader;


	ButtonGraphics m_current_texture;
	texture_ptr m_additional_textures[2];
	std::string m_text;
};

} /* namespace SDL_GUI */

#endif /* BUTTON_H_ */
