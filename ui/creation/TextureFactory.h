
#ifndef TEXTUREFACTORY_H_
#define TEXTUREFACTORY_H_
#include <SDL2/SDL.h>
#include <memory>

namespace sdl_gui {
namespace creation {

typedef std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture_ptr;
typedef std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface_ptr;

class TextureFactory {

public:
	TextureFactory(SDL_Renderer *renderer);
	virtual ~TextureFactory();

	texture_ptr create_window(int width, int height, SDL_Color color);
private:
	surface_ptr create_surface(int width, int height);

	SDL_Renderer *m_renderer;
};

} /*namespace construction */
} /* namespace SDL_GUI */

#endif
