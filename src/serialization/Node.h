#ifndef NODE_H_
#define NODE_H_
#include <string>
#include <memory>
namespace sdl_gui {
namespace serialization {

class Node {
public:
	virtual ~Node() { }

	virtual std::string name() const = 0;
	virtual std::unique_ptr<Node> parent() const = 0;
	virtual std::string value(const std::string &key) const = 0;
};

} /* namespace serialization */
} /* namespace sdl_gui */


#endif /* NODE_H_ */
