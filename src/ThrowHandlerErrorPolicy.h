#ifndef THROWHANDLEREXCEPTIONPOLICY_H_
#define THROWHANDLEREXCEPTIONPOLICY_H_
#include "HandlerErrorPolicy.h"
namespace sdl_gui {

class ThrowHandlerErrorPolicy : public HandlerErrorPolicy {
public:
	ThrowHandlerErrorPolicy();
	virtual ~ThrowHandlerErrorPolicy();

	void on_missing_handler(const std::string &handler_name) override;

};

} /* namespace sdl_gui */

#endif
