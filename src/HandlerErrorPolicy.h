#ifndef HANDLEREXCEPTIONPOLICY_H_
#define HANDLEREXCEPTIONPOLICY_H_
#include <string>
namespace sdl_gui {

class HandlerErrorPolicy {
public:
	virtual ~HandlerErrorPolicy() { }
	virtual void on_missing_handler(const std::string &handler_name) = 0;
};

} /* namespace sdl_gui */



#endif
