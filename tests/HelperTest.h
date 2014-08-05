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

    CPPUNIT_TEST(destination_rectangle_is_clipped_correctly_when_clipping_is_required);
    CPPUNIT_TEST(destination_rectangle_is__not_clipped_when_it_fits_inside);
    CPPUNIT_TEST(source_rectangle_is_clipped_correctly_when_clipping_is_required);
    CPPUNIT_TEST(source_rectangle_is_not_clipped_when_clipping_is_not_required);

    CPPUNIT_TEST(lighter_color_produces_lighter_colors);
    CPPUNIT_TEST(darker_color_produces_darker_colors);

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


    void destination_rectangle_is_clipped_correctly_when_clipping_is_required() {
    	SDL_Rect source = {0, 0, 50, 50 };
    	SDL_Rect destination = { 40, 50, 90, 100 };

    	SDL_Rect draw_area = { 20, 60, 30, 30 };
    	utility::clip_draw_rectangles(draw_area, source, destination);

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination x-coordinate was changed incorrectly", 40, destination.x);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination y-coordinate was changed incorrectly", 60, destination.y);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination w-coordinate was changed incorrectly", 10, destination.w);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination h-coordinate was changed incorrectly", 30, destination.h);
    }

    void destination_rectangle_is__not_clipped_when_it_fits_inside() {
    	SDL_Rect source = {0, 0, 50, 50 };
    	SDL_Rect destination = { 40, 50, 90, 100 };

    	SDL_Rect draw_area = { 20, 50, 300, 300 };
    	utility::clip_draw_rectangles(draw_area, source, destination);

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination x-coordinate was changed incorrectly", 40, destination.x);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination y-coordinate was changed incorrectly", 50, destination.y);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination w-coordinate was changed incorrectly", 90, destination.w);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Destination h-coordinate was changed incorrectly", 100, destination.h);
    }

    void source_rectangle_is_clipped_correctly_when_clipping_is_required() {
        	SDL_Rect source = {0, 0, 50, 50 };
        	SDL_Rect destination = { 40, 50, 90, 100 };

        	SDL_Rect draw_area = { 20, 60, 30, 30 };
        	utility::clip_draw_rectangles(draw_area, source, destination);

        	CPPUNIT_ASSERT_EQUAL_MESSAGE("Source x-coordinate was changed incorrectly", 0, source.x);
        	CPPUNIT_ASSERT_EQUAL_MESSAGE("Source y-coordinate was changed incorrectly", 10, source.y);
        	CPPUNIT_ASSERT_EQUAL_MESSAGE("Source w-coordinate was changed incorrectly", 10, source.w);
        	CPPUNIT_ASSERT_EQUAL_MESSAGE("Source h-coordinate was changed incorrectly", 30, source.h);
    }

    void source_rectangle_is_not_clipped_when_clipping_is_not_required() {
        	SDL_Rect source = {0, 0, 50, 50 };
        	SDL_Rect destination = { 40, 50, 90, 100 };

        	SDL_Rect draw_area = { 20, 20, 300, 300 };
        	utility::clip_draw_rectangles(draw_area, source, destination);

        	CPPUNIT_ASSERT_EQUAL_MESSAGE("Source x-coordinate was changed incorrectly", 0, source.x);
        	CPPUNIT_ASSERT_EQUAL_MESSAGE("Source y-coordinate was changed incorrectly", 0, source.y);
        	CPPUNIT_ASSERT_EQUAL_MESSAGE("Source w-coordinate was changed incorrectly", 50, source.w);
        	CPPUNIT_ASSERT_EQUAL_MESSAGE("Source h-coordinate was changed incorrectly", 50, source.h);
    }

    void lighter_color_produces_lighter_colors() {
    	SDL_Color original = { 170, 170, 170, 255 };
    	SDL_Color lightened = utility::lighter_color(original, 0.5);

    	CPPUNIT_ASSERT_MESSAGE("Produced r-component is not lighter", lightened.r >= original.r);
    	CPPUNIT_ASSERT_MESSAGE("Produced g-component is not lighter", lightened.g >= original.g);
    	CPPUNIT_ASSERT_MESSAGE("Produced b-component is not lighter", lightened.b >= original.b);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Alpha value has changed", original.a, lightened.a);
    }

    void darker_color_produces_darker_colors() {
    	SDL_Color original = { 170, 170, 170, 255 };
    	SDL_Color darkened = utility::darker_color(original, 0.5);

    	CPPUNIT_ASSERT_MESSAGE("Produced r-component is not darker", darkened.r <= original.r);
    	CPPUNIT_ASSERT_MESSAGE("Produced g-component is not darker", darkened.g <= original.g);
    	CPPUNIT_ASSERT_MESSAGE("Produced b-component is not darker", darkened.b <= original.b);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Alpha value has changed", original.a, darkened.a);
    }
};




CPPUNIT_TEST_SUITE_REGISTRATION( UtilityTest);
} /* ńamespace sdl_gui */
#endif /* HELPERTEST_H_ */
