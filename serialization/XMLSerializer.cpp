#include "XMLSerializer.h"
#include "ParseException.h"
#include "XMLNode.h"
#include <sstream>
namespace sdl_gui {

XMLSerializer::XMLSerializer(const std::string &file_name) {
	auto result = doc.load_file(file_name.c_str());
	if (!result) {
		std::stringstream str;
		str << "An error was encountered while parsing xml file:\n";
		str << "Error description: " << result.description() << "\n";
		str << "Error offset: " << result.offset << "\n";

		throw ParseException(str.str());
	}
}

XMLSerializer::~XMLSerializer() {

}

void XMLSerializer::accept(std::function<void(const Node &)> visitor)
{
	for (const auto &child : doc.children()) {
		accept(visitor, child);
	}
}

void XMLSerializer::accept(std::function<void(const Node &)> visitor, const pugi::xml_node &node) {
	XMLNode xmlnode{node};
	visitor(xmlnode);

	for (const auto &child : node.children()) {
		accept(visitor, child);
	}
}


} /* namespace SDL_GUI */
