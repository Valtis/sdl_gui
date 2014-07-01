#ifndef SERIALIZER_H_
#define SERIALIZER_H_
#include "Node.h"
#include <string>
#include <memory>
#include <functional>

namespace SDL_GUI {

class Serializer {
public:

	virtual ~Serializer();
	virtual void accept(std::function<void(const Node &)> visitor) = 0;
};

}




#endif /* SERIALIZER_H_ */
