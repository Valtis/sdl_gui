#ifndef BUTTON_H_
#define BUTTON_H_

#include "../WindowBase.h"
#include "../Typedefs.h"
#include <string>


namespace sdl_gui {
namespace component {

class Button : public WindowBase {
public:
	Button();
	Button(std::string text);
	virtual ~Button();

	virtual void draw(SDL_Renderer *renderer) override;

	virtual void on_click(Sint16 x, Sint16 y) override;

private:
	std::string m_text_string;
	texture_ptr m_text_texture;
};


} /* namespace component */
} /* namespace SDL_GUI */

#endif /* BUTTON_H_ */
