/*
 * WindowLoader.cpp
 *
 *  Created on: 12.7.2014
 *      Author: valtis
 */

#include "WindowLoader.h"
#include "../components/Window.h"
#include "../components/Button.h"
#include "../components/TextLabel.h"
#include "../components/TextBox.h"
#include "../serialization/Serializer.h"
#include "../serialization/ParseException.h"
#include "../utility/Helpers.h"
#include <SDL2/SDL.h>
#include <stdexcept>

#define WINDOW "window"
#define BUTTON "button"
#define TEXT_LABEL "text"
#define TEXT_BOX "textbox"

#define HORIZONTAL_ALIGNMENT "halign"
#define VERTICAL_ALIGNMENT "valign"
#define HORIZONTAL_OFFSET "horizontal_offset"
#define VERTICAL_OFFSET "vertical_offset"
#define FONT_SIZE "font_size"
#define WORD_WRAP "word_wrap"
#define TEXT "text"
#define NAME "name"

namespace sdl_gui {
namespace creation {

WindowLoader::WindowLoader(serialization::Serializer &serializer, std::shared_ptr<rendering::Renderer> renderer, Window *window, std::shared_ptr<ITextureFactory> factory) :
	m_serializer(serializer), m_renderer(renderer), m_window(window), m_factory{factory} {

	m_parent_windows[WINDOW][""] = window;

	if (renderer == nullptr) {
		throw std::invalid_argument("Renderer must not be null");
	} else if (window == nullptr) {
		throw std::invalid_argument("Window must not be null");
	}

	m_loaders[WINDOW] = [=](const serialization::Node &node) {
		set_generic_parameters(node, m_window);
		m_window->m_background = m_factory->create_window(m_window->m_dimension.w, m_window->m_dimension.h, m_window->m_color);
		m_window->m_no_focus_overlay = m_factory->create_window(m_window->m_dimension.w, m_window->m_dimension.h, {255, 255, 255, 100});
		m_window->m_title = node.value("title");
		m_parent_windows[WINDOW][node.value(NAME)] = m_window;
	};

	m_loaders[BUTTON] = [=](const serialization::Node &node) {

		std::unique_ptr<Button> button{new Button{}};
		set_generic_parameters(node, button.get());
		button->m_background = m_factory->create_button(button->m_dimension.w, button->m_dimension.h, button->m_color);


		SDL_Color hover_over_color = utility::lighter_color(button->m_color, 0.4);
		button->m_additional_textures[static_cast<int>(Button_Graphics::HOVER_OVER)] = m_factory->create_button(button->m_dimension.w, button->m_dimension.h, hover_over_color);
		SDL_Color pressed_down_color = utility::darker_color(button->m_color, 0.5);
		button->m_additional_textures[static_cast<int>(Button_Graphics::PRESSED_DOWN)] = m_factory->create_button(button->m_dimension.w, button->m_dimension.h, pressed_down_color);

		m_parent_windows[BUTTON][node.value(NAME)] = button.get();
		m_parent_windows[node.parent()->name()][node.parent()->value(NAME)]->add_child(std::move(button));
	};

	m_loaders[TEXT_LABEL] = [=](const serialization::Node &node) {
		std::unique_ptr<TextLabel> label{new TextLabel{m_factory}};
		set_generic_parameters(node, label.get());


		// if width or height is zero, use parent width/height. This is required for centering to work properly
		int width = (label->m_dimension.w == 0) ? m_parent_windows[node.parent()->name()][node.parent()->value(NAME)]->relative_dimension().w
		                                                                                  : label->m_dimension.w;

		int height = (label->m_dimension.w== 0) ? m_parent_windows[node.parent()->name()][node.parent()->value(NAME)]->relative_dimension().h
				                                                                                  : label->m_dimension.h;

		label->set_relative_dimension({label->m_dimension.x, label->m_dimension.y, width, height});


		auto get_halignment = [](const std::string &align) -> Text_HAlignment {
			if (align == "center") {
				return Text_HAlignment::CENTER;
			} else if (align == "right") {
				return Text_HAlignment::RIGHT;
			} else {
				return Text_HAlignment::LEFT;
			}
		};

		auto get_valignment = [](const std::string &align) -> Text_VAlignment {
					if (align == "center") {
						return Text_VAlignment::CENTER;
					} else if (align == "bottom") {
						return Text_VAlignment::BOTTOM;
					} else {
						return Text_VAlignment::TOP;
					}
				};

		label->set_font_size(stoi(node.value(FONT_SIZE), DEFAULT_FONT_SIZE));

		label->set_horizontal_alignment(get_halignment(node.value(HORIZONTAL_ALIGNMENT)), stoi(node.value(HORIZONTAL_OFFSET)));
		label->set_vertical_alignment(get_valignment(node.value(VERTICAL_ALIGNMENT)), stoi(node.value(VERTICAL_OFFSET)));

		label->set_text(node.value(TEXT));
		m_parent_windows[TEXT_LABEL][node.value(NAME)] = label.get();
		m_parent_windows[node.parent()->name()][node.parent()->value(NAME)]->add_child(std::move(label));
	};

	m_loaders[TEXT_BOX] = [=](const serialization::Node &node) {
		std::unique_ptr<TextBox> box{new TextBox{m_factory, stoi(node.value(FONT_SIZE))}};
		set_generic_parameters(node, box.get());
		box->m_background = m_factory->create_text_box(box->m_dimension.w, box->m_dimension.h, box->m_color);

		box->set_word_wrap(node.value(WORD_WRAP) == "true");

		m_parent_windows[TEXT_BOX][node.value(NAME)] = box.get();
		m_parent_windows[node.parent()->name()][node.parent()->value(NAME)]->add_child(std::move(box));
	};


}

WindowLoader::~WindowLoader() {
	// m_renderer and m_window are not owned by this class and must not be deleted here
}

// helper function; returns the default value on empty string instead of throwing
int WindowLoader::stoi(const std::string &str, int default_value) {
	if (str.empty()) {
		return default_value;
	}
	return std::stoi(str);
}

void WindowLoader::load() {
	m_serializer.accept([=](const serialization::Node &node) {this->visitor(node); });
}

void WindowLoader::visitor(const serialization::Node &node) {
	if (m_loaders.count(node.name()) != 0) {
		if (node.value(NAME).empty()) {
			throw serialization::ParseException("Node must have a name (type: " + node.name() + ")");
		} else if (m_names.count(node.value(NAME)) != 0) {
			throw serialization::ParseException("Node must have unique name (type: " + node.name() + ")");
		}
		m_names.insert(node.value("name"));
		m_loaders[node.name()](node);
	}
}


void WindowLoader::set_generic_parameters(const serialization::Node &node, WindowBase *base) {
	set_dimensions(node, base);
	set_color(node, base);
	base->set_renderer(m_renderer.get());
	base->m_name = node.value(NAME);
	set_handlers(node, base);

}

void WindowLoader::set_dimensions(const serialization::Node &node, WindowBase *base) {
	base->set_relative_dimension({
		stoi(node.value("x")),
		stoi(node.value("y")),
		stoi(node.value("w")),
		stoi(node.value("h")),
	});
}

void WindowLoader::set_color(const serialization::Node &node, WindowBase *base) {
	base->set_color({
		(Uint8)stoi(node.value("r")),
		(Uint8)stoi(node.value("g")),
		(Uint8)stoi(node.value("b")),
		(Uint8)stoi(node.value("a"), 255)
	});
}

void WindowLoader::set_handlers(const serialization::Node &node, WindowBase *base) {
	base->set_handler(Handler_Type::ON_CLICK, node.value("on_click"));
}



} /* namespace creation */
} /* namespace sdl_gui */
