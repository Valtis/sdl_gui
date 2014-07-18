#ifndef WINDOWBASETEST_H_
#define WINDOWBASETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

#include "../src/components/WindowBase.h"
#include "TestHandlerManager.h"
#include "../src/rendering/Renderer.h"

namespace sdl_gui {
// helper classes for tests


class TestRenderer : public rendering::Renderer {
public:
	TestRenderer() : m_source_is_set(false), m_destination_is_set(false) {}

	// pointers may be released shortly after this call so we can't simply copy the pointer
	void draw(const texture_ptr &texture, SDL_Rect *source_rect, SDL_Rect *destination_rect) {
		m_source_is_set = false;
		m_destination_is_set = false;

		if (source_rect != nullptr) {
			m_source_rect = *source_rect;
			m_source_is_set = true;
		}

		if (destination_rect != nullptr) {
			m_destination_rect = *destination_rect;
			m_destination_is_set = true;
		}

	}

	SDL_Rect m_source_rect;
	bool m_source_is_set;

	SDL_Rect m_destination_rect;
	bool m_destination_is_set;
};



class WindowBaseTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(WindowBaseTest);
    CPPUNIT_TEST(absolute_dimension_returns_correct_value_if_no_parent);
    CPPUNIT_TEST(relative_dimension_returns_correct_value_if_no_parent);
    CPPUNIT_TEST(absolute_dimension_returns_correct_value_if_has_parent);
    CPPUNIT_TEST(relative_dimension_returns_correct_value_if_has_parent);

    CPPUNIT_TEST(on_click_handler_is_called_with_no_children);
    CPPUNIT_TEST(on_click_handler_is_called_with_child_when_not_clicking_child);
    CPPUNIT_TEST(child_on_click_handler_is_called_with_child_when_clicking_child);


    CPPUNIT_TEST(child_window_is_drawn_fully_if_it_fits_parent);
    CPPUNIT_TEST(grand_child_window_is_drawn_fully_if_it_fits_child_and_child_fits_parent);
    CPPUNIT_TEST(grand_child_window_is_clipped_if_it_does_not_fit_child_and_child_fits_parent);

    CPPUNIT_TEST(child_window_is_clipped_correctly_from_right);
    CPPUNIT_TEST(grand_child_window_is_clipped_correctly_from_right_if_child_is_clipped);
    CPPUNIT_TEST(child_window_is_clipped_correctly_from_top);
    CPPUNIT_TEST(grand_child_window_is_clipped_correctly_from_top_if_child_is_clipped);
    CPPUNIT_TEST(child_window_is_clipped_correctly_from_left);
    CPPUNIT_TEST(grand_child_window_is_clipped_correctly_from_left_if_child_is_clipped);
    CPPUNIT_TEST(child_window_is_clipped_correctly_from_bottom);
    CPPUNIT_TEST(grand_child_window_is_clipped_correctly_from_bottom_if_child_is_clipped);

    CPPUNIT_TEST_SUITE_END();

public:
	WindowBaseTest() { }
	virtual ~WindowBaseTest() { }


    void setUp(void) {}
    void tearDown(void) {}

private:

	void absolute_dimension_returns_correct_value_if_no_parent() {
		WindowBase base{};
		base.set_relative_dimension({30, 40, 50, 60});
		CPPUNIT_ASSERT_EQUAL(30, base.absolute_dimension().x);
		CPPUNIT_ASSERT_EQUAL(40, base.absolute_dimension().y);
		CPPUNIT_ASSERT_EQUAL(50, base.absolute_dimension().w);
		CPPUNIT_ASSERT_EQUAL(60, base.absolute_dimension().h);
	}

	void relative_dimension_returns_correct_value_if_no_parent() {
		WindowBase base{};
		base.set_relative_dimension({30, 40, 50, 60});
		CPPUNIT_ASSERT_EQUAL(30, base.relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(40, base.relative_dimension().y);
		CPPUNIT_ASSERT_EQUAL(50, base.relative_dimension().w);
		CPPUNIT_ASSERT_EQUAL(60, base.relative_dimension().h);
	}

	void absolute_dimension_returns_correct_value_if_has_parent() {
		WindowBase parent{};
		parent.set_relative_dimension({20, 50, 100, 120});

		WindowBase child{};
		child.set_relative_dimension({120, 400, 500, 180});
		child.set_parent(&parent);

		CPPUNIT_ASSERT_EQUAL(140, child.absolute_dimension().x);
		CPPUNIT_ASSERT_EQUAL(450, child.absolute_dimension().y);
		CPPUNIT_ASSERT_EQUAL(500, child.absolute_dimension().w);
		CPPUNIT_ASSERT_EQUAL(180, child.absolute_dimension().h);
	}


	void relative_dimension_returns_correct_value_if_has_parent() {
		WindowBase parent{};
		parent.set_relative_dimension({20, 50, 100, 120});

		WindowBase child{};
		child.set_relative_dimension({120, 400, 500, 180});
		child.set_parent(&parent);

		CPPUNIT_ASSERT_EQUAL(120, child.relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(400, child.relative_dimension().y);
		CPPUNIT_ASSERT_EQUAL(500, child.relative_dimension().w);
		CPPUNIT_ASSERT_EQUAL(180, child.relative_dimension().h);
	}

	void on_click_handler_is_called_with_no_children() {
		WindowBase base{};
		TestHandlerManager manager;

		base.set_handler_manager(&manager);
		std::string handler_name = "my_click_handler";
		base.set_handler(HandlerType::ON_CLICK, handler_name);
		base.on_mouse_up(0, 0);

		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler);
	}

	void on_click_handler_is_called_with_child_when_not_clicking_child() {
		TestHandlerManager manager;

		WindowBase base{};
		base.set_handler_manager(&manager);
		std::string parent_handler_name = "my_click_handler";
		std::string child_handler_name = "child_click_handler";

		base.set_handler(HandlerType::ON_CLICK, parent_handler_name);
		base.set_relative_dimension({0,0, 400, 400});

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({40, 40, 100, 100});
		child->set_handler(HandlerType::ON_CLICK, child_handler_name);
		base.add_child(std::move(child));

		base.on_mouse_up(0, 0);

		CPPUNIT_ASSERT_EQUAL(parent_handler_name, manager.m_called_handler);
	}

	void child_on_click_handler_is_called_with_child_when_clicking_child() {
		TestHandlerManager manager;

		WindowBase base{};
		base.set_handler_manager(&manager);
		std::string parent_handler_name = "my_click_handler";
		std::string child_handler_name = "child_click_handler";

		base.set_handler(HandlerType::ON_CLICK, parent_handler_name);
		base.set_relative_dimension({0,0, 400, 400});

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({40, 40, 100, 100});
		child->set_handler(HandlerType::ON_CLICK, child_handler_name);
		base.add_child(std::move(child));

		base.on_mouse_up(60, 60);

		CPPUNIT_ASSERT_EQUAL(child_handler_name, manager.m_called_handler);
	}

	void child_window_is_drawn_fully_if_it_fits_parent() {

		auto renderer = std::make_shared<TestRenderer>();WindowBase base{};

		base.set_relative_dimension({40, 40, 400, 400});
		base.set_renderer(std::static_pointer_cast<rendering::Renderer>(renderer));

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({10, 10, 200, 100});

		base.add_child(std::move(child));

		base.draw();
		check_source_and_destination(renderer, {0, 0, 200, 100}, {50, 50, 200, 100});
	}

	void grand_child_window_is_drawn_fully_if_it_fits_child_and_child_fits_parent() {

		auto renderer = std::make_shared<TestRenderer>();WindowBase base{};

		base.set_relative_dimension({40, 40, 400, 400});
		base.set_renderer(std::static_pointer_cast<rendering::Renderer>(renderer));

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({20, 30, 100, 100});

		std::unique_ptr<WindowBase> grand_child{new WindowBase{}};
		grand_child->set_relative_dimension({10, 10, 80, 80});

		child->add_child(std::move(grand_child));
		base.add_child(std::move(child));

		base.draw();

		check_source_and_destination(renderer, {0, 0, 80, 80}, {70, 80, 80, 80});
	}

	void grand_child_window_is_clipped_if_it_does_not_fit_child_and_child_fits_parent() {
		auto renderer = std::make_shared<TestRenderer>();
		WindowBase base{};

		base.set_relative_dimension({40, 40, 400, 400});
		base.set_renderer(std::static_pointer_cast<rendering::Renderer>(renderer));

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({20, 30, 40, 100});

		std::unique_ptr<WindowBase> grand_child{new WindowBase{}};
		grand_child->set_relative_dimension({-10, 10, 80, 80});

		child->add_child(std::move(grand_child));
		base.add_child(std::move(child));

		base.draw();
		check_source_and_destination(renderer, {10, 0, 40, 80}, {60, 80, 40, 80});
	}

	void child_window_is_clipped_correctly_from_right() {

		auto renderer = std::make_shared<TestRenderer>();
		WindowBase base{};

		base.set_relative_dimension({40, 40, 400, 500});
		base.set_renderer(std::static_pointer_cast<rendering::Renderer>(renderer));

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({300, 10, 200, 100});

		base.add_child(std::move(child));

		base.draw();
		check_source_and_destination(renderer, {0, 0, 100, 100}, {340, 50, 100, 100});
	}

	void grand_child_window_is_clipped_correctly_from_right_if_child_is_clipped() {

		auto renderer = std::make_shared<TestRenderer>();
		WindowBase base{};

		base.set_relative_dimension({40, 40, 400, 500});
		base.set_renderer(std::static_pointer_cast<rendering::Renderer>(renderer));

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({300, 10, 200, 100});

		std::unique_ptr<WindowBase> grand_child{new WindowBase{}};
		grand_child->set_relative_dimension({10, 10, 160, 20});

		child->add_child(std::move(grand_child));
		base.add_child(std::move(child));

		base.draw();
		check_source_and_destination(renderer, {0, 0, 90, 20}, {350, 60, 90, 20});
	}

	void child_window_is_clipped_correctly_from_top() {

		auto renderer = std::make_shared<TestRenderer>();
		WindowBase base{};

		base.set_relative_dimension({40, 60, 400, 300});
		base.set_renderer(std::static_pointer_cast<rendering::Renderer>(renderer));

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({10, -40, 200, 100});

		base.add_child(std::move(child));

		base.draw();

		CPPUNIT_ASSERT(renderer->m_source_is_set);
		CPPUNIT_ASSERT(renderer->m_destination_is_set);
		check_source_and_destination(renderer, {0, 40, 200, 60}, {50, 60, 200, 60});
	}

	void grand_child_window_is_clipped_correctly_from_top_if_child_is_clipped() {

		auto renderer = std::make_shared<TestRenderer>();
		WindowBase base{};

		base.set_relative_dimension({40, 60, 400, 400});
		base.set_renderer(std::static_pointer_cast<rendering::Renderer>(renderer));

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({10, -40, 200, 100});

		std::unique_ptr<WindowBase> grand_child{new WindowBase{}};
		grand_child->set_relative_dimension({10, 10, 160, 80});

		child->add_child(std::move(grand_child));
		base.add_child(std::move(child));

		base.draw();
		check_source_and_destination(renderer, {0, 30, 160, 50}, {60, 60, 160, 50});
	}

	void child_window_is_clipped_correctly_from_left() {

		auto renderer = std::make_shared<TestRenderer>();
		WindowBase base{};

		base.set_relative_dimension({40, 60, 400, 300});
		base.set_renderer(std::static_pointer_cast<rendering::Renderer>(renderer));

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({-40, 10, 200, 100});

		base.add_child(std::move(child));

		base.draw();
		check_source_and_destination(renderer, {40, 0, 160, 100}, {40, 70, 160, 100});
	}

	void grand_child_window_is_clipped_correctly_from_left_if_child_is_clipped() {

		auto renderer = std::make_shared<TestRenderer>();
		WindowBase base{};

		base.set_relative_dimension({40, 60, 400, 300});
		base.set_renderer(std::static_pointer_cast<rendering::Renderer>(renderer));

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({-20, 10, 200, 100});

		std::unique_ptr<WindowBase> grand_child{new WindowBase{}};
		grand_child->set_relative_dimension({10, 10, 160, 80});

		child->add_child(std::move(grand_child));
		base.add_child(std::move(child));

		base.draw();
		check_source_and_destination(renderer, {10, 0, 150, 80}, {40, 80, 150, 80});
	}

	void child_window_is_clipped_correctly_from_bottom() {

		auto renderer = std::make_shared<TestRenderer>();
		WindowBase base{};

		base.set_relative_dimension({40, 60, 400, 300});
		base.set_renderer(std::static_pointer_cast<rendering::Renderer>(renderer));

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({10, 250, 200, 100});

		base.add_child(std::move(child));

		base.draw();
		check_source_and_destination(renderer, {0, 0, 200, 50}, {50, 310, 200, 50});
	}

	void grand_child_window_is_clipped_correctly_from_bottom_if_child_is_clipped() {

		auto renderer = std::make_shared<TestRenderer>();WindowBase base{};

		base.set_relative_dimension({40, 60, 400, 300});
		base.set_renderer(std::static_pointer_cast<rendering::Renderer>(renderer));

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({10, 250, 200, 100});

		std::unique_ptr<WindowBase> grand_child{new WindowBase{}};
		grand_child->set_relative_dimension({10, 10, 160, 80});

		child->add_child(std::move(grand_child));
		base.add_child(std::move(child));

		base.draw();
		check_source_and_destination(renderer, {0, 0, 160, 40}, {60, 320, 160, 40});
	}


	void check_source_and_destination(std::shared_ptr<TestRenderer> renderer, SDL_Rect expected_source, SDL_Rect expected_destination) {

		CPPUNIT_ASSERT(renderer->m_source_is_set);
		CPPUNIT_ASSERT(renderer->m_destination_is_set);

		CPPUNIT_ASSERT_EQUAL_MESSAGE("Source x coordinate incorrect", expected_source.x, renderer->m_source_rect.x);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Source y coordinate incorrect", expected_source.y, renderer->m_source_rect.y);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Source w coordinate incorrect", expected_source.w, renderer->m_source_rect.w);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Source h coordinate incorrect", expected_source.h, renderer->m_source_rect.h);

		CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination x coordinate incorrect", expected_destination.x, renderer->m_destination_rect.x);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination y coordinate incorrect", expected_destination.y, renderer->m_destination_rect.y);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination w coordinate incorrect", expected_destination.w, renderer->m_destination_rect.w);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination h coordinate incorrect", expected_destination.h, renderer->m_destination_rect.h);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( WindowBaseTest );

} /* namespace sdl_gui */





#endif /* WINDOWBASETEST_H_ */
