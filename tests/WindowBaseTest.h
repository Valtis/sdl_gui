#ifndef WINDOWBASETEST_H_
#define WINDOWBASETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../ui/WindowBase.h"

namespace sdl_gui {

class WindowBaseTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(WindowBaseTest);
    CPPUNIT_TEST(absolute_dimension_returns_correct_value_if_no_parent);
    CPPUNIT_TEST(relative_dimension_returns_correct_value_if_no_parent);
    CPPUNIT_TEST(absolute_dimension_returns_correct_value_if_has_parent);
    CPPUNIT_TEST(relative_dimension_returns_correct_value_if_has_parent);
    CPPUNIT_TEST_SUITE_END();

public:
	WindowBaseTest() { }
	virtual ~WindowBaseTest() { }


    void setUp(void) {}
    void tearDown(void) {}

private:

	void absolute_dimension_returns_correct_value_if_no_parent() {
		WindowBase base;
		base.set_relative_dimension({30, 40, 50, 60});
		CPPUNIT_ASSERT_EQUAL(30, base.absolute_dimension().x);
		CPPUNIT_ASSERT_EQUAL(40, base.absolute_dimension().y);
		CPPUNIT_ASSERT_EQUAL(50, base.absolute_dimension().w);
		CPPUNIT_ASSERT_EQUAL(60, base.absolute_dimension().h);
	}

	void relative_dimension_returns_correct_value_if_no_parent() {
		WindowBase base;
		base.set_relative_dimension({30, 40, 50, 60});
		CPPUNIT_ASSERT_EQUAL(30, base.relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(40, base.relative_dimension().y);
		CPPUNIT_ASSERT_EQUAL(50, base.relative_dimension().w);
		CPPUNIT_ASSERT_EQUAL(60, base.relative_dimension().h);
	}

	void absolute_dimension_returns_correct_value_if_has_parent() {
		WindowBase parent;
		parent.set_relative_dimension({20, 50, 100, 120});

		WindowBase child;
		child.set_relative_dimension({120, 400, 500, 180});
		child.set_parent(&parent);

		CPPUNIT_ASSERT_EQUAL(140, child.absolute_dimension().x);
		CPPUNIT_ASSERT_EQUAL(450, child.absolute_dimension().y);
		CPPUNIT_ASSERT_EQUAL(500, child.absolute_dimension().w);
		CPPUNIT_ASSERT_EQUAL(180, child.absolute_dimension().h);
	}


	void relative_dimension_returns_correct_value_if_has_parent() {
		WindowBase parent;
		parent.set_relative_dimension({20, 50, 100, 120});

		WindowBase child;
		child.set_relative_dimension({120, 400, 500, 180});
		child.set_parent(&parent);

		CPPUNIT_ASSERT_EQUAL(120, child.relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(400, child.relative_dimension().y);
		CPPUNIT_ASSERT_EQUAL(500, child.relative_dimension().w);
		CPPUNIT_ASSERT_EQUAL(180, child.relative_dimension().h);
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( WindowBaseTest );

} /* namespace sdl_gui */





#endif /* WINDOWBASETEST_H_ */
