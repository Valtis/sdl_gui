#ifndef HANDLEREXCEPTIONPOLICY_H_
#define HANDLEREXCEPTIONPOLICY_H_
#include <string>
namespace sdl_gui {

class HandlerExceptionPolicy {
public:
	virtual ~HandlerExceptionPolicy() { }
	virtual void on_missing_handler(const std::string &handler_name) = 0;
};

} /* namespace sdl_gui */



#endif /* HANDLEREXCEPTIONPOLICY_H_ */
