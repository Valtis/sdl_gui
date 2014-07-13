#ifndef WINDOWLOADER_H_
#define WINDOWLOADER_H_
#include <string>
#include <functional>
#include <unordered_map>

#include "TextureFactory.h"

struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Color;


namespace sdl_gui {


namespace serialization {
	class Serializer;
	class Node;
}

class Window;
class WindowBase;

namespace creation {

class WindowLoader {
public:
	WindowLoader(serialization::Serializer &serializer, SDL_Renderer *renderer, Window *window);
	virtual ~WindowLoader();
	void load();

private:

	int stoi(const std::string &str, int default_value = 0);
	void visitor(const serialization::Node &node);

	void set_dimensions(const serialization::Node &node, SDL_Rect &dimension);
	void set_color(const serialization::Node &node, SDL_Color &color);
	void set_generic_parameters(const serialization::Node &node, WindowBase *base);

	serialization::Serializer &m_serializer;
	SDL_Renderer *m_renderer;
	Window *m_window;
	TextureFactory m_factory;
	std::unordered_map<std::string, std::function<void(const serialization::Node &node)>> m_loaders;

};

} /* namespace creation */
} /* namespace sdl_gui */

#endif /* WINDOWLOADER_H_ */
