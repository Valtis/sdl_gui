#ifndef CREATIONFAILUREEXCEPTION_H
#define CREATIONFAILUREEXCEPTION_H

namespace sdl_gui {
namespace creation {

class CreationFailureException : public std::runtime_error {
public:
	CreationFailureException(const char *msg) : std::runtime_error(msg) {

	}

	CreationFailureException(const std::string &msg) : CreationFailureException(msg.c_str()) {

	}

private:
};

}
}



#endif /* CREATIONFAILUREEXCEPTION_H */
