#include "SurfaceOperations.h"
#include <stdexcept>
/* assumes 32 bit bpp for now */

namespace sdl_gui {
namespace creation {

void lock_surface(SDL_Surface *surface)
{
	if (SDL_MUSTLOCK(surface))
	{
		if (SDL_LockSurface(surface) != 0)
		{
		  throw std::runtime_error("Failed to lock surface for manipulation");
		}
	}
}

void unlock_surface(SDL_Surface *surface)
{
	if (SDL_MUSTLOCK(surface))
	{
		SDL_UnlockSurface(surface);
	}
}

Uint8 get_color(int x, int y, int width, Uint32 *pixels, Uint32 mask, Uint8 shift, Uint8 loss)
{
	Uint32 temp;
	temp = pixels[y*width + x] & mask;
	temp = temp >> shift;
	temp = temp << loss;
	return (Uint8)temp;
}


void set_color(int x, int y, int width, Uint32 color, Uint32 *pixels, Uint32 mask, Uint8 shift, Uint8 loss)
{
	pixels[y*width + x] = pixels[y*width + x] ^ (pixels[y*width + x] & mask);
	color = color >> loss;
	color = color << shift;
	pixels[y*width + x] = pixels[y*width + x] | (color);
}

Uint8 get_alpha(SDL_Surface *surface, int x, int y)
{
	lock_surface(surface);
	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	Uint8 retVal = get_color(x, y, surface->w, pixels, fmt->Amask, fmt->Ashift, fmt->Aloss);

	unlock_surface(surface);

	return retVal;
}

Uint8 get_red(SDL_Surface *surface, int x, int y)
{
	lock_surface(surface);

	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	Uint8 retVal = get_color(x, y, surface->w, pixels, fmt->Rmask, fmt->Rshift, fmt->Rloss);

	unlock_surface(surface);
	return retVal;
}


Uint8 get_green(SDL_Surface *surface, int x, int y)
{
	lock_surface(surface);

	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	Uint8 retVal = get_color(x, y, surface->w, pixels, fmt->Gmask, fmt->Gshift, fmt->Gloss);

	unlock_surface(surface);
	return retVal;
}



Uint8 get_blue(SDL_Surface *surface, int x, int y)
{
	lock_surface(surface);

  SDL_PixelFormat *fmt;
  fmt = surface->format;
  Uint32 *pixels = (Uint32 * )surface->pixels;

  Uint8 retVal = get_color(x, y, surface->w, pixels, fmt->Bmask, fmt->Bshift, fmt->Bloss);

  unlock_surface(surface);
  return retVal;
}



void set_alpha(SDL_Surface *surface, int x, int y, Uint32 color)
{
	lock_surface(surface);

	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	set_color(x, y, surface->w, color, pixels, fmt->Amask, fmt->Ashift, fmt->Aloss);
	unlock_surface(surface);
}


void set_red(SDL_Surface *surface, int x, int y, Uint32 color)
{
	lock_surface(surface);

	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	set_color(x, y, surface->w, color, pixels, fmt->Rmask, fmt->Rshift, fmt->Rloss);
	unlock_surface(surface);
}

void set_green(SDL_Surface *surface, int x, int y, Uint32 color)
{
	lock_surface(surface);

	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	set_color(x, y, surface->w, color, pixels, fmt->Gmask, fmt->Gshift, fmt->Gloss);
	unlock_surface(surface);
}

void set_blue(SDL_Surface *surface, int x, int y, Uint32 color)
{
	lock_surface(surface);

	SDL_PixelFormat *fmt;
	fmt = surface->format;
	Uint32 *pixels = (Uint32 * )surface->pixels;

	set_color(x, y, surface->w, color, pixels, fmt->Bmask, fmt->Bshift, fmt->Bloss);
	unlock_surface(surface);
}


void set_color(SDL_Surface *surface, int x, int y, SDL_Color color)
{
	set_red(surface, x, y, color.r);
	set_green(surface, x, y, color.g);
	set_blue(surface, x, y, color.g);
	set_alpha(surface, x, y, color.a);
}

void fill_surface_with_color(SDL_Surface *surface, const SDL_Color &color) {
	SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
}

} /* namespace creation */
} /* namespace sdl_gui */
