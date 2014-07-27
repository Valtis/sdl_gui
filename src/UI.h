#ifndef UI_H_
#define UI_H_

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "components/Window.h"

#include "HandlerManager.h"
#include "HandlerErrorPolicy.h"
#include "UIComponents.h"

#include "rendering/SDLRenderer.h"
#include "creation/ITextureFactory.h"



namespace sdl_gui {

enum class Handedness { LEFT, RIGHT };

class UI : public HandlerManager {
public:

	explicit UI(SDL_Renderer *renderer);
	virtual ~UI();

	// copying the UI may lead to releasing font support too early (when first destructor runs)
	// so copying is disabled
	UI &operator=(const UI &ui) = delete;
	UI(const UI &ui) = default;
	void set_handedness(Handedness h);

	void set_renderer(SDL_Renderer *renderer);

	void update(const SDL_Event &event);

	void draw();

	void load_window(const std::string &file_name);

	void add_window(std::shared_ptr<Window> window);

	void register_handler(const std::string &name, std::function<void(UIComponents, WindowBase *)> handler) {
		m_handlers[name] = handler;
 	}

	void set_handler_error_policy(std::unique_ptr<HandlerErrorPolicy> policy) {
		m_handler_error_policy = std::move(policy);
	}

	void call_handler(const std::string &name, WindowBase *caller) override;

private:
	std::shared_ptr<rendering::Renderer> initialize_window(std::shared_ptr<Window> window);
	void handle_click(const SDL_Event &event);
	void handle_motion(const SDL_Event &event);
	bool update_active_window(int x, int y);
	void update_mouse_position();
	SDL_Renderer *m_renderer;

	// whether or not this class is responsible for initializing font support; if so, it must also
	// shut it down on destruction

	bool m_has_initialized_ttf;

	enum class Drag_Status { NOT_DRAGGING, DRAGGING, FAILED_DRAG };
	Drag_Status m_dragging;

	// Window is non-copyable, hence we must store it as a pointer as stl requires copyability for container reallocations
	std::vector<std::shared_ptr<Window>> m_windows;
	std::unordered_map<std::string, std::function<void(UIComponents, WindowBase *)>> m_handlers;
	std::shared_ptr<HandlerErrorPolicy> m_handler_error_policy;

	struct Buttons {
		Uint8 action_button;
		Uint8 menu_button;
		Uint32 action_button_mask;
		Uint32 menu_button_mask;
	};

	Buttons m_mouse_buttons;

	std::shared_ptr<creation::ITextureFactory> m_factory;
};
}
#endif /* UI_H_ */
