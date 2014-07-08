
#ifndef TEXTUREFACTORY_H_
#define TEXTUREFACTORY_H_
#include <SDL2/SDL.h>
#include <memory>
#include <string>


namespace sdl_gui {
namespace creation {

class TextureFactory {

public:
	TextureFactory(SDL_Renderer *renderer);
	virtual ~TextureFactory();

	texture_ptr create_window(int width, int height, const SDL_Color &color);
	texture_ptr create_button(int width, int height, const SDL_Color &color);
	texture_ptr create_text(std::string text);

private:
	surface_ptr create_surface(int width, int height, const SDL_Color &color);
	void fill_surface_with_color(SDL_Surface *surface, const SDL_Color &color);
	texture_ptr create_texture(SDL_Surface *surface);

	SDL_Renderer *m_renderer;
};

} /*namespace construction */
} /* namespace SDL_GUI */

#endif
