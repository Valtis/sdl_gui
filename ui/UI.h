#ifndef UI_H_
#define UI_H_
struct SDL_Renderer;
#include <string>
#include <list>
#include "Window.h"



namespace SDL_GUI {
class UI {
public:
	static UI make_ui(SDL_Renderer &renderer);

	virtual ~UI();

	void draw();

	void load_window(const std::string &file_name);

private:
	UI(SDL_Renderer &renderer);

	SDL_Renderer &m_renderer;

	std::list<std::shared_ptr<Window>> m_windows;
};
}
#endif /* UI_H_ */
