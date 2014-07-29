#ifndef TEXTBOX_H_
#define TEXTBOX_H_
#include "WindowBase.h"
#include "TextLabel.h"
#include <memory>


namespace sdl_gui {

namespace creation {
	class ITextureFactory;
}

class TextBox : public WindowBase {
public:
	TextBox(std::shared_ptr<creation::ITextureFactory> factory);
	virtual ~TextBox();

	virtual void on_key_down(SDL_Keycode code) override;
	virtual void on_text_input(std::string text) override;
	virtual void draw() const override;

	virtual void on_gaining_focus() override;
	virtual void on_losing_focus() override;

	void set_text(std::string text);

private:
	std::shared_ptr<creation::ITextureFactory> m_factory;
	std::string m_text;
	// vector needs copyability in order to resize and unique_ptrs are non-copyable
	// therefore we use shared_ptrs
	std::vector<std::shared_ptr<TextLabel>> m_text_lines;
};

} /* namespace sdl_gui */

#endif /* TEXTBOX_H_ */
