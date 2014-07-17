#ifndef THROWHANDLEREXCEPTIONPOLICY_H_
#define THROWHANDLEREXCEPTIONPOLICY_H_
#include "HandlerExceptionPolicy.h"
namespace sdl_gui {

class ThrowHandlerExceptionPolicy : public HandlerExceptionPolicy {
public:
	ThrowHandlerExceptionPolicy();
	virtual ~ThrowHandlerExceptionPolicy();

	void on_missing_handler(const std::string &handler_name) override;

};

} /* namespace sdl_gui */

#endif /* THROWHANDLEREXCEPTIONPOLICY_H_ */
