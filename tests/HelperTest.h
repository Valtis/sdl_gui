#ifndef HELPERTEST_H_
#define HELPERTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../src/utility/Helpers.h"

namespace sdl_gui {

class UtilityTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UtilityTest);

    CPPUNIT_TEST(point_inside_rect_returns_true_if_point_is_inside);
    CPPUNIT_TEST(point_inside_rect_returns_false_if_point_is_left_and_above);
    CPPUNIT_TEST(point_inside_rect_returns_false_if_point_is_right_and_below);
    CPPUNIT_TEST(point_inside_rect_returns_true_if_point_is_on_top_left_edge_of_rectangle);
    CPPUNIT_TEST(point_inside_rect_returns_true_if_point_is_on_bottom_right_edge_of_rectangle);

    CPPUNIT_TEST_SUITE_END();

public:
    UtilityTest() { }
	virtual ~UtilityTest() { }

    void setUp(void) {}
    void tearDown(void) {}

private:

    void point_inside_rect_returns_true_if_point_is_inside() {
    	CPPUNIT_ASSERT_MESSAGE("False returned for a point that is inside rectangle", utility::point_inside_rect({ 80, 100 }, { 50, 90, 100, 30 }));
    }

    void point_inside_rect_returns_false_if_point_is_left_and_above() {
    	CPPUNIT_ASSERT_MESSAGE("True returned for a point that is outside rectangle", !utility::point_inside_rect({ 40, 80 }, { 50, 90, 100, 30 }));
    }

    void point_inside_rect_returns_false_if_point_is_right_and_below() {
    	CPPUNIT_ASSERT_MESSAGE("True returned for a point that is outside rectangle", !utility::point_inside_rect({ 160, 130 }, { 50, 90, 100, 30 }));
    }

    void point_inside_rect_returns_true_if_point_is_on_top_left_edge_of_rectangle() {
    	CPPUNIT_ASSERT_MESSAGE("True returned for a point that is outside rectangle", utility::point_inside_rect({ 50, 90, }, { 50, 90, 100, 30 }));
    }

    void point_inside_rect_returns_true_if_point_is_on_bottom_right_edge_of_rectangle() {
        	CPPUNIT_ASSERT_MESSAGE("True returned for a point that is outside rectangle", utility::point_inside_rect({ 150, 120, }, { 50, 90, 100, 30 }));
    }


};




CPPUNIT_TEST_SUITE_REGISTRATION( UtilityTest);
} /* ńamespace sdl_gui */
#endif /* HELPERTEST_H_ */
