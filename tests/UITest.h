#ifndef UITEST_H_
#define UITEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <SDL2/SDL.h>

#include "../src/components/Window.h"
#include "../src/UI.h"

namespace sdl_gui {

class UITest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(UITest);
    CPPUNIT_TEST(window_is_moved_when_dragging);
   // CPPUNIT_TEST(button_on_click_handler_is_called_when_clicking_on_text);
    CPPUNIT_TEST_SUITE_END();

public:
	UITest() { }
	virtual ~UITest() { }

    void setUp(void) {
    	m_event.type = -1;
    }
    void tearDown(void) {}


private:
    SDL_Event m_event;
    void mouse_down_event(Sint32 x, Sint32 y) {
    	m_event.type = SDL_MOUSEBUTTONDOWN;
		m_event.button.button = SDL_BUTTON_LEFT;
		m_event.button.state = SDL_PRESSED;
		m_event.button.x = x;
		m_event.button.y = y;
    }

    void mouse_motion_event(Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel) {

    }

    void window_is_moved_when_dragging() {
    	auto window = std::make_shared<Window>();
    	window->set_relative_dimension({ 40, 50, 120, 140 });

    	UI ui{nullptr};
    	ui.add_window(window);

    	mouse_down_event(60, 60);

    	ui.update(m_event);

    	m_event.type = SDL_MOUSEMOTION;
    	m_event.motion.x = 65;
    	m_event.motion.y = 65;
    	m_event.motion.xrel= 5;
    	m_event.motion.yrel= 5;

    	ui.update(m_event);

    	m_event.type = SDL_MOUSEBUTTONUP;
    	m_event.button.button = SDL_BUTTON_LEFT;
    	m_event.button.state = SDL_RELEASED;
    	m_event.button.x = 65;
    	m_event.button.y = 65;

    	ui.update(m_event);

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window x coordinate has wrong value", 45, window->relative_dimension().x);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window y coordinate has wrong value", 55, window->relative_dimension().y);
    }

    void window_is_not_moved_if_drag_starts_when_cursor_is_not_on_any_window() {

    }

   /* void second_window_is_not_dragged_if_dragging_first_one_and_cursor_on_second() {
    	auto first_window = std::make_shared<Window>();
    	auto second_window = std::make_shared<Window>();

    	first_window->set_relative_dimension({ 40, 50, 120, 140 });
    	second_window->set_relative_dimension({ 300, 400, 200, 400 });

    	first_window->set_handler(HandlerType::ON_DRAG, first_window->)_

    	UI ui{};

    }*/

};


CPPUNIT_TEST_SUITE_REGISTRATION(UITest);

} /* namespace sdl_gui */

#endif /* UITEST_H_ */
