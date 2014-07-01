#include "XMLNode.h"

namespace SDL_GUI {

XMLNode::XMLNode(const pugi::xml_node &node) : m_node(node) {

}

XMLNode::~XMLNode() {
}

std::string XMLNode::name() const {
	return m_node.name();
}

} /* namespace SDL_GUI */
