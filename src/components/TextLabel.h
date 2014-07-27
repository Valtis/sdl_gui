#ifndef TEXTLABEL_H_
#define TEXTLABEL_H_
#include <string>
#include "WindowBase.h"
#include "../creation/ITextureFactory.h"
#define DEFAULT_FONT_SIZE 12
namespace sdl_gui {

enum class Text_HAlignment { LEFT, CENTER, RIGHT };
enum class Text_VAlignment { TOP, CENTER, BOTTOM };


class TextLabel : public WindowBase {
public:
	TextLabel(std::shared_ptr<creation::ITextureFactory> factory);
	virtual ~TextLabel();

	SDL_Rect relative_dimension() const override;

	void set_text(std::string text);
	std::string get_text() { return m_text; }

	void set_font_size(int size);


	// for center, offset_from_align_direction is from the left
	void set_horizontal_alignment(Text_HAlignment alingment, int offset_from_align_direction);

	// for center, offset is from the top
	void set_vertical_alignment(Text_VAlignment alingment, int offset_from_align_direction);

private:
	std::string m_text;
	int m_font_size;

	Text_HAlignment m_halignment;
	int m_hoffset;

	Text_VAlignment m_valignment;
	int m_voffset;

	std::shared_ptr<creation::ITextureFactory> m_factory;
};

} /* namespace sdl_gui */

#endif /* TEXTLABEL_H_ */
