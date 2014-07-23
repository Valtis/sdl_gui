#include "XMLNode.h"

namespace sdl_gui {
namespace serialization {
XMLNode::XMLNode(const pugi::xml_node &node) : m_node(node) {

}

XMLNode::~XMLNode() {
}

std::string XMLNode::name() const {
	return m_node.name();
}

std::unique_ptr<Node> XMLNode::parent() const {
	return std::unique_ptr<Node>(new XMLNode(m_node.parent()));
}

std::string XMLNode::value(const std::string &key) const {
	return m_node.attribute(key.c_str()).as_string();
}



} /* namespace serialization */
} /* namespace SDL_GUI */
