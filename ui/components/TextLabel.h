#ifndef TEXTLABEL_H_
#define TEXTLABEL_H_
#include <string>
#include "../WindowBase.h"

namespace sdl_gui {

class TextLabel : public WindowBase {
public:
	TextLabel();
	TextLabel(std::string text);
	virtual ~TextLabel();

	void set_text(std::string text);
	std::string get_text() { return m_text; }

private:
	std::string m_text;
};

} /* namespace sdl_gui */

#endif /* TEXTLABEL_H_ */
