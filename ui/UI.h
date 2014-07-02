#ifndef UI_H_
#define UI_H_
struct SDL_Renderer;
#include <string>
#include <vector>
#include "Window.h"



namespace SDL_GUI {
class UI final {
public:
	static UI make_ui(SDL_Renderer &renderer);

	virtual ~UI();

	void update();

	void load_window(const std::string &file_name);

private:
	UI(SDL_Renderer &renderer);

	SDL_Renderer &m_renderer;

	std::vector<Window> m_windows;
};
}
#endif /* UI_H_ */
