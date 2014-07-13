/*
 * TextureFactory.cpp
 *
 *  Created on: 2.7.2014
 *      Author: valtis
 */

#include "TextureFactory.h"
#include <SDL2/SDL_ttf.h>

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

#include "CreationFailureException.h"

namespace sdl_gui {

namespace creation {


TextureFactory::TextureFactory(SDL_Renderer *renderer) : m_renderer(renderer) {

}

TextureFactory::~TextureFactory() {
	// do not delete the renderer; this class does not own the pointer
}

texture_ptr TextureFactory::create_window(int width, int height, const SDL_Color &color) {
	auto surface = create_surface(width, height, color);
	return create_texture(surface.get());
}



texture_ptr TextureFactory::create_button(int width, int height, const SDL_Color &color) {
	auto surface = create_surface(width, height, color);
	return create_texture(surface.get());
}


// TODO: allow size & color to be controlled by the caller
texture_ptr TextureFactory::create_text(std::string text) {
	font_ptr font{TTF_OpenFont("FreeMono.ttf", 12), TTF_CloseFont};
	if (font == nullptr) {
		// TODO: replace with appropriate exception type
		throw CreationFailureException(std::string("Failed to open font file: ") + TTF_GetError());

	}

	surface_ptr font_surface{TTF_RenderText_Blended(font.get(), text.c_str(), {0, 0, 0, 255}), SDL_FreeSurface};

	if (font_surface == nullptr) {
		throw CreationFailureException(std::string("Failed to create surface for text: ") + TTF_GetError());
	}

	return create_texture(font_surface.get());
}

surface_ptr TextureFactory::create_surface(int width, int height, const SDL_Color &color) {
	surface_ptr surface{SDL_CreateRGBSurface(0, width, height, 32, RMASK, GMASK, BMASK, AMASK), SDL_FreeSurface};

	if (surface == nullptr) {
		throw CreationFailureException(std::string("Failed to create surface: ") + SDL_GetError());
	}

	fill_surface_with_color(surface.get(), color);
	return surface;
}

texture_ptr TextureFactory::create_texture(SDL_Surface *surface) {
	texture_ptr texture{SDL_CreateTextureFromSurface(m_renderer, surface), SDL_DestroyTexture};

	if (texture == nullptr) {
		throw CreationFailureException(std::string("Failed to create texture: ") + SDL_GetError());
	}
	return texture;
}

void TextureFactory::fill_surface_with_color(SDL_Surface *surface, const SDL_Color &color) {
	SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
}

} /*namespace construction */
} /* namespace sdl_gui */
