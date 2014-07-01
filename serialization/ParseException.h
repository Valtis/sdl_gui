
#ifndef PARSEEXCEPTION_H_
#define PARSEEXCEPTION_H_
#include <stdexcept>
#include <string>

namespace SDL_GUI {
class ParseException : public std::exception {
public:
	ParseException(const char *msg) : m_msg(msg) {

	}

	ParseException(const std::string &msg) : m_msg(msg) {

	}

	const char *what() const noexcept override {
		return m_msg.c_str();
	}

private:
	std::string m_msg;
};

}


#endif /* PARSEEXCEPTION_H_ */
