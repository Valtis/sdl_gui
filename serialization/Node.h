#include <string>
#ifndef NODE_H_
#define NODE_H_
namespace SDL_GUI {

class Node {
public:
	virtual ~Node() { }

	virtual std::string name() = 0;
};

}


#endif /* NODE_H_ */
