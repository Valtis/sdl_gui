#ifndef UITEST_H_
#define UITEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <SDL2/SDL.h>

#include "../src/components/Window.h"
#include "../src/components/Button.h"
#include "../src/UI.h"

#include "mocks/TestHandlerErrorPolicy.h"

namespace sdl_gui {

class UITest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(UITest);
    CPPUNIT_TEST(window_is_moved_when_dragging_with_left_button_and_right_handed_profile);
    CPPUNIT_TEST(window_is_not_moved_with_right_button_and_right_handed_profile);
    CPPUNIT_TEST(window_is_moved_when_dragging_with_right_button_and_left_handed_profile);
    CPPUNIT_TEST(window_is_not_moved_with_left_button_and_left_handed_profile);

    CPPUNIT_TEST(window_is_not_moved_if_drag_starts_when_cursor_is_not_on_any_window);
    CPPUNIT_TEST(second_window_is_not_dragged_if_dragging_first_one_and_cursor_moves_on_second);
    CPPUNIT_TEST(second_window_is_dragged_if_dragging_first_one_but_button_is_released_before_new_drag_with_right_handed_profile);
    CPPUNIT_TEST(second_window_is_dragged_if_dragging_first_one_but_button_is_released_before_new_drag_with_left_handed_profile);
    CPPUNIT_TEST(window_position_is_changed_on_drag_if_first_dragging_on_child_and_drag_is_terminated_outside_window_area);

    CPPUNIT_TEST(window_on_mouse_down_handler_is_called_on_mouse_down_event_with_right_handed_profile);
    CPPUNIT_TEST(window_on_mouse_down_handler_is_called_on_mouse_down_event_with_left_handed_profile);

    CPPUNIT_TEST(window_on_mouse_up_handler_is_called_on_mouse_up_event_with_right_handed_profile);
    CPPUNIT_TEST(window_on_mouse_up_handler_is_called_on_mouse_up_event_with_left_handed_profile);

    CPPUNIT_TEST(ui_uses_handler_error_policy);

    CPPUNIT_TEST_SUITE_END();

public:
	UITest() { }
	virtual ~UITest() { }

    void setUp(void) {}
    void tearDown(void) {}


private:

    SDL_Event mouse_up_event(Sint32 x, Sint32 y, Uint8 button) {
    	SDL_Event event;
    	event.type = SDL_MOUSEBUTTONUP;
		event.button.button = button;
		event.button.state = SDL_RELEASED;
		event.button.x = x;
		event.button.y = y;
		return event;
    }

    SDL_Event mouse_down_event(Sint32 x, Sint32 y, Uint8 button) {
    	SDL_Event event;
    	event.type = SDL_MOUSEBUTTONDOWN;
		event.button.button = button;
		event.button.state = SDL_PRESSED;
		event.button.x = x;
		event.button.y = y;
		return event;
    }

    SDL_Event mouse_motion_event(Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel, Uint32 mask) {
       	SDL_Event event;
    	event.type = SDL_MOUSEMOTION;
       	event.motion.state = mask;
		event.motion.x = x;
		event.motion.y = y;
		event.motion.xrel= xrel;
		event.motion.yrel= yrel;
		return event;
    }

    void window_is_moved_when_dragging_with_left_button_and_right_handed_profile() {
    	auto window = std::make_shared<Window>();
    	window->set_relative_dimension({ 40, 50, 120, 140 });

    	UI ui{nullptr};
    	ui.add_window(window);

    	ui.update(mouse_motion_event(65, 62, 5, 2, SDL_BUTTON_LMASK));

    	ui.update(mouse_up_event(65, 65, SDL_BUTTON_LEFT));

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window x coordinate has not changed correctly", 45, window->absolute_dimension().x);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window y coordinate has not changed correctly", 52, window->absolute_dimension().y);
    }

    void window_is_not_moved_with_right_button_and_right_handed_profile() {
    	auto window = std::make_shared<Window>();
    	window->set_relative_dimension({ 40, 50, 120, 140 });

    	UI ui{nullptr};
    	ui.add_window(window);

    	ui.update(mouse_motion_event(65, 62, 5, 2, SDL_BUTTON_RMASK));

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window x coordinate has changed", 40, window->absolute_dimension().x);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window y coordinate has changed", 50, window->absolute_dimension().y);
    }

    void window_is_moved_when_dragging_with_right_button_and_left_handed_profile() {
    	auto window = std::make_shared<Window>();
    	window->set_relative_dimension({ 40, 50, 120, 140 });

    	UI ui{nullptr};
    	ui.set_handedness(Handedness::LEFT);
    	ui.add_window(window);

    	ui.update(mouse_motion_event(65, 62, -3, -2, SDL_BUTTON_RMASK));

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window x coordinate has not changed correctly", 37, window->absolute_dimension().x);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window y coordinate has not changed correctly", 48, window->absolute_dimension().y);
    }

    void window_is_not_moved_with_left_button_and_left_handed_profile() {
    	auto window = std::make_shared<Window>();
    	window->set_relative_dimension({ 40, 50, 120, 140 });

    	UI ui{nullptr};
    	ui.set_handedness(Handedness::LEFT);
    	ui.add_window(window);
    	ui.update(mouse_motion_event(65, 62, 5, 2, SDL_BUTTON_LMASK));

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window x coordinate has changed", 40, window->absolute_dimension().x);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window y coordinate has changed", 50, window->absolute_dimension().y);
    }

    void window_is_not_moved_if_drag_starts_when_cursor_is_not_on_any_window() {
    	auto window = std::make_shared<Window>();
    	window->set_relative_dimension({ 40, 50, 120, 140 });

    	UI ui{nullptr};
    	ui.add_window(window);

    	ui.update(mouse_motion_event(30, 30, 2, 2, SDL_BUTTON_LMASK));
    	ui.update(mouse_motion_event(40, 40, 8, 8, SDL_BUTTON_LMASK));
    	ui.update(mouse_motion_event(45, 45, 5, 5, SDL_BUTTON_LMASK));
    	ui.update(mouse_motion_event(41, 41, -4, -4, SDL_BUTTON_LMASK));

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window x coordinate has changed", 40, window->absolute_dimension().x);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window y coordinate has changed", 50, window->absolute_dimension().y);
    }

    void second_window_is_not_dragged_if_dragging_first_one_and_cursor_moves_on_second() {
    	auto first_window = std::make_shared<Window>();
    	auto second_window = std::make_shared<Window>();

    	first_window->set_relative_dimension({ 40, 50, 120, 140 });
    	second_window->set_relative_dimension({ 300, 400, 200, 400 });

    	UI ui{nullptr};

    	ui.add_window(first_window);
    	ui.add_window(second_window);

    	ui.update(mouse_motion_event(60, 60, 3, 3, SDL_BUTTON_LMASK));
    	ui.update(mouse_motion_event(305, 405, 3, 3, SDL_BUTTON_LMASK));

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Second window x coordinate has changed", 300, second_window->absolute_dimension().x);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Second window y coordinate has changed", 400, second_window->absolute_dimension().y);
    }

    void second_window_is_dragged_if_dragging_first_one_but_button_is_released_before_new_drag_with_right_handed_profile() {
        	auto first_window = std::make_shared<Window>();
        	auto second_window = std::make_shared<Window>();

        	first_window->set_relative_dimension({ 40, 50, 120, 140 });
        	second_window->set_relative_dimension({ 300, 400, 200, 400 });

        	UI ui{nullptr};
        	ui.add_window(first_window);
        	ui.add_window(second_window);

        	ui.update(mouse_motion_event(60, 60, 3, 3, SDL_BUTTON_LMASK));
        	ui.update(mouse_up_event(63, 63, SDL_BUTTON_LEFT));
        	ui.update(mouse_motion_event(405, 505, 3, -4, SDL_BUTTON_LMASK));

        	CPPUNIT_ASSERT_EQUAL_MESSAGE("First window x coordinate has not changed correctly", 43, first_window->absolute_dimension().x);
        	CPPUNIT_ASSERT_EQUAL_MESSAGE("First window y coordinate has not changed correctly", 53, first_window->absolute_dimension().y);

        	CPPUNIT_ASSERT_EQUAL_MESSAGE("Second window x coordinate has not changed correctly", 303, second_window->absolute_dimension().x);
        	CPPUNIT_ASSERT_EQUAL_MESSAGE("Second window y coordinate has not changed correctly", 396, second_window->absolute_dimension().y);
     }

    void second_window_is_dragged_if_dragging_first_one_but_button_is_released_before_new_drag_with_left_handed_profile() {
        	auto first_window = std::make_shared<Window>();
        	auto second_window = std::make_shared<Window>();

        	first_window->set_relative_dimension({ 40, 50, 120, 140 });
        	second_window->set_relative_dimension({ 300, 400, 200, 400 });

        	UI ui{nullptr};
        	ui.set_handedness(Handedness::LEFT);
        	ui.add_window(first_window);
        	ui.add_window(second_window);

        	ui.update(mouse_motion_event(60, 60, 3, 3, SDL_BUTTON_RMASK));
        	ui.update(mouse_up_event(63, 63, SDL_BUTTON_LEFT));
        	ui.update(mouse_motion_event(405, 505, 3, -4, SDL_BUTTON_RMASK));

        	CPPUNIT_ASSERT_EQUAL_MESSAGE("First window x coordinate has not changed correctly", 43, first_window->absolute_dimension().x);
        	CPPUNIT_ASSERT_EQUAL_MESSAGE("First window y coordinate has not changed correctly", 53, first_window->absolute_dimension().y);

        	CPPUNIT_ASSERT_EQUAL_MESSAGE("Second window x coordinate has not changed correctly", 303, second_window->absolute_dimension().x);
        	CPPUNIT_ASSERT_EQUAL_MESSAGE("Second window y coordinate has not changed correctly", 396, second_window->absolute_dimension().y);
     }


    void window_position_is_changed_on_drag_if_first_dragging_on_child_and_drag_is_terminated_outside_window_area() {
    	auto window = std::make_shared<Window>();
    	window->set_relative_dimension({ 40, 50, 120, 140 });

		std::unique_ptr<Button> button{new Button{}};
		button->set_relative_dimension({ 10, 10, 120, 120 });

		window->add_child(std::move(button));

		UI ui{nullptr};
		ui.add_window(window);

		ui.update(mouse_motion_event(70, 70, 3, 3, SDL_BUTTON_LMASK));
		ui.update(mouse_up_event(0, 0, SDL_BUTTON_LEFT));
		ui.update(mouse_motion_event(41, 51, 3, -4, SDL_BUTTON_LMASK));

		CPPUNIT_ASSERT_EQUAL_MESSAGE("Window x coordinate has not changed correctly", 43, window->absolute_dimension().x);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Window y coordinate has not changed correctly", 46, window->absolute_dimension().y);
    }


    void window_on_mouse_down_handler_is_called_on_mouse_down_event_with_right_handed_profile() {
    	bool is_called = false;
    	auto ui = set_up_ui_for_handler_test(Handler_Type::ON_MOUSE_DOWN, is_called);
		ui.update(mouse_down_event( 50, 60, SDL_BUTTON_LEFT));

		CPPUNIT_ASSERT_MESSAGE("Window on_mouse_down handler was not called", is_called);
    }

    void window_on_mouse_down_handler_is_called_on_mouse_down_event_with_left_handed_profile() {
    	bool is_called = false;
    	auto ui = set_up_ui_for_handler_test(Handler_Type::ON_MOUSE_DOWN, is_called);
    	ui.set_handedness(Handedness::LEFT);
    	ui.update(mouse_down_event( 50, 60, SDL_BUTTON_RIGHT));

		CPPUNIT_ASSERT_MESSAGE("Window on_mouse_down handler was not called", is_called);
    }

    void window_on_mouse_up_handler_is_called_on_mouse_up_event_with_right_handed_profile() {
    	bool is_called = false;
      	auto ui = set_up_ui_for_handler_test(Handler_Type::ON_CLICK, is_called);
  		ui.update(mouse_up_event( 50, 60, SDL_BUTTON_LEFT));

  		CPPUNIT_ASSERT_MESSAGE("Window on_mouse_down handler was not called", is_called);
    }

    void window_on_mouse_up_handler_is_called_on_mouse_up_event_with_left_handed_profile() {
    	  bool is_called = false;
    	  auto ui = set_up_ui_for_handler_test(Handler_Type::ON_CLICK, is_called);
    	  ui.set_handedness(Handedness::LEFT);
    	  ui.update(mouse_up_event( 50, 60, SDL_BUTTON_RIGHT));
    	  CPPUNIT_ASSERT_MESSAGE("Window on_mouse_down handler was not called", is_called);
    }


    void ui_uses_handler_error_policy() {

    	UI ui{nullptr};
    	std::unique_ptr<TestHandlerErrorPolicy> policy{new TestHandlerErrorPolicy{}};
    	std::string missing_handler_name;

    	policy->m_on_missing_handler = [&](const std::string &name) { missing_handler_name = name; };
    	ui.set_handler_error_policy(std::move(policy));

    	auto window = std::make_shared<Window>();
    	window->set_relative_dimension({ 40, 50, 120, 140 });
    	std::string handler_name = "handler";
    	window->set_handler(Handler_Type::ON_CLICK, handler_name);
    	ui.add_window(window);

    	ui.update(mouse_up_event( 50, 60, SDL_BUTTON_LEFT));

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Error handler was not invoked", handler_name, missing_handler_name);
    }

    UI set_up_ui_for_handler_test(Handler_Type type, bool &is_called) {
    	auto window = std::make_shared<Window>();
		window->set_relative_dimension({ 40, 50, 120, 140 });

		std::string handler_name = "handler";
		window->set_handler(type, handler_name);

		UI ui{nullptr};
		ui.add_window(window);
		ui.register_handler(handler_name, [&]() { is_called = true; });
		return ui;
    }


};


CPPUNIT_TEST_SUITE_REGISTRATION(UITest);

} /* namespace sdl_gui */

#endif /* UITEST_H_ */
