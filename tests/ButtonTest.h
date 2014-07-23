#ifndef BUTTONTEST_H_
#define BUTTONTEST_H_
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../src/components/Button.h"
#include "../src/components/TextLabel.h"
#include "mocks/TestHandlerManager.h"
#include "mocks/TestTextureFactory.h"
#include "mocks/TestRenderer.h"

namespace sdl_gui {

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
    	Button button{};
    	button.set_relative_dimension({40, 40, 100, 100});
		TestHandlerManager manager;

		button.set_handler_manager(&manager);
		std::string handler_name = "my_click_handler";
		button.set_handler(Handler_Type::ON_CLICK, handler_name);
		button.add_child(create_label(80, 60));

		button.on_mouse_up(41, 41);
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler);
    }

    void button_on_click_handler_is_called_when_clicking_on_text() {
      	Button button{};
      	button.set_relative_dimension({40, 40, 100, 100});


      	button.add_child(create_label(80, 60));

      	TestHandlerManager manager;

  		button.set_handler_manager(&manager);
  		std::string handler_name = "my_click_handler";
  		button.set_handler(Handler_Type::ON_CLICK, handler_name);

  		button.on_mouse_up(80, 70);
  		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler);
      }


    std::unique_ptr<TextLabel> create_label(int width, int height) {
    	auto renderer = std::make_shared<TestRenderer>();
		renderer->m_texture_width = width;
		renderer->m_texture_height= height;


		std::unique_ptr<TextLabel> label{new TextLabel{std::shared_ptr<creation::ITextureFactory>{new TestTextureFactory{} }}};
		label->set_renderer(std::static_pointer_cast<rendering::Renderer>(renderer));
		label->set_text("Let there be text!");
		label->set_horizontal_alignment(Text_Alignment::CENTER, 0);
		label->set_vertical_alignment(Text_Alignment::CENTER, 0);
		return label;
    }

};
CPPUNIT_TEST_SUITE_REGISTRATION( ButtonTest);
}



#endif /* BUTTONTEST_H_ */
