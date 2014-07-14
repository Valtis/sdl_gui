#include "WindowBaseTest.h"

namespace sdl_gui {

WindowBaseTest::WindowBaseTest() {
	// TODO Auto-generated constructor stub

}

WindowBaseTest::~WindowBaseTest() {
	// TODO Auto-generated destructor stub
}

void WindowBaseTest::always_pass() {
	CPPUNIT_ASSERT(42 == 42);
}

void WindowBaseTest::always_fail() {
	CPPUNIT_ASSERT(4 == 5);
}

} /* namespace sdl_gui */
