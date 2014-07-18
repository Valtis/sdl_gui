#ifndef TEXTLABEL_H_
#define TEXTLABEL_H_
#include <string>
#include "WindowBase.h"
#include "../creation/ITextureFactory.h"
namespace sdl_gui {

class TextLabel : public WindowBase {
public:
	TextLabel(std::shared_ptr<creation::ITextureFactory> factory);

	TextLabel(std::shared_ptr<creation::ITextureFactory> factory, std::string text);
	virtual ~TextLabel();

	void set_text(std::string text);
	std::string get_text() { return m_text; }

private:
	std::string m_text;
	std::shared_ptr<creation::ITextureFactory> m_factory;
};

} /* namespace sdl_gui */

#endif /* TEXTLABEL_H_ */
