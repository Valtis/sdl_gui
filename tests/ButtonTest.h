#ifndef BUTTONTEST_H_
#define BUTTONTEST_H_
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../src/components/Button.h"

namespace sdl_gui {

class ButtonTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ButtonTest);

    CPPUNIT_TEST_SUITE_END();

public:
	ButtonTest() { }
	virtual ~ButtonTest() { }

    void setUp(void) {}
    void tearDown(void) {}

private:
    void button_handler_is_called_on_click() {
    	Button button{};
    	button.set_relative_dimension({40, 40, 100, 100});
		TestHandlerManager manager;

		button.set_handler_manager(&manager);
		std::string handler_name = "my_click_handler";
		button.set_handler(HandlerType::ON_CLICK, handler_name);

		button.on_mouse_up(60, 60);
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler);
    }

};
CPPUNIT_TEST_SUITE_REGISTRATION( ButtonTest);
}



#endif /* BUTTONTEST_H_ */
