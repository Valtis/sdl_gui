#ifndef XMLNODE_H_
#define XMLNODE_H_

#include "Node.h"
#include <pugixml/pugixml.hpp>

namespace sdl_gui {
namespace serialization {

class XMLNode : public Node {
public:
	XMLNode(const pugi::xml_node &node);
	virtual ~XMLNode();
	virtual std::string name() const override;
	virtual std::string value(const std::string &key) const override;
private:

	pugi::xml_node m_node;
};

} /* namespace serialization */
} /* namespace sdl_gui */

#endif /* XMLNODE_H_ */
