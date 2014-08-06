#ifndef WINDOWBASETEST_H_
#define WINDOWBASETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <algorithm>

#include "../src/components/WindowBase.h"
#include "mocks/TestHandlerManager.h"
#include "mocks/TestRenderer.h"

namespace sdl_gui {


class WindowBaseTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(WindowBaseTest);
    CPPUNIT_TEST(absolute_dimension_returns_correct_value_if_no_parent);
    CPPUNIT_TEST(relative_dimension_returns_correct_value_if_no_parent);
    CPPUNIT_TEST(absolute_dimension_returns_correct_value_if_has_parent);
    CPPUNIT_TEST(relative_dimension_returns_correct_value_if_has_parent);

    CPPUNIT_TEST(on_click_handler_is_called_with_no_children);
    CPPUNIT_TEST(on_click_handler_is_called_with_child_when_not_clicking_child);
    CPPUNIT_TEST(child_on_click_handler_is_called_with_child_when_clicking_child);
    CPPUNIT_TEST(on_click_to_on_child_calls_child_on_gaining_focus_handler);
    CPPUNIT_TEST(on_click_to_on_parent_calls_child_on_losing_focus_handler_when_child_had_focus);
    CPPUNIT_TEST(second_on_click_to_on_child_does_not_call_on_gaining_focus_handler_when_child_had_focus);
    CPPUNIT_TEST(second_on_click_to_on_new_child_calls_on_gaining_focus_on_new_child_and_on_losing_focus_on_old_child);

    CPPUNIT_TEST(on_mouse_down_handler_is_called_with_no_children);
    CPPUNIT_TEST(on_mouse_down_handler_is_called_with_child_when_not_clicking_child);
    CPPUNIT_TEST(child_on_mouse_down_handler_is_called_with_child_when_clicking_child);

    CPPUNIT_TEST(on_mouse_over_handler_is_called_with_no_children);
	CPPUNIT_TEST(on_mouse_over_handler_is_called_with_child_when_not_hovering_over_child);
	CPPUNIT_TEST(child_on_mouse_over_handler_is_called_with_child_when_hovering_over_child);

    CPPUNIT_TEST(on_drag_handler_is_called_with_no_children);
	CPPUNIT_TEST(on_drag_handler_is_called_with_child_when_not_dragging_child);
	CPPUNIT_TEST(child_on_drag_handler_is_called_with_child_when_dragging_child);

	CPPUNIT_TEST(on_gaining_focus_handler_is_called_with_no_children);
	CPPUNIT_TEST(on_gaining_focus_handler_is_called_with_child_and_parent);

	CPPUNIT_TEST(on_losing_focus_handler_is_called_with_no_children);
	CPPUNIT_TEST(on_losing_focus_handler_is_called_with_child_and_parent);
	CPPUNIT_TEST(on_losing_focus_handler_is_called_with_child_if_another_child_gains_focus);

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

    CPPUNIT_TEST(set_name_works);

    CPPUNIT_TEST(get_child_by_name_returns_nullptr_if_no_child_exists_with_name);
    CPPUNIT_TEST(get_child_by_name_returns_valid_pointer_if_child_exists_with_name);
    CPPUNIT_TEST(get_child_by_name_returns_valid_pointer_if_grand_child_exists_with_name);


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
		std::string handler_name = "handler_name";
		TestHandlerManager manager;
		auto base = set_up_base_for_no_children_handler_calls(manager, Handler_Type::ON_CLICK, handler_name);
		base->on_mouse_up(0, 0);
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler.at(0));
	}

	void on_click_handler_is_called_with_child_when_not_clicking_child() {
		TestHandlerManager manager;
		std::string parent_handler_name = "parent_handler";
		std::string child_handler_name = "child_handler";

		auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_CLICK, parent_handler_name, child_handler_name);
		base->on_mouse_up(0, 0);

		CPPUNIT_ASSERT_EQUAL(parent_handler_name, manager.m_called_handler.at(0));
	}

	void child_on_click_handler_is_called_with_child_when_clicking_child() {
		TestHandlerManager manager;
		std::string parent_handler_name = "parent_handler";
		std::string child_handler_name = "child_handler";
		auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_CLICK, parent_handler_name, child_handler_name);
		base->on_mouse_up(60, 60);

		CPPUNIT_ASSERT_EQUAL(child_handler_name, manager.m_called_handler.at(0));
	}

	void on_click_to_on_child_calls_child_on_gaining_focus_handler() {
		TestHandlerManager manager;
		std::string parent_handler_name = "parent_handler";
		std::string child_handler_name = "child_handler";
		auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_GAINING_FOCUS, parent_handler_name, child_handler_name);
		base->on_mouse_up(60, 60);
		CPPUNIT_ASSERT_EQUAL(child_handler_name, manager.m_called_handler.at(0));
	}

	void on_click_to_on_parent_calls_child_on_losing_focus_handler_when_child_had_focus() {
		TestHandlerManager manager;
		std::string parent_handler_name = "parent_handler";
		std::string child_handler_name = "child_handler";
		auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_LOSING_FOCUS, parent_handler_name, child_handler_name);
		base->on_mouse_up(60, 60);
		base->on_mouse_up(10, 10);
		CPPUNIT_ASSERT_EQUAL(child_handler_name, manager.m_called_handler.at(0));
	}

	void second_on_click_to_on_child_does_not_call_on_gaining_focus_handler_when_child_had_focus() {
		TestHandlerManager manager;
		std::string parent_handler_name = "parent_handler";
		std::string child_handler_name = "child_handler";
		auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_GAINING_FOCUS, parent_handler_name, child_handler_name);
		base->on_mouse_up(60, 60);
		base->on_mouse_up(10, 10);

		CPPUNIT_ASSERT_EQUAL((size_t)1, manager.m_called_handler.size());
		CPPUNIT_ASSERT_EQUAL(child_handler_name, manager.m_called_handler.at(0));
	}

	void second_on_click_to_on_new_child_calls_on_gaining_focus_on_new_child_and_on_losing_focus_on_old_child() {
			TestHandlerManager manager;
			std::string parent_handler_name = "parent_handler";
			std::string child_handler_name = "child_handler";
			std::string second_child_handler_name = "child_handler2";

			auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_LOSING_FOCUS, parent_handler_name, child_handler_name);

			std::unique_ptr<WindowBase> second_child{new WindowBase{}};
			second_child->set_relative_dimension({10, 10, 10, 10});
			second_child->set_handler(Handler_Type::ON_GAINING_FOCUS, second_child_handler_name);
			base->add_child(std::move(second_child));

			base->on_mouse_up(60, 60);
			base->on_mouse_up(10, 10);

			CPPUNIT_ASSERT_EQUAL((size_t)2, manager.m_called_handler.size());
			CPPUNIT_ASSERT_EQUAL(child_handler_name, manager.m_called_handler.at(0));
			CPPUNIT_ASSERT_EQUAL(second_child_handler_name, manager.m_called_handler.at(1));
	}

	void on_mouse_down_handler_is_called_with_no_children() {
		std::string handler_name = "handler_name";
		TestHandlerManager manager;
		auto base = set_up_base_for_no_children_handler_calls(manager, Handler_Type::ON_MOUSE_DOWN, handler_name);
		base->on_mouse_down(0, 0);
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler.at(0));
	}

	void on_mouse_down_handler_is_called_with_child_when_not_clicking_child() {
		TestHandlerManager manager;
		std::string parent_handler_name = "parent_handler";
		std::string child_handler_name = "child_handler";

		auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_MOUSE_DOWN, parent_handler_name, child_handler_name);
		base->on_mouse_down(0, 0);

		CPPUNIT_ASSERT_EQUAL(parent_handler_name, manager.m_called_handler.at(0));
	}

	void child_on_mouse_down_handler_is_called_with_child_when_clicking_child() {
		TestHandlerManager manager;
		std::string parent_handler_name = "parent_handler";
		std::string child_handler_name = "child_handler";

		auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_MOUSE_DOWN, parent_handler_name, child_handler_name);
		base->on_mouse_down(60, 60);

		CPPUNIT_ASSERT_EQUAL(child_handler_name, manager.m_called_handler.at(0));
	}

	void on_mouse_over_handler_is_called_with_no_children() {
		std::string handler_name = "handler_name";
		TestHandlerManager manager;
		auto base = set_up_base_for_no_children_handler_calls(manager, Handler_Type::ON_MOUSE_OVER, handler_name);
		base->on_mouse_over(0, 0);
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler.at(0));
	}

	void on_mouse_over_handler_is_called_with_child_when_not_hovering_over_child() {
		TestHandlerManager manager;
		std::string parent_handler_name = "parent_handler";
		std::string child_handler_name = "child_handler";

		auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_MOUSE_OVER, parent_handler_name, child_handler_name);
		base->on_mouse_over(0, 0);

		CPPUNIT_ASSERT_EQUAL(parent_handler_name, manager.m_called_handler.at(0));
	}

	void child_on_mouse_over_handler_is_called_with_child_when_hovering_over_child() {
		TestHandlerManager manager;
		std::string parent_handler_name = "parent_handler";
		std::string child_handler_name = "child_handler";

		auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_MOUSE_OVER, parent_handler_name, child_handler_name);
		base->on_mouse_over(60, 60);

		CPPUNIT_ASSERT_EQUAL(child_handler_name, manager.m_called_handler.at(0));
	}

	void on_drag_handler_is_called_with_no_children() {
		std::string handler_name = "handler_name";
		TestHandlerManager manager;
		auto base = set_up_base_for_no_children_handler_calls(manager, Handler_Type::ON_DRAG, handler_name);
		base->on_drag(0, 0, 1, 1);
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler.at(0));
	}

	void on_drag_handler_is_called_with_child_when_not_dragging_child() {
		TestHandlerManager manager;
		std::string parent_handler_name = "parent_handler";
		std::string child_handler_name = "child_handler";

		auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_DRAG, parent_handler_name, child_handler_name);
		base->on_drag(0, 0, 1, 1);

		CPPUNIT_ASSERT_EQUAL(parent_handler_name, manager.m_called_handler.at(0));
	}

	void child_on_drag_handler_is_called_with_child_when_dragging_child() {
		TestHandlerManager manager;
		std::string parent_handler_name = "parent_handler";
		std::string child_handler_name = "child_handler";

		auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_DRAG, parent_handler_name, child_handler_name);
		base->on_drag(60, 60, 1, 1);

		CPPUNIT_ASSERT_EQUAL(child_handler_name, manager.m_called_handler.at(0));
	}

	void on_gaining_focus_handler_is_called_with_no_children() {
		std::string handler_name = "handler_name";
		TestHandlerManager manager;
		auto base = set_up_base_for_no_children_handler_calls(manager, Handler_Type::ON_GAINING_FOCUS, handler_name);
		base->on_gaining_focus();
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler.at(0));
	}

	void on_gaining_focus_handler_is_called_with_child_and_parent() {
		TestHandlerManager manager;
		std::string parent_handler_name = "parent_handler";
		std::string child_handler_name = "child_handler";

		auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_GAINING_FOCUS, parent_handler_name, child_handler_name);
		base->on_gaining_focus();

		CPPUNIT_ASSERT(std::find(manager.m_called_handler.begin(), manager.m_called_handler.end(), parent_handler_name) != manager.m_called_handler.end());
		CPPUNIT_ASSERT(std::find(manager.m_called_handler.begin(), manager.m_called_handler.end(), child_handler_name) != manager.m_called_handler.end());
	}

	void on_losing_focus_handler_is_called_with_no_children() {
		std::string handler_name = "handler_name";
		TestHandlerManager manager;
		auto base = set_up_base_for_no_children_handler_calls(manager, Handler_Type::ON_LOSING_FOCUS, handler_name);
		base->on_losing_focus();
		CPPUNIT_ASSERT_EQUAL(handler_name, manager.m_called_handler.at(0));
	}

	void on_losing_focus_handler_is_called_with_child_and_parent() {
		TestHandlerManager manager;
		std::string parent_handler_name = "parent_handler";
		std::string child_handler_name = "child_handler";

		auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_LOSING_FOCUS, parent_handler_name, child_handler_name);
		base->on_losing_focus();

		CPPUNIT_ASSERT(std::find(manager.m_called_handler.begin(), manager.m_called_handler.end(), parent_handler_name) != manager.m_called_handler.end());
		CPPUNIT_ASSERT(std::find(manager.m_called_handler.begin(), manager.m_called_handler.end(), child_handler_name) != manager.m_called_handler.end());
	}

	void on_losing_focus_handler_is_called_with_child_if_another_child_gains_focus() {
		TestHandlerManager manager;
		std::string parent_handler_name = "parent_handler";
		std::string child_handler_name = "child_handler";

		auto base = set_up_base_with_child_for_handler_calls(manager, Handler_Type::ON_LOSING_FOCUS, parent_handler_name, child_handler_name);
		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({0, 0, 10, 10});
		base->add_child(std::move(child));

		base->on_mouse_up(60, 60);
		base->on_mouse_up(10, 10);

		CPPUNIT_ASSERT(std::find(manager.m_called_handler.begin(), manager.m_called_handler.end(), child_handler_name) != manager.m_called_handler.end());
	}

	std::unique_ptr<WindowBase> set_up_base_for_no_children_handler_calls(TestHandlerManager &manager, Handler_Type type, const std::string &name) {
		std::unique_ptr<WindowBase> base{new WindowBase{}};
		base->set_handler_manager(&manager);
		base->set_handler(type, name);

		return base;
	}

	std::unique_ptr<WindowBase> set_up_base_with_child_for_handler_calls(TestHandlerManager &manager, Handler_Type type, const std::string &parent_name, const std::string &child_name) {
		std::unique_ptr<WindowBase> base{new WindowBase{}};
		base->set_handler_manager(&manager);

		base->set_handler(type, parent_name);
		base->set_relative_dimension({0,0, 400, 400});

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({40, 40, 100, 100});
		child->set_handler(type, child_name);
		base->add_child(std::move(child));

		return base;
	}

	void child_window_is_drawn_fully_if_it_fits_parent() {

		auto renderer = std::make_shared<TestRenderer>();WindowBase base{};

		base.set_relative_dimension({40, 40, 400, 400});
		base.set_renderer(renderer.get());

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({10, 10, 200, 100});

		base.add_child(std::move(child));

		base.draw();
		check_source_and_destination(renderer, {0, 0, 200, 100}, {50, 50, 200, 100});
	}

	void grand_child_window_is_drawn_fully_if_it_fits_child_and_child_fits_parent() {

		auto renderer = std::make_shared<TestRenderer>();WindowBase base{};

		base.set_relative_dimension({40, 40, 400, 400});
		base.set_renderer(renderer.get());

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
		base.set_renderer(renderer.get());

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
		base.set_renderer(renderer.get());

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
		base.set_renderer(renderer.get());

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
		base.set_renderer(renderer.get());

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
		base.set_renderer(renderer.get());

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
		base.set_renderer(renderer.get());

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
		base.set_renderer(renderer.get());

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
		base.set_renderer(renderer.get());

		std::unique_ptr<WindowBase> child{new WindowBase{}};
		child->set_relative_dimension({10, 250, 200, 100});

		base.add_child(std::move(child));

		base.draw();
		check_source_and_destination(renderer, {0, 0, 200, 50}, {50, 310, 200, 50});
	}

	void grand_child_window_is_clipped_correctly_from_bottom_if_child_is_clipped() {

		auto renderer = std::make_shared<TestRenderer>();WindowBase base{};

		base.set_relative_dimension({40, 60, 400, 300});
		base.set_renderer(renderer.get());

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

	void set_name_works() {
		WindowBase base;
		base.set_name("foobar");
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Name was not set correctly", std::string("foobar"), base.get_name());
	}

	void get_child_by_name_returns_nullptr_if_no_child_exists_with_name() {
		auto base = create_base_for_get_child_name_tests();
		CPPUNIT_ASSERT_MESSAGE("Nullptr was expected for non-existent child", base->get_child_by_name("no_name") == nullptr);
	}

	void get_child_by_name_returns_valid_pointer_if_child_exists_with_name() {
		auto base = create_base_for_get_child_name_tests();
		CPPUNIT_ASSERT_MESSAGE("Expected valid pointer", base->get_child_by_name("child_1") != nullptr);
	}

	void get_child_by_name_returns_valid_pointer_if_grand_child_exists_with_name() {
		auto base = create_base_for_get_child_name_tests();
		CPPUNIT_ASSERT_MESSAGE("Expected valid pointer", base->get_child_by_name("grand_child") != nullptr);
	}

	std::unique_ptr<WindowBase> create_base_for_get_child_name_tests() {
		std::unique_ptr<WindowBase> grand_child{new WindowBase{}};
		grand_child->set_name("grand_child");

		std::unique_ptr<WindowBase> child_1{new WindowBase{}};
		child_1->set_name("child_1");

		std::unique_ptr<WindowBase> child_2{new WindowBase{}};
		child_2->set_name("child_2");

		child_1->add_child(std::move(grand_child));

		std::unique_ptr<WindowBase> base{new WindowBase{}};

		base->add_child(std::move(child_1));
		base->add_child(std::move(child_2));

		return base;
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( WindowBaseTest );

} /* namespace sdl_gui */





#endif /* WINDOWBASETEST_H_ */
