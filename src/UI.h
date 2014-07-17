#ifndef UI_H_
#define UI_H_

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "components/Window.h"
#include "HandlerManager.h"
#include "HandlerExceptionPolicy.h"
#include "rendering/SDLRenderer.h"



namespace sdl_gui {

enum class Handedness { LEFT, RIGHT };

class UI : public HandlerManager {
public:
	static UI make_ui(SDL_Renderer *renderer);

	virtual ~UI();

	void set_handedness(Handedness h);

	void set_renderer(SDL_Renderer *renderer);

	void update(const SDL_Event &event);

	void draw();

	void load_window(const std::string &file_name);

	void register_handler(const std::string &name, std::function<void()> handler) {
		m_handlers[name] = handler;
 	}

	void set_handler_exception_policy(std::unique_ptr<HandlerExceptionPolicy> policy);

	void call_handler(const std::string &name) override;

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

	enum class Drag_Status { NOT_DRAGGING, DRAGGING, FAILED_DRAG };
	Drag_Status m_dragging;
	// whether or not this class is responsible for initializing font support; if so, it must also
	// shut it down on destruction
	bool m_has_initialized_ttf;

	// Window is non-copyable, hence we must store it as a pointer as stl requires copyability for container reallocations
	// shared_ptr is used for same reason, as unique_ptr would make UI non-copyable which might be too restricting
	std::vector<std::shared_ptr<Window>> m_windows;
	std::unordered_map<std::string, std::function<void()>> m_handlers;
	std::shared_ptr<HandlerExceptionPolicy> m_handler_exception_policy;



	struct Buttons {
		Uint8 action_button;
		Uint8 menu_button;
	};

	Buttons m_mouse_buttons;



};
}
#endif /* UI_H_ */
