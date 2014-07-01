
#ifndef XMLSERIALIZER_H_
#define XMLSERIALIZER_H_

#include <pugixml/pugixml.hpp>
#include <string>
#include "Serializer.h"

namespace SDL_GUI {

class XMLSerializer : public Serializer {
public:
	virtual ~XMLSerializer();
	XMLSerializer(const std::string &file_name);

	virtual void accept(std::function<void(const Node &)> visitor) override;

private:
	pugi::xml_document doc;
	void accept(std::function<void(const Node &)> visitor, const pugi::xml_node &node);
};



}

#endif /* XMLSERIALIZER_H_ */
