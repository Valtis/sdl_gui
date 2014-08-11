#ifndef TEXTCURSORTEST_H_
#define TEXTCURSORTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <vector>
#include <string>

#include "../src/components/TextCursor.h"
#include "mocks/TestRenderer.h"

namespace sdl_gui {

class TextCursorTest  : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TextCursorTest);

    CPPUNIT_TEST(text_cursor_moves_to_right_correctly_inside_a_line);
    CPPUNIT_TEST(text_cursor_moves_to_left_correctly_inside_a_line);
    CPPUNIT_TEST(text_cursor_moves_up_correctly);
    CPPUNIT_TEST(text_cursor_moves_down_correctly);

    CPPUNIT_TEST(text_cursor_moves_to_end_of_previous_line_when_moving_left);
    CPPUNIT_TEST(text_cursor_moves_to_beginning_of_next_line_when_moving_right);

    CPPUNIT_TEST(text_cursor_stops_at_upper_left_corner);
    CPPUNIT_TEST(text_cursor_stops_at_lower_right_corner);

    CPPUNIT_TEST(text_cursor_moves_to_end_of_line_if_next_line_is_shorter_and_moving_up);
    CPPUNIT_TEST(text_cursor_moves_to_end_of_line_if_next_line_is_shorter_and_moving_down);

    CPPUNIT_TEST(text_cursor_set_line_position_works);
    CPPUNIT_TEST_SUITE_END();

public:
    TextCursorTest() { }
	virtual ~TextCursorTest() { }

	void setUp(void) {
		m_lines = { "this is a line", "this is a longer line", "short" };
		m_test_renderer = std::make_shared<TestRenderer>();
		m_cursor = std::make_shared<TextCursor>();
		m_cursor->set_renderer(m_test_renderer.get());
	    m_cursor->set_font_size(1);
	}

	void tearDown(void) {}

private:
	std::vector<std::string> m_lines;
	std::shared_ptr<TextCursor> m_cursor;
	std::shared_ptr<TestRenderer> m_test_renderer;

	// relative dimension x has +1 added, this must be taken account when testing

	void text_cursor_moves_to_right_correctly_inside_a_line() {
		m_cursor->move_cursor({4, 0}, m_lines);

		CPPUNIT_ASSERT_EQUAL(5, m_cursor->relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(0, m_cursor->relative_dimension().y);

	}

	void text_cursor_moves_to_left_correctly_inside_a_line() {
		m_cursor->set_cursor_line_position({10, 0}, m_lines);
		m_cursor->move_cursor({-5, 0}, m_lines);

		CPPUNIT_ASSERT_EQUAL(6, m_cursor->relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(0, m_cursor->relative_dimension().y);

	}

	void text_cursor_moves_up_correctly() {
		m_cursor->set_cursor_line_position({10, 1}, m_lines);
		m_cursor->move_cursor({0, -1}, m_lines);
		CPPUNIT_ASSERT_EQUAL(11, m_cursor->relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(0, m_cursor->relative_dimension().y);
	}

	void text_cursor_moves_down_correctly() {
		m_cursor->set_cursor_line_position({10, 0}, m_lines);
		m_cursor->move_cursor({0, 1}, m_lines);
		CPPUNIT_ASSERT_EQUAL(11, m_cursor->relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(1, m_cursor->relative_dimension().y);
	}


	void text_cursor_moves_to_end_of_line_if_next_line_is_shorter_and_moving_up() {
		m_cursor->set_cursor_line_position({20, 1}, m_lines);
		m_cursor->move_cursor({0, -1}, m_lines);

		CPPUNIT_ASSERT_EQUAL(15, m_cursor->relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(0, m_cursor->relative_dimension().y);
	}

	void text_cursor_moves_to_end_of_line_if_next_line_is_shorter_and_moving_down() {
		m_cursor->set_cursor_line_position({20, 1}, m_lines);
		m_cursor->move_cursor({0, 1}, m_lines);

		CPPUNIT_ASSERT_EQUAL(6, m_cursor->relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(2, m_cursor->relative_dimension().y);
	}


    void text_cursor_moves_to_end_of_previous_line_when_moving_left() {
    	m_cursor->set_cursor_line_position({0, 1}, m_lines);
		m_cursor->move_cursor({-1, 0}, m_lines);
		CPPUNIT_ASSERT_EQUAL(15, m_cursor->relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(0, m_cursor->relative_dimension().y);
    }

    void text_cursor_moves_to_beginning_of_next_line_when_moving_right() {
    	m_cursor->set_cursor_line_position({14, 0}, m_lines);
		m_cursor->move_cursor({1, 0}, m_lines);
		CPPUNIT_ASSERT_EQUAL(1, m_cursor->relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(1, m_cursor->relative_dimension().y);
    }


	void text_cursor_stops_at_upper_left_corner() {
		m_cursor->move_cursor({-5, -2}, m_lines);

		CPPUNIT_ASSERT_EQUAL(1, m_cursor->relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(0, m_cursor->relative_dimension().y);
	}

	void text_cursor_stops_at_lower_right_corner() {
		m_cursor->move_cursor({70, 5}, m_lines);

		CPPUNIT_ASSERT_EQUAL(6, m_cursor->relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(2, m_cursor->relative_dimension().y);
	}

	void text_cursor_set_line_position_works() {
		m_cursor->set_cursor_line_position({10, 1}, m_lines);
		m_cursor->set_cursor_line_position({4, 2}, m_lines);
		CPPUNIT_ASSERT_EQUAL(5, m_cursor->relative_dimension().x);
		CPPUNIT_ASSERT_EQUAL(2, m_cursor->relative_dimension().y);
	}

};


CPPUNIT_TEST_SUITE_REGISTRATION( TextCursorTest );
} /* ńamespace sdl_gui */


#endif /* TEXTCURSORTEST_H_ */
