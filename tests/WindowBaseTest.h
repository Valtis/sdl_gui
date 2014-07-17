#ifndef WINDOWBASETEST_H_
#define WINDOWBASETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

#include "../src/components/WindowBase.h"
#include "../src/HandlerManager.h"

namespace sdl_gui {
// helper class for tests
class TestHandlerManager : public HandlerManager {
public:
	std::string m_called_handler;
	void call_handler(const std::string &handler_name) {
		m_called_handler = handler_name;
	}
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
		base.on_click(0, 0);

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

		base.on_click(0, 0);

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

		base.on_click(60, 60);

		CPPUNIT_ASSERT_EQUAL(child_handler_name, manager.m_called_handler);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( WindowBaseTest );

} /* namespace sdl_gui */





#endif /* WINDOWBASETEST_H_ */
