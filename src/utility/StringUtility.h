#ifndef STRINGUTILITY_H_
#define STRINGUTILITY_H_

#include <vector>
#include <string>

namespace sdl_gui {
namespace utility {

	std::vector<std::string> tokenize(const std::string &text, const char delimiter);

} /* namespace utility */
} /* namespace sdl_gui*/

#endif /* STRINGUTILITY_H_ */
