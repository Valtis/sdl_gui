#ifndef HANDLERMANAGER_H_
#define HANDLERMANAGER_H_
#include <string>

namespace sdl_gui {
class HandlerManager {
public:
	virtual ~HandlerManager() { }
	virtual void call_handler(const std::string &handler_name) = 0;
};

} /* namespace sdl_gui */

#endif /* HANDLERMANAGER_H_ */
