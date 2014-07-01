/*
 * XMLNode.h
 *
 *  Created on: 29.6.2014
 *      Author: valtis
 */

#ifndef XMLNODE_H_
#define XMLNODE_H_

#include "Node.h"
#include <pugixml/pugixml.hpp>

namespace SDL_GUI {

class XMLNode : public Node {
public:
	XMLNode(const pugi::xml_node &node);
	virtual ~XMLNode();
	virtual std::string name() const override;
private:

	pugi::xml_node m_node;
};


}

#endif /* XMLNODE_H_ */
