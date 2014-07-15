#include "ThrowHandlerExceptionPolicy.h"
#include <stdexcept>
namespace sdl_gui {

ThrowHandlerExceptionPolicy::ThrowHandlerExceptionPolicy() {
}

ThrowHandlerExceptionPolicy::~ThrowHandlerExceptionPolicy() {
}

void ThrowHandlerExceptionPolicy::on_missing_handler(const std::string &handler_name) {
	throw std::runtime_error("Called for missing handler " + handler_name);
}

} /* namespace sdl_gui */
