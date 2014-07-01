
#ifndef WINDOW_H_
#define WINDOW_H_
#include <SDL2/SDL.h>
#include <string>
namespace SDL_GUI {

class Serializer;

class Window {
public:
	Window(int x, int y);
	virtual ~Window();
	void load(Serializer &serializer);
private:
	std::string m_title;

	SDL_Rect m_dimension;
	SDL_Color m_color;

};

}

#endif /* WINDOW_H_ */
