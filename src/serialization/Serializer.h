#ifndef SERIALIZER_H_
#define SERIALIZER_H_
#include "Node.h"
#include <string>
#include <memory>
#include <functional>

namespace sdl_gui {
namespace serialization {
class Serializer {
public:

	virtual ~Serializer();
	virtual void accept(std::function<void(const Node &)> visitor) = 0;
};

} /* namespace serialization */
} /* namespace sdl_gui */




#endif /* SERIALIZER_H_ */
