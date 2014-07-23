#ifndef TEXTLABEL_H_
#define TEXTLABEL_H_
#include <string>
#include "WindowBase.h"
#include "../creation/ITextureFactory.h"
#define DEFAULT_FONT_SIZE 12
namespace sdl_gui {

enum class Text_Position {};

class TextLabel : public WindowBase {
public:
	TextLabel(std::shared_ptr<creation::ITextureFactory> factory);
	virtual ~TextLabel();

	void set_text(std::string text);
	std::string get_text() { return m_text; }

	void set_font_size(int size);

private:
	std::string m_text;
	int m_font_size;
	std::shared_ptr<creation::ITextureFactory> m_factory;
};

} /* namespace sdl_gui */

#endif /* TEXTLABEL_H_ */
