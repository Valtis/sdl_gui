
#ifndef XMLSERIALIZER_H_
#define XMLSERIALIZER_H_

#include <pugixml/pugixml.hpp>
#include <string>
#include "Serializer.h"

namespace sdl_gui {
namespace serialization {
class XMLSerializer : public Serializer {
public:
	virtual ~XMLSerializer();
	XMLSerializer(const std::string &file_name);

	virtual void accept(std::function<void(const Node &)> visitor) override;

private:
	pugi::xml_document doc;
	void accept(std::function<void(const Node &)> visitor, const pugi::xml_node &node);
};


} /* namespace serialization */
} /* namespace sdl_gui */

#endif /* XMLSERIALIZER_H_ */
