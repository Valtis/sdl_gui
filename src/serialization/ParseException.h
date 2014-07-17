
#ifndef PARSEEXCEPTION_H_
#define PARSEEXCEPTION_H_
#include <stdexcept>
#include <string>

namespace sdl_gui {
namespace serialization {
class ParseException : public std::runtime_error {
public:
	ParseException(const char *msg) : std::runtime_error(msg) {

	}

	ParseException(const std::string &msg) : ParseException(msg.c_str()) {

	}

private:
};
} /* namespace serialization */
} /* namespace sdl_gui */


#endif /* PARSEEXCEPTION_H_ */
