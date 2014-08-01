#ifndef TESTRENDERER_H_
#define TESTRENDERER_H_
#include "../../src/rendering/Renderer.h"
#include <functional>

namespace sdl_gui {
class TestRenderer : public rendering::Renderer {
public:

	TestRenderer() : m_source_is_set(false), m_destination_is_set(false),
	m_texture_width(0), m_texture_height(0) {
		m_on_draw = []() {};
	}

	// pointers may be released shortly after this call so we can't simply copy the pointer
	void draw(const texture_ptr &texture, SDL_Rect *source_rect, SDL_Rect *destination_rect) override  {
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

		m_on_draw();
	}

	void texture_width_and_height(const texture_ptr &ptr, int &width, int &height) override {
		width = m_texture_width;
		height = m_texture_height;
	}

	void text_width_and_height(std::string text, int font_size, int *width, int *height) override {
		if (width != nullptr) {
			*width = text.length();
		}
		if (height != nullptr) {
			*height = 1;
		}
	}

	SDL_Rect m_source_rect;
	bool m_source_is_set;

	SDL_Rect m_destination_rect;
	bool m_destination_is_set;

	int m_texture_width;
	int m_texture_height;

	std::function<void()> m_on_draw;

};


} /* sdl_gui */

#endif /* TESTRENDERER_H_ */
