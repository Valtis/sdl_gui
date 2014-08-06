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
    CPPUNIT_TEST(button_on_mouse_hover_handler_is_called_when_not_hovering_over_text);
    CPPUNIT_TEST(button_on_mouse_over_handler_is_called_when_hovering_over_text);
    CPPUNIT_TEST(button_on_mouse_exit_handler_is_called_when_exiting_button);
    CPPUNIT_TEST(button_on_mouse_down_is_called_when_clicking_on_button);
    CPPUNIT_TEST(button_on_mouse_down_is_called_when_clicking_on_child);

    CPPUNIT_TEST(button_is_drawn_with_default_state);
    CPPUNIT_TEST(button_is_drawn_with_pushed_down_state);
    CPPUNIT_TEST(button_is_drawn_with_hover_over_state);

    CPPUNIT_TEST(get_text_returns_empty_string_if_no_label_is_set);
    CPPUNIT_TEST(get_text_returns_label_text);

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
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler.at(0));
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
  		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler.at(0));
    }

    void button_on_mouse_down_is_called_when_clicking_on_button() {
    	Button button{};
		button.set_relative_dimension({40, 40, 100, 100});
		button.add_child(create_label(80, 60));

		TestHandlerManager manager;

		button.set_handler_manager(&manager);
		std::string handler_name = "my_on_mouse_down_handler";
		button.set_handler(Handler_Type::ON_MOUSE_DOWN, handler_name);

		button.on_mouse_down(41, 41);
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler.at(0));
    }

    void button_on_mouse_down_is_called_when_clicking_on_child() {
    	Button button{};
		button.set_relative_dimension({40, 40, 100, 100});


		button.add_child(create_label(80, 60));

		TestHandlerManager manager;

		button.set_handler_manager(&manager);
		std::string handler_name = "my_on_mouse_down_handler";
		button.set_handler(Handler_Type::ON_MOUSE_DOWN, handler_name);

		button.on_mouse_down(80, 70);
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler.at(0));
    }

    void button_on_mouse_hover_handler_is_called_when_not_hovering_over_text() {
    	Button button{};
    	button.set_relative_dimension({40, 40, 100, 100});
		TestHandlerManager manager;

		button.set_handler_manager(&manager);
		std::string handler_name = "my_hover_manager";
		button.set_handler(Handler_Type::ON_MOUSE_OVER, handler_name);
		button.add_child(create_label(80, 60));

		button.on_mouse_over(41, 41);
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler.at(0));
    }



    void button_on_mouse_over_handler_is_called_when_hovering_over_text() {
		Button button{};
		button.set_relative_dimension({40, 40, 100, 100});
		button.add_child(create_label(80, 60));

		TestHandlerManager manager;

		button.set_handler_manager(&manager);
		std::string handler_name = "my_hover_manager";
		button.set_handler(Handler_Type::ON_MOUSE_OVER, handler_name);

		button.on_mouse_over(80, 70);
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler.at(0));
    }

    void button_on_mouse_exit_handler_is_called_when_exiting_button() {
		Button button{};
		button.set_relative_dimension({40, 40, 100, 100});
		button.add_child(create_label(80, 60));

		TestHandlerManager manager;

		button.set_handler_manager(&manager);
		std::string handler_name = "poasdeijpf";
		button.set_handler(Handler_Type::ON_MOUSE_EXIT, handler_name);

		button.on_mouse_exit(79, 70);
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler.at(0));
    }

    void button_is_drawn_with_default_state() {
    	Button button{};
    	auto renderer = std::make_shared<TestRenderer>();
    	button.set_renderer(renderer.get());

    	button.draw();

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Source rectangle was not set", true, renderer->m_source_is_set);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination rectangle was not set", true, renderer->m_destination_is_set);
    }

    void button_is_drawn_with_pushed_down_state() {
        	Button button{};
        	auto renderer = std::make_shared<TestRenderer>();
        	button.set_renderer(renderer.get());
        	button.set_relative_dimension({0, 0, 100, 100});
        	button.on_mouse_down(10, 10);
        	button.draw();

        	CPPUNIT_ASSERT_EQUAL_MESSAGE("Source rectangle was not set", true, renderer->m_source_is_set);
        	CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination rectangle was not set", true, renderer->m_destination_is_set);
     }

     void button_is_drawn_with_hover_over_state() {
           	Button button{};
           	auto renderer = std::make_shared<TestRenderer>();
           	button.set_renderer(renderer.get());
           	button.set_relative_dimension({0, 0, 100, 100});
           	button.on_mouse_over(10, 10);
           	button.draw();

           	CPPUNIT_ASSERT_EQUAL_MESSAGE("Source rectangle was not set", true, renderer->m_source_is_set);
           	CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination rectangle was not set", true, renderer->m_destination_is_set);
    }

    void get_text_returns_empty_string_if_no_label_is_set() {
    	Button button{};
    	CPPUNIT_ASSERT_MESSAGE("Empty string expected if button has no text label", button.get_text().empty());
    }

    void get_text_returns_label_text() {
    	Button button{};

    	auto label = create_label(10, 10);
    	button.add_child(std::move(label));

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("get_text excepted to return label text", std::string("Let there be text!"), button.get_text());
    }

    std::unique_ptr<TextLabel> create_label(int width, int height) {
    		auto renderer = std::make_shared<TestRenderer>();

        	renderer->m_texture_width = width;
    		renderer->m_texture_height= height;

    		std::unique_ptr<TextLabel> label{new TextLabel{std::shared_ptr<creation::ITextureFactory>{new TestTextureFactory{} }}};
    		label->set_renderer(renderer.get());
    		label->set_text("Let there be text!");
    		label->set_horizontal_alignment(Text_HAlignment::CENTER, 0);
    		label->set_vertical_alignment(Text_VAlignment::CENTER, 0);
    		return label;
	}

};
CPPUNIT_TEST_SUITE_REGISTRATION( ButtonTest);
}



#endif /* BUTTONTEST_H_ */
