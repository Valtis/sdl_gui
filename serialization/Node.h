#include <string>
#ifndef NODE_H_
#define NODE_H_
namespace sdl_gui {

class Node {
public:
	virtual ~Node() { }

	virtual std::string name() const = 0;
	virtual std::string value(const std::string &key) const = 0;
};

}


#endif /* NODE_H_ */
