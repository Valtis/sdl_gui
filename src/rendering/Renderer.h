#ifndef RENDERER_H_
#define RENDERER_H_
#include "../Typedefs.h"
namespace sdl_gui {
namespace rendering {

/*
 * Interface class for rendering. Primary motivation is to allow mocking the renderer component in unit tests.
 *
 * */
class Renderer {
public:
	virtual ~Renderer() { }
	virtual void draw(const texture_ptr &ptr, SDL_Rect *source_rect, SDL_Rect *destination_rect) = 0;
};


} /* namespace rendering */
} /* namespace sdl_gui */



#endif /* RENDERER_H_ */
