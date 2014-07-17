/*
 * WindowLoader.cpp
 *
 *  Created on: 12.7.2014
 *      Author: valtis
 */

#include "WindowLoader.h"
#include "../components/Window.h"
#include "../components/Button.h"
#include "../serialization/Serializer.h"
#include <SDL2/SDL.h>
#include <stdexcept>

namespace sdl_gui {
namespace creation {

WindowLoader::WindowLoader(serialization::Serializer &serializer, std::shared_ptr<rendering::Renderer> renderer, Window *window, TextureFactory factory) :
	m_serializer(serializer), m_renderer(renderer), m_window(window), m_factory{factory} {
	if (renderer == nullptr) {
		throw std::invalid_argument("Renderer must not be null");
	} else if (window == nullptr) {
		throw std::invalid_argument("Window must not be null");
	}

	m_loaders["window"] = [=](const serialization::Node &node) {
		set_generic_parameters(node, m_window);
		m_window->m_title = node.value("title");
	};

	m_loaders["button"] = [=](const serialization::Node &node) {
		std::unique_ptr<Button> button{new Button{m_factory, node.value("text")}};
		set_generic_parameters(node, button.get());

		button->set_renderer(m_renderer);
		button->set_text(node.value("text"));
		m_window->add_child(std::move(button));
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
		m_loaders[node.name()](node);
	}
}


void WindowLoader::set_generic_parameters(const serialization::Node &node, WindowBase *base) {
	set_dimensions(node, base->m_dimension);
	set_color(node, base->m_color);
	set_handlers(node, base);
	base->m_background = m_factory.create_window(base->m_dimension.w, base->m_dimension.h, base->m_color);
}

void WindowLoader::set_dimensions(const serialization::Node &node, SDL_Rect &dimension) {
	dimension.x = stoi(node.value("x"));
	dimension.y = stoi(node.value("y"));
	dimension.w = stoi(node.value("w"));
	dimension.h = stoi(node.value("h"));
}

void WindowLoader::set_color(const serialization::Node &node, SDL_Color &color) {
	color.r = stoi(node.value("r"));
	color.g = stoi(node.value("g"));
	color.b = stoi(node.value("b"));
	color.a = stoi(node.value("a"), 255);
}

void WindowLoader::set_handlers(const serialization::Node &node, WindowBase *base) {
	base->set_handler(HandlerType::ON_CLICK, node.value("on_click"));
}



} /* namespace creation */
} /* namespace sdl_gui */
