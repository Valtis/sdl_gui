#include "SDLRenderer.h"

namespace sdl_gui {
namespace rendering {

SDLRenderer::SDLRenderer(SDL_Renderer *renderer) : m_renderer(renderer) {


}

SDLRenderer::~SDLRenderer() {
	// this class does not own the renderer and the pointer must not be released here
}

void SDLRenderer::draw(const texture_ptr &texture, SDL_Rect *source_rect, SDL_Rect *destination_rect) {
	SDL_RenderCopy(m_renderer, texture.get(), source_rect, destination_rect);
}

void SDLRenderer::texture_width_and_height(const texture_ptr &ptr, int &width, int &height) {
	SDL_QueryTexture(ptr.get(), nullptr, nullptr, &width, &height);
}

} /* namespace rendering */
} /* namespace sdl_gui */
