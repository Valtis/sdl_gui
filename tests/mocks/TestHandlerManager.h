#ifndef TESTHANDLERMANAGER_H_
#define TESTHANDLERMANAGER_H_
#include <vector>
#include "../../src/HandlerManager.h"
namespace sdl_gui {



class TestHandlerManager : public HandlerManager {
public:
	std::vector<std::string> m_called_handler;
	void call_handler(const std::string &handler_name) {
		m_called_handler.push_back(handler_name);
	}
};

} /* namespace sdl_gui */

#endif /* TESTHANDLERMANAGER_H_ */
