#ifndef UICOMPONENTS_H_
#define UICOMPONENTS_H_
#include <unordered_map>
#include <string>
#include "components/Window.h"

namespace sdl_gui {

// allows querying for UI components from handler functions
class UIComponents {
public:
	UIComponents(const std::string &default_window, const std::vector<std::shared_ptr<Window>> &windows);
	virtual ~UIComponents();

	template <typename T>
	T get_by_name(const std::string &component_name) {
		return dynamic_cast<T>(m_windows[m_default_window]->get_child_by_name(component_name));
	}

	template <typename T>
	T get_by_name(const std::string &component_name, const std::string &window_name) {
		return dynamic_cast<T>(m_windows[window_name]->get_child_by_name(component_name));
	}

private:
	std::string m_default_window;
	std::unordered_map<std::string, std::shared_ptr<Window>> m_windows;
};

} /* namespace sdl_gui */

#endif /* UICOMPONENTS_H_ */
