
#ifndef TEXTUREFACTORY_H_
#define TEXTUREFACTORY_H_
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "../Typedefs.h"


namespace sdl_gui {
namespace creation {

class TextureFactory {

public:
	TextureFactory(SDL_Renderer *renderer);
	virtual ~TextureFactory();

	texture_ptr create_window(const int width, const int height, const SDL_Color &color);
	texture_ptr create_button(const int width, const int height, const SDL_Color &color);
	texture_ptr create_text(std::string text);

private:
	surface_ptr create_surface(const int width, const int height, const SDL_Color &color);

	texture_ptr create_texture(SDL_Surface *surface);

	void draw_box(SDL_Surface *surface, SDL_Rect dimension, SDL_Color color);

	SDL_Renderer *m_renderer;
};

} /*namespace construction */
} /* namespace SDL_GUI */

#endif
