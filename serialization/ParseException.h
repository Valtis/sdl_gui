
#ifndef PARSEEXCEPTION_H_
#define PARSEEXCEPTION_H_
#include <stdexcept>
#include <string>

namespace sdl_gui {
class ParseException : public std::runtime_error {
public:
	ParseException(const char *msg) : std::runtime_error(msg) {

	}

	ParseException(const std::string &msg) : ParseException(msg.c_str()) {

	}

private:
};

}


#endif /* PARSEEXCEPTION_H_ */
