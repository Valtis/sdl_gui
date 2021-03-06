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
	virtual void draw(const texture_ptr &ptr, const SDL_Rect *source_rect, const SDL_Rect *destination_rect) = 0;
	virtual void texture_width_and_height(const texture_ptr &ptr, int &width, int &height) = 0;
	virtual void text_width_and_height(std::string text, int font_size, int *width, int *height) = 0;
	virtual int get_font_height(int font_size) = 0;

};


} /* namespace rendering */
} /* namespace sdl_gui */



#endif /* RENDERER_H_ */
