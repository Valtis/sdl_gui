#include "SDLRenderer.h"
#include "SDL2/SDL_ttf.h"
#include "../Typedefs.h"

namespace sdl_gui {
namespace rendering {

SDLRenderer::SDLRenderer(SDL_Renderer *renderer) : m_renderer(renderer) {


}

SDLRenderer::~SDLRenderer() {
	// this class does not own the renderer and the pointer must not be released here
}

void SDLRenderer::draw(const texture_ptr &texture, const SDL_Rect *source_rect, const SDL_Rect *destination_rect) {
	SDL_RenderCopy(m_renderer, texture.get(), source_rect, destination_rect);
}

void SDLRenderer::texture_width_and_height(const texture_ptr &ptr, int &width, int &height) {
	SDL_QueryTexture(ptr.get(), nullptr, nullptr, &width, &height);
}

// Todo: Remove hardcoded font file
void SDLRenderer::text_width_and_height(std::string text, int font_size, int *width, int *height) {
	font_ptr font{TTF_OpenFont("FreeMono.ttf", font_size), TTF_CloseFont};
	TTF_SizeUTF8(font.get(), text.c_str(), width, height);
}

} /* namespace rendering */
} /* namespace sdl_gui */
