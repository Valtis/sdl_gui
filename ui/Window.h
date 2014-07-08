
#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
#include "WindowBase.h"

namespace sdl_gui {

class Serializer;

class Window : public WindowBase {
public:
	Window();
	Window(int x, int y);

	virtual ~Window();

	void load(Serializer &serializer, SDL_Renderer *renderer);

private:
	std::string m_title;


};

}

#endif /* WINDOW_H_ */
