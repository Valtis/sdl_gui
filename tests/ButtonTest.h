#ifndef BUTTONTEST_H_
#define BUTTONTEST_H_
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../src/components/Button.h"
#include "../src/creation/ITextureFactory.h"

namespace sdl_gui {

class TestFactory : public creation::ITextureFactory {
public:
	virtual texture_ptr create_window(const int width, const int height, const SDL_Color &color) {
		return texture_ptr{ nullptr, SDL_DestroyTexture };
	}

	virtual texture_ptr create_button(const int width, const int height, const SDL_Color &color) {
		return texture_ptr{ nullptr, SDL_DestroyTexture };
	}

	virtual texture_ptr create_text(std::string text) {
		return texture_ptr{ nullptr, SDL_DestroyTexture };
	}
};

class ButtonTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ButtonTest);
    CPPUNIT_TEST(button_on_click_handler_is_called_when_not_clicking_on_text);
    CPPUNIT_TEST(button_on_click_handler_is_called_when_clicking_on_text);
    CPPUNIT_TEST_SUITE_END();

public:
	ButtonTest() { }
	virtual ~ButtonTest() { }

    void setUp(void) {}
    void tearDown(void) {}

private:
    void button_on_click_handler_is_called_when_not_clicking_on_text() {
    	Button button{std::shared_ptr<creation::ITextureFactory>{new TestFactory{} }, "Let there be text!"};
    	button.set_relative_dimension({40, 40, 100, 100});
		TestHandlerManager manager;

		button.set_handler_manager(&manager);
		std::string handler_name = "my_click_handler";
		button.set_handler(HandlerType::ON_CLICK, handler_name);

		button.on_mouse_up(41, 41);
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler);
    }

    void button_on_click_handler_is_called_when_clicking_on_text() {
      	Button button{std::shared_ptr<creation::ITextureFactory>{new TestFactory{} }, "Let there be text!"};
      	button.set_relative_dimension({40, 40, 100, 100});
  		TestHandlerManager manager;

  		button.set_handler_manager(&manager);
  		std::string handler_name = "my_click_handler";
  		button.set_handler(HandlerType::ON_CLICK, handler_name);

  		button.on_mouse_up((100 - 40)/2, (100-40)/2);
  		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler);
      }

};
CPPUNIT_TEST_SUITE_REGISTRATION( ButtonTest);
}



#endif /* BUTTONTEST_H_ */
