#include "XMLNode.h"

namespace SDL_GUI {

XMLNode::XMLNode(const pugi::xml_node &node) : m_node(node) {

}

XMLNode::~XMLNode() {
}

std::string XMLNode::name() const {
	return m_node.name();
}

std::string XMLNode::value(const std::string &key) const {
	return m_node.attribute(key.c_str()).as_string();

}

} /* namespace SDL_GUI */
