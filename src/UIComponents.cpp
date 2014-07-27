#include "UIComponents.h"

namespace sdl_gui {

UIComponents::UIComponents(const std::string &default_window, const std::vector<std::shared_ptr<Window>> &windows) :
	m_default_window(default_window) {
	for (const auto &window : windows) {
		m_windows[window->get_name()] = window;
	}
}

UIComponents::~UIComponents() {

}

} /* namespace sdl_gui */
