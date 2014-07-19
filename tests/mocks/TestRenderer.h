#ifndef TESTRENDERER_H_
#define TESTRENDERER_H_
#include "../../src/rendering/Renderer.h"


namespace sdl_gui {
class TestRenderer : public rendering::Renderer {
public:
	TestRenderer() : m_source_is_set(false), m_destination_is_set(false),
	m_texture_width(0), m_texture_height(0) {

	}

	// pointers may be released shortly after this call so we can't simply copy the pointer
	void draw(const texture_ptr &texture, SDL_Rect *source_rect, SDL_Rect *destination_rect) {
		m_source_is_set = false;
		m_destination_is_set = false;

		if (source_rect != nullptr) {
			m_source_rect = *source_rect;
			m_source_is_set = true;
		}

		if (destination_rect != nullptr) {
			m_destination_rect = *destination_rect;
			m_destination_is_set = true;
		}
	}

	void texture_width_and_height(const texture_ptr &ptr, int &width, int &height) {
		width = m_texture_width;
		height = m_texture_height;
	}

	SDL_Rect m_source_rect;
	bool m_source_is_set;

	SDL_Rect m_destination_rect;
	bool m_destination_is_set;

	int m_texture_width;
	int m_texture_height;
};


} /* sdl_gui */

#endif /* TESTRENDERER_H_ */
