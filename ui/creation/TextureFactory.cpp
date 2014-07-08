/*
 * TextureFactory.cpp
 *
 *  Created on: 2.7.2014
 *      Author: valtis
 */

#include "TextureFactory.h"

#include <stdexcept>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define RMASK 0xff000000
#define GMASK 0x00ff0000
#define BMASK 0x0000ff00
#define AMASK 0x000000ff
#else
#define RMASK 0x000000ff
#define GMASK 0x0000ff00
#define BMASK 0x00ff0000
#define AMASK 0xff000000
#endif

#include "AllocationFailureException.h"

namespace sdl_gui {

namespace creation {


TextureFactory::TextureFactory(SDL_Renderer *renderer) : m_renderer(renderer) {

}

TextureFactory::~TextureFactory() {
	// do not release the renderer; we do not own the pointer
}

texture_ptr TextureFactory::create_window(int width, int height, SDL_Color color) {
	auto surface = create_surface(width, height);
	SDL_FillRect(surface.get(), nullptr, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));

	texture_ptr texture(SDL_CreateTextureFromSurface(m_renderer, surface.get()), SDL_DestroyTexture);
	if (texture == nullptr) {
		throw AllocationFailureException("Failed to allocate memory for texture");
	}
	return texture;

}

surface_ptr TextureFactory::create_surface(int width, int height) {
	surface_ptr surface(SDL_CreateRGBSurface(0, width, height, 32, RMASK, GMASK, BMASK, AMASK), SDL_FreeSurface);
	if (surface == nullptr) {
		throw AllocationFailureException("Failed to allocate memory for surface");
	}
	return surface;
}

} /*namespace construction */
} /* namespace SDL_GUI */
