#ifndef UI_H_
#define UI_H_

#include <string>
#include <vector>
#include "Window.h"



namespace sdl_gui {

enum class Handedness { LEFT, RIGHT };

class UI {
public:
	static UI make_ui(SDL_Renderer *renderer);

	virtual ~UI();

	void set_handedness(Handedness h);

	void update(const SDL_Event &event);

	void draw();

	void load_window(const std::string &file_name);

private:
	UI(SDL_Renderer *renderer);

	void handle_click(const SDL_Event &event);
	void handle_drag(const SDL_Event &event);
	bool update_active_window(int x, int y);
	void update_mouse_position();

	Sint16 relative_x(Sint16 x, SDL_Rect r) {
		return x - r.x;
	}

	Sint16 relative_y(Sint16 y, SDL_Rect r) {
		return y - r.y;
	}

	SDL_Renderer *m_renderer;


	// Window is non-copyable, hence we must store it as a pointer as stl requires copyability for container reallocations
	// shared_ptr is used for same reason, as unique_ptr would make UI non-copyable which might be too restricting
	std::vector<std::shared_ptr<Window>> m_windows;

	enum class Drag_Status { NOT_DRAGGING, DRAGGING, FAILED_DRAG };
	Drag_Status m_dragging;

	struct Buttons {
		Uint8 action_button;
		Uint8 menu_button;
	};

	Buttons m_mouse_buttons;



};
}
#endif /* UI_H_ */
