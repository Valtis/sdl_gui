/*
 * WindowBase.h
 *
 *  Created on: 3.7.2014
 *      Author: valtis
 */

#ifndef WINDOWBASE_H_
#define WINDOWBASE_H_
#include <SDL2/SDL.h>
#include <memory>
namespace SDL_GUI {

class WindowBase {
public:
	WindowBase();
	virtual ~WindowBase();
	void draw(SDL_Renderer *renderer);

protected:
	SDL_Rect m_dimension;
	SDL_Color m_color;

	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_background;

};

} /* namespace SDL_GUI */

#endif /* WINDOWBASE_H_ */
