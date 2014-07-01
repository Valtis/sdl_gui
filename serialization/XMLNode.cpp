/*
 * XMLNode.cpp
 *
 *  Created on: 29.6.2014
 *      Author: valtis
 */

#include "XMLNode.h"

namespace SDL_GUI {

XMLNode::XMLNode(const pugi::xml_node &node) : m_node(node) {

}

XMLNode::~XMLNode() {
}

std::string XMLNode::name() {
	return "";
}

} /* namespace SDL_GUI */
