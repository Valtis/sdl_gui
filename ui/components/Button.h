#ifndef BUTTON_H_
#define BUTTON_H_

#include <../WindowBase.h>
#include <../Typedefs.h>
#include <string>


namespace sdl_gui {
namespace component {

class Button : public WindowBase {
public:
	Button();
	virtual ~Button();

private:
	std::string m_text;
};


} /* namespace component */
} /* namespace SDL_GUI */

#endif /* BUTTON_H_ */
