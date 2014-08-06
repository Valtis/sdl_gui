#ifndef BUTTON_H_
#define BUTTON_H_

#include "WindowBase.h"
#include <string>

namespace sdl_gui {

namespace creation {
	class ITextureFactory;
}
enum class Button_Graphics : int  { HOVER_OVER, PRESSED_DOWN, DEFAULT };
class Button : public WindowBase {
public:
	Button();
	virtual ~Button();

	virtual void draw() const override;
	virtual void on_mouse_over(Sint32 mouse_x, Sint32 mouse_y) override;
	virtual void on_mouse_exit(Sint32 mouse_x, Sint32 mouse_y) override;
	virtual void on_mouse_down(Sint32 mouse_x, Sint32 mouse_y) override;
	virtual void on_mouse_up(Sint32 mouse_x, Sint32 mouse_y) override;

	virtual void on_losing_focus() override;
	virtual void on_drag(Sint32 mouse_x, Sint32 mouse_y, Sint32 dx, Sint32 dy) override {} // do nothing if dragged

	std::string get_text() const;
private:
	friend class creation::WindowLoader;


	Button_Graphics m_current_texture;
	texture_ptr m_additional_textures[2];
};

} /* namespace SDL_GUI */

#endif /* BUTTON_H_ */
