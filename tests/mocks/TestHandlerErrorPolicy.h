#ifndef TESTHANDLERERRORPOLICY_H_
#define TESTHANDLERERRORPOLICY_H_
#include "../../src/HandlerErrorPolicy.h"
#include <functional>

namespace sdl_gui {

class TestHandlerErrorPolicy : public HandlerErrorPolicy {
public:
	std::function<void(const std::string &)> m_on_missing_handler;

	void on_missing_handler(const std::string &handler_name) override {
		m_on_missing_handler(handler_name);
	}
};


} /* namespace sdl_gui */

#endif /* TESTHANDLERERRORPOLICY_H_ */
