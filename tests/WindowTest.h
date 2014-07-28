#ifndef WINDOWTEST_H_
#define WINDOWTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


#include "../src/rendering/Renderer.h"
#include "../src/components/Window.h"
#include "../src/components/Button.h"
#include "mocks/TestTextureFactory.h"
#include "mocks/TestRenderer.h"

namespace sdl_gui {

class WindowTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(WindowTest);
    CPPUNIT_TEST(drag_that_starts_on_child_window_does_not_drag_actual_window_if_cursor_moves_outside_child_region);
    CPPUNIT_TEST(window_position_is_changed_on_drag_that_follows_child_window_drag);
    CPPUNIT_TEST(window_does_not_draw_overlay_when_it_has_focus);
    CPPUNIT_TEST(window_draws_overlay_when_it_has_no_focus);
    CPPUNIT_TEST_SUITE_END();

public:
    WindowTest() { }
	virtual ~WindowTest() { }

    void setUp(void) {}
    void tearDown(void) {}

private:
    void drag_that_starts_on_child_window_does_not_drag_actual_window_if_cursor_moves_outside_child_region() {

    	Window window;
    	window.set_relative_dimension({ 40, 50, 300, 400 });
    	std::unique_ptr<Button> button{new Button{}};
    	button->set_relative_dimension({ 10, 10, 120, 120 });

    	window.add_child(std::move(button));

    	// start dragging at button
    	window.on_drag(60, 80, 1, 1);
    	// then drag from the actual window
    	window.on_drag(42, 52, 1, 1);

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window x coordinate has changed", 40, window.absolute_dimension().x);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window y coordinate has changed", 50, window.absolute_dimension().y);
    }

    void window_position_is_changed_on_drag_that_follows_child_window_drag() {

    	Window window;
    	window.set_relative_dimension({ 40, 50, 300, 400 });
    	std::unique_ptr<Button> button{new Button{}};
    	button->set_relative_dimension({ 10, 10, 120, 120 });

    	window.add_child(std::move(button));

    	// start dragging at button
    	window.on_drag(60, 80, 1, 1);

    	// mouse cursor is released
    	window.on_mouse_up(61, 81);

    	// then drag from the actual window
    	window.on_drag(42, 52, 1, 1);

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window x coordinate has not changed", 41, window.absolute_dimension().x);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Window y coordinate has not changed", 51, window.absolute_dimension().y);
    }

    void window_does_not_draw_overlay_when_it_has_focus() {
    	Window window;
    	int count = 0;
    	auto renderer = std::make_shared<TestRenderer>();

    	renderer->m_on_draw = [&]() {
    		++count;
    	};

    	window.set_renderer(renderer.get());
    	window.on_gaining_focus();
    	window.draw();

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Wrong number of calls for Renderer::Draw", 1, count);
    }


    void window_draws_overlay_when_it_has_no_focus() {
    	Window window;
    	int count = 0;
    	auto renderer = std::make_shared<TestRenderer>();

    	renderer->m_on_draw = [&]() {
    		++count;
    	};

    	window.set_renderer(renderer.get());
    	window.on_losing_focus();
    	window.draw();

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Wrong number of calls for Renderer::Draw", 2, count);
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( WindowTest);
}





#endif /* WINDOWTEST_H_ */
