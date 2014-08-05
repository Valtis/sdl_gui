#include "StringUtility.h"
#include <cstring>
#include <iostream>
namespace sdl_gui {
namespace utility {

std::vector<std::string> tokenize(const std::string &text, const char delimiter)
{
	std::vector<std::string> tokens;

	if (text.empty())
	{
		return tokens;
	}

	int begin_pos = 0;
	int end_pos = 0;

	while ((end_pos = text.find(delimiter, begin_pos)) != std::string::npos) {
		std::string token = text.substr(begin_pos, end_pos - begin_pos);

		if (!token.empty()) {
			tokens.push_back(token);
		}
		begin_pos = end_pos+1;
	}

	if (begin_pos != std::string::npos) {
		tokens.push_back(text.substr(begin_pos));
	}

	return tokens;
}

} /* namespace utility */
} /* namespace sdl_gui */
