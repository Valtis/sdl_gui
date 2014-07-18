#ifndef ITEXTUREFACTORY_H_
#define ITEXTUREFACTORY_H_
#include <SDL2/SDL.h>
#include "../Typedefs.h"

namespace sdl_gui {
namespace creation {

class ITextureFactory {
public:
	virtual ~ITextureFactory() { }
	virtual texture_ptr create_window(const int width, const int height, const SDL_Color &color) = 0;
	virtual texture_ptr create_button(const int width, const int height, const SDL_Color &color) = 0;
	virtual texture_ptr create_text(std::string text) = 0;

};

} /* namespace creation*/
} /* namespace sdl_gui */




#endif /* ITEXTUREFACTORY_H_ */
