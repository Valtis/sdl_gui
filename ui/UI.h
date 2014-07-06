#ifndef UI_H_
#define UI_H_

#include <string>
#include <vector>
#include "Window.h"

struct SDL_Renderer;

namespace SDL_GUI {
class UI {
public:
	static UI make_ui(SDL_Renderer &renderer);

	virtual ~UI();

	void update(const SDL_Event &event);

	void draw();

	void load_window(const std::string &file_name);

private:
	UI(SDL_Renderer &renderer);

	void handle_drag();
	bool update_active_window(int x, int y);
	void update_mouse_position();

	SDL_Renderer &m_renderer;


	// Window is non-copyable, hence we must store it as a pointer as stl requires copyability for container reallocations
	// shared_ptr is used for same reason, as unique_ptr would make UI non-copyable which might be too restricting
	std::vector<std::shared_ptr<Window>> m_windows;

	// workaround for a glitch
	SDL_Point m_old_mouse_position;

	enum class Drag_Status { NOT_DRAGGING, DRAGGING, FAILED_DRAG };
	Drag_Status m_dragging;
};
}
#endif /* UI_H_ */
