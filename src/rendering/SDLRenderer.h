#ifndef SDLRENDERER_H_
#define SDLRENDERER_H_
#include <SDL2/SDL.h>
#include "Renderer.h"

namespace sdl_gui {
namespace rendering {

class SDLRenderer : public Renderer {
public:
	SDLRenderer(SDL_Renderer *renderer);
	virtual ~SDLRenderer();


	virtual void draw(const texture_ptr &ptr, SDL_Rect *source_rect, SDL_Rect *destination_rect) override;
	SDL_Renderer *get_renderer() const { return m_renderer; }
private:
	SDL_Renderer *m_renderer;
};

} /* namespace rendering */
} /* namespace sdl_gui */

#endif /* SDLRENDERER_H_ */
