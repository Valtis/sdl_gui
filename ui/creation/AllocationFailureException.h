/*
 * AllocationFailureException.h
 *
 *  Created on: 2.7.2014
 *      Author: valtis
 */

#ifndef ALLOCATIONFAILUREEXCEPTION_H_
#define ALLOCATIONFAILUREEXCEPTION_H_

namespace SDL_GUI {
namespace creation {

class AllocationFailureException : public std::runtime_error {
public:
	AllocationFailureException(const char *msg) : std::runtime_error(msg) {

	}

	AllocationFailureException(const std::string &msg) : AllocationFailureException(msg.c_str()) {

	}

private:
};

}
}



#endif /* ALLOCATIONFAILUREEXCEPTION_H_ */
