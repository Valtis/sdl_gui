#ifndef TESTTEXTUREFACTORY_H_
#define TESTTEXTUREFACTORY_H_

#include "../../src/creation/ITextureFactory.h"
namespace sdl_gui {

class TestTextureFactory : public creation::ITextureFactory {
public:
	virtual texture_ptr create_window(const int width, const int height, const SDL_Color &color) {
		return texture_ptr{ nullptr, SDL_DestroyTexture };
	}

	virtual texture_ptr create_button(const int width, const int height, const SDL_Color &color) {
		return texture_ptr{ nullptr, SDL_DestroyTexture };
	}

	virtual texture_ptr create_text(std::string text) {
		return texture_ptr{ nullptr, SDL_DestroyTexture };
	}
};

} /* namespace sdl_gui */

#endif /* TESTTEXTUREFACTORY_H_ */