#include "TextLabel.h"
#include "../creation/TextureFactory.h"

namespace sdl_gui {

TextLabel::TextLabel() : TextLabel("") {
}

TextLabel::TextLabel(std::string text) : m_text(text) {

}

TextLabel::~TextLabel() {
}

void TextLabel::set_text(std::string text) {
//	creation::TextureFactory f;
}


} /* namespace sdl_gui */
