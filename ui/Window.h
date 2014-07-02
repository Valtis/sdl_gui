
#ifndef WINDOW_H_
#define WINDOW_H_
#include <SDL2/SDL.h>
#include <string>
#include <memory>

namespace SDL_GUI {

class Serializer;

class Window {
public:
	Window();
	Window(int x, int y);

	virtual ~Window();
	void load(Serializer &serializer, SDL_Renderer *renderer);
	void draw(SDL_Renderer *renderer);

private:
	std::string m_title;

	SDL_Rect m_dimension;
	SDL_Color m_color;

	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_background;

};

}

#endif /* WINDOW_H_ */
