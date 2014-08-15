#ifndef TEXTCURSORTEST_H_
#define TEXTCURSORTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <vector>
#include <string>

#include "../src/components/TextCursor.h"
#include "mocks/TestRenderer.h"

namespace sdl_gui {

class TextCursorTest: public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(TextCursorTest);
    CPPUNIT_TEST(text_cursor_movement_on_empty_lines_sets_cursor_line_position_to_beginning);

    CPPUNIT_TEST(text_cursor_does_not_move_when_no_movement_asked);

    CPPUNIT_TEST(text_cursor_moves_to_right_correctly_inside_a_line);
    CPPUNIT_TEST(text_cursor_moves_to_left_correctly_inside_a_line);
    CPPUNIT_TEST(text_cursor_moves_up_correctly);
    CPPUNIT_TEST(text_cursor_moves_down_correctly);

    CPPUNIT_TEST(text_cursor_is_set_back_to_first_line_when_moving_up);
    CPPUNIT_TEST(text_cursor_is_set_back_to_last_line_when_moving_down);

    CPPUNIT_TEST(text_cursor_moves_to_end_of_previous_line_when_moving_left_from_longer_line);
    CPPUNIT_TEST(text_cursor_moves_to_end_of_previous_line_when_moving_left_from_shorter_line);

    CPPUNIT_TEST(text_cursor_moves_to_beginning_of_next_line_when_moving_right);

    CPPUNIT_TEST(moving_down_from_longer_line_and_then_moving_left_works);
    CPPUNIT_TEST(moving_down_from_longer_line_and_then_moving_right_works);

    CPPUNIT_TEST(text_cursor_stops_at_upper_left_corner);
    CPPUNIT_TEST(text_cursor_stops_at_lower_right_corner);

    CPPUNIT_TEST(text_cursor_moves_to_end_of_line_if_next_line_is_shorter_and_moving_up);
    CPPUNIT_TEST(text_cursor_moves_to_end_of_line_if_next_line_is_shorter_and_moving_down);

    CPPUNIT_TEST(text_cursor_maintains_old_x_position_when_moving_up);
    CPPUNIT_TEST(text_cursor_maintains_old_x_position_when_moving_down);

    CPPUNIT_TEST(text_cursor_maintains_old_x_position_when_moving_up_and_down);
    CPPUNIT_TEST(text_cursor_maintains_old_x_position_when_moving_down_and_up);

    CPPUNIT_TEST(text_cursor_old_position_is_reset_when_moving_left_and_right);
    CPPUNIT_TEST(text_cursor_old_position_is_reset_when_moving_left);
    CPPUNIT_TEST(text_cursor_old_position_is_reset_when_moving_right);

    CPPUNIT_TEST(text_cursor_set_line_position_works);

    CPPUNIT_TEST(text_cursor_moves_correctly_on_text_insetion_to_back_when_no_text_wrap_happens);
    CPPUNIT_TEST(text_cursor_moves_correctly_on_text_insertion_to_back_when_new_word_is_wrapped_to_next_line);
    CPPUNIT_TEST(text_cursor_moves_correctly_on_text_insertion_to_back_when_existing_word_is_wrapped_to_next_line);
    CPPUNIT_TEST(text_cursor_moves_correctly_on_text_insertion_to_middle_when_word_wrapping_does_not_change);
    CPPUNIT_TEST(
            text_cursor_moves_correctly_on_text_insertion_to_middle_when_word_changes_but_cursor_does_not_change_line);
    CPPUNIT_TEST(
            text_cursor_moves_correctly_on_text_insertion_to_middle_when_word_changes_and_cursor_moves_to_next_line);

    CPPUNIT_TEST(text_cursor_does_not_correctly_on_text_deletion_if_deleting_from_beginning_of_first_line);
    CPPUNIT_TEST(text_cursor_moves_correctly_on_text_deletion_from_end_when_wrapping_does_not_change);
    CPPUNIT_TEST(text_cursor_moves_correctly_on_text_deletion_from_end_when_wrapping_changes);
    CPPUNIT_TEST(
            text_cursor_moves_correctly_on_text_deletion_from_the_middle_of_the_sentence_when_wrapping_does_not_change);
    CPPUNIT_TEST(text_cursor_moves_correctly_on_text_deletion_from_the_middle_of_the_sentence_when_wrapping_changes);

    CPPUNIT_TEST(text_cursor_movement_followed_by_text_insert_works_correctly);
    CPPUNIT_TEST(text_cursor_text_insert_followed_by_movement_works_correctly);CPPUNIT_TEST_SUITE_END()
    ;

public:
    TextCursorTest() {
    }
    virtual ~TextCursorTest() {
    }

    void setUp(void) {
        // cyrillic text is just randomly shortened to 5 characters; hopefully it won't turn out to be something offensive
        m_lines = {"this is a line", "this is a longer line", "хоро́ш", "Chinese 好久不見 !!"};
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

    void text_cursor_movement_on_empty_lines_sets_cursor_line_position_to_beginning() {
        std::vector<std::string> empty_lines;
        m_cursor->move_cursor( {5, 4}, empty_lines);
        assert_position(0, 0, empty_lines);
    }

    void text_cursor_does_not_move_when_no_movement_asked() {
        m_cursor->set_cursor_line_position( {5, 3}, m_lines);
        m_cursor->move_cursor( {0, 0}, m_lines);

        assert_position(5, 3);
    }

    void text_cursor_moves_to_right_correctly_inside_a_line() {
        m_cursor->move_cursor( {4, 0}, m_lines);

        assert_position(4, 0);
    }

    void text_cursor_moves_to_left_correctly_inside_a_line() {
        m_cursor->set_cursor_line_position( {10, 0}, m_lines);
        m_cursor->move_cursor( {-5, 0}, m_lines);

        assert_position(5, 0);
    }

    void text_cursor_moves_up_correctly() {
        m_cursor->set_cursor_line_position( {10, 1}, m_lines);
        m_cursor->move_cursor( {0, -1}, m_lines);
        assert_position(10, 0);
    }

    void text_cursor_moves_down_correctly() {
        m_cursor->set_cursor_line_position( {10, 0}, m_lines);
        m_cursor->move_cursor( {0, 1}, m_lines);
        assert_position(10, 1);
    }

    void text_cursor_is_set_back_to_first_line_when_moving_up() {
        m_cursor->set_cursor_line_position( {5, 0}, m_lines);
        m_cursor->move_cursor( {0, -1}, m_lines);

        assert_position(5, 0);
    }

    void text_cursor_is_set_back_to_last_line_when_moving_down() {
        m_cursor->set_cursor_line_position( {4, 3}, m_lines);
        m_cursor->move_cursor( {0, 1}, m_lines);

        assert_position(4, 3);
    }

    void text_cursor_moves_to_end_of_line_if_next_line_is_shorter_and_moving_up() {
        m_cursor->set_cursor_line_position( {20, 1}, m_lines);
        m_cursor->move_cursor( {0, -1}, m_lines);

        assert_position(14, 0);
    }

    void text_cursor_moves_to_end_of_line_if_next_line_is_shorter_and_moving_down() {
        m_cursor->set_cursor_line_position( {20, 1}, m_lines);
        m_cursor->move_cursor( {0, 1}, m_lines);

        assert_position(5, 2);
    }

    void text_cursor_moves_to_end_of_previous_line_when_moving_left_from_longer_line() {
        m_cursor->set_cursor_line_position( {0, 1}, m_lines);
        m_cursor->move_cursor( {-1, 0}, m_lines);
        assert_position(14, 0);
    }

    void text_cursor_moves_to_end_of_previous_line_when_moving_left_from_shorter_line() {
        m_cursor->set_cursor_line_position( {0, 2}, m_lines);
        m_cursor->move_cursor( {-1, 0}, m_lines);
        assert_position(21, 1);
    }

    void text_cursor_moves_to_beginning_of_next_line_when_moving_right() {
        m_cursor->set_cursor_line_position( {14, 0}, m_lines);
        m_cursor->move_cursor( {1, 0}, m_lines);
        assert_position(0, 1);
    }

    void moving_down_from_longer_line_and_then_moving_left_works() {
        m_cursor->set_cursor_line_position( {20, 1}, m_lines);
        m_cursor->move_cursor( {0, 1}, m_lines);
        m_cursor->move_cursor( {-1, 0}, m_lines);

        assert_position(4, 2);

    }

    void moving_down_from_longer_line_and_then_moving_right_works() {
        m_cursor->set_cursor_line_position( {20, 1}, m_lines);
        m_cursor->move_cursor( {0, 1}, m_lines);
        m_cursor->move_cursor( {1, 0}, m_lines);

        assert_position(0, 3);
    }

    void text_cursor_stops_at_upper_left_corner() {
        m_cursor->set_cursor_line_position( {0, 0}, m_lines);
        m_cursor->move_cursor( {-5, -2}, m_lines);

        assert_position(0, 0);
    }

    void text_cursor_stops_at_lower_right_corner() {
        m_cursor->move_cursor( {70, 5}, m_lines);

        assert_position(15, 3);
    }

    void text_cursor_maintains_old_x_position_when_moving_up() {
        m_cursor->set_cursor_line_position( {8, 3}, m_lines);
        m_cursor->move_cursor( {0, -1}, m_lines);
        m_cursor->move_cursor( {0, -1}, m_lines);

        assert_position(8, 1);
    }

    void text_cursor_maintains_old_x_position_when_moving_down() {
        m_cursor->set_cursor_line_position( {10, 1}, m_lines);

        m_cursor->move_cursor( {0, 1}, m_lines);
        m_cursor->move_cursor( {0, 1}, m_lines);

        assert_position(10, 3);
    }

    void text_cursor_maintains_old_x_position_when_moving_up_and_down() {
        m_cursor->set_cursor_line_position( {20, 1}, m_lines);

        m_cursor->move_cursor( {0, -1}, m_lines);
        m_cursor->move_cursor( {0, 1}, m_lines);

        assert_position(20, 1);
    }

    void text_cursor_maintains_old_x_position_when_moving_down_and_up() {
        m_cursor->set_cursor_line_position( {20, 1}, m_lines);

        m_cursor->move_cursor( {0, 1}, m_lines);
        m_cursor->move_cursor( {0, -1}, m_lines);

        assert_position(20, 1);
    }

    void text_cursor_old_position_is_reset_when_moving_left_and_right() {
        m_cursor->set_cursor_line_position( {20, 1}, m_lines);

        m_cursor->move_cursor( {0, 1}, m_lines);
        m_cursor->move_cursor( {-1, 0}, m_lines);
        m_cursor->move_cursor( {1, 0}, m_lines);
        m_cursor->move_cursor( {0, -1}, m_lines);

        assert_position(5, 1);
    }

    void text_cursor_old_position_is_reset_when_moving_left() {
        m_cursor->set_cursor_line_position( {20, 1}, m_lines);

        m_cursor->move_cursor( {0, -1}, m_lines);
        m_cursor->move_cursor( {-1, 0}, m_lines);
        m_cursor->move_cursor( {0, 1}, m_lines);

        assert_position(13, 1);
    }

    void text_cursor_old_position_is_reset_when_moving_right() {
        m_cursor->set_cursor_line_position( {20, 1}, m_lines);

        m_cursor->move_cursor( {0, -1}, m_lines);
        m_cursor->move_cursor( {-1, 0}, m_lines);
        m_cursor->move_cursor( {0, 1}, m_lines);

        assert_position(13, 1);
    }

    void text_cursor_set_line_position_works() {
        m_cursor->set_cursor_line_position( {10, 1}, m_lines);
        m_cursor->set_cursor_line_position( {4, 2}, m_lines);
        assert_position(4, 2);
    }

    void text_cursor_moves_correctly_on_text_insetion_to_back_when_no_text_wrap_happens() {

        std::string insertion = " and more";
        m_cursor->set_cursor_line_position( {15, 3}, m_lines);

        m_lines.back() += insertion;
        auto text_line = construct_line();

        m_cursor->text_insertion(insertion, text_line, m_lines);
        assert_position(24, 3);
    }

    void text_cursor_moves_correctly_on_text_insertion_to_back_when_new_word_is_wrapped_to_next_line() {

        m_cursor->set_cursor_line_position( {15, 3}, m_lines);

        std::string insertion = "wrapped words here";
        m_lines.push_back(insertion);
        auto text_line = construct_line();

        m_cursor->text_insertion(insertion, text_line, m_lines);

        assert_position(18, 4);
    }

    void text_cursor_moves_correctly_on_text_insertion_to_back_when_existing_word_is_wrapped_to_next_line() {
        m_cursor->set_cursor_line_position( {15, 3}, m_lines);

        std::string insertion = "blablalbalba";
        m_cursor->set_cursor_line_position( {15, 3}, m_lines);

        m_lines[3] = "Chinese 好久不見 ";

        m_lines.push_back("!!" + insertion);
        auto text_line = construct_line();

        m_cursor->text_insertion(insertion, text_line, m_lines);
        assert_position(14, 4);
    }

    void text_cursor_moves_correctly_on_text_insertion_to_middle_when_word_wrapping_does_not_change() {
        m_cursor->set_cursor_line_position( {10, 0}, m_lines);
        std::string insertion = "changed ";
        m_lines[0] = "this is a " + insertion + "line";
        auto text_line = construct_line();

        m_cursor->text_insertion(insertion, text_line, m_lines);
        assert_position(18, 0);
    }

    void text_cursor_moves_correctly_on_text_insertion_to_middle_when_word_changes_but_cursor_does_not_change_line() {
        m_cursor->set_cursor_line_position( {10, 0}, m_lines);
        std::string insertion = "changed ";
        m_lines[0] = "this is a " + insertion;
        m_lines[1] = "line " + m_lines[1];
        auto text_line = construct_line();

        m_cursor->text_insertion(insertion, text_line, m_lines);
        assert_position(18, 0);
    }

    void text_cursor_moves_correctly_on_text_insertion_to_middle_when_word_changes_and_cursor_moves_to_next_line() {
        m_cursor->set_cursor_line_position( {10, 0}, m_lines);
        std::string insertion = "changed ";
        m_lines[0] = "this is a ";
        m_lines[1] = insertion + "line " + m_lines[1];
        auto text_line = construct_line();

        m_cursor->text_insertion(insertion, text_line, m_lines);
        assert_position(8, 1);
    }

    void text_cursor_does_not_correctly_on_text_deletion_if_deleting_from_beginning_of_first_line() {
        m_cursor->set_cursor_line_position( {0, 0}, m_lines);
        m_cursor->text_deletion(0, m_lines);
        assert_position(0, 0);
    }

    void text_cursor_moves_correctly_on_text_deletion_from_end_when_wrapping_does_not_change() {
        m_cursor->set_cursor_line_position( {15, 3}, m_lines);
        m_lines[3] = "Chinese 好久不見";
        m_cursor->text_deletion(3, m_lines);
        assert_position(12, 3);
    }

    void text_cursor_moves_correctly_on_text_deletion_from_end_when_wrapping_changes() {

        m_cursor->set_cursor_line_position( {15, 3}, m_lines);
        m_lines = {"this is a line", "this is a longer line", "хоро́шChinese"};
        m_cursor->text_deletion(8, m_lines);
        assert_position(12, 2);
    }

    void text_cursor_moves_correctly_on_text_deletion_from_the_middle_of_the_sentence_when_wrapping_does_not_change() {
        m_cursor->set_cursor_line_position( {4, 0}, m_lines);
        m_lines[0] = "th is a line";
        m_cursor->text_deletion(2, m_lines);
        assert_position(2, 0);

    }
    void text_cursor_moves_correctly_on_text_deletion_from_the_middle_of_the_sentence_when_wrapping_changes() {
        m_cursor->set_cursor_line_position( {2, 1}, m_lines);
        m_lines[0] = "this is a lineis";
        m_lines[1] = " a longer line";
        m_cursor->text_deletion(2, m_lines);
        assert_position(14, 0);
    }

    void text_cursor_movement_followed_by_text_insert_works_correctly() {
        m_cursor->set_cursor_line_position( {0, 0}, m_lines);
        m_cursor->move_cursor( {2, 0}, m_lines);
        m_lines[0] = "thaais is a line";
        m_cursor->text_insertion("aa", construct_line(), m_lines);
        assert_position(4, 0);
    }

    void text_cursor_text_insert_followed_by_movement_works_correctly() {
        m_cursor->set_cursor_line_position( {0, 0}, m_lines);
        m_lines[0] = "aathis is a line";
        m_cursor->text_insertion("aa", construct_line(), m_lines);
        m_cursor->move_cursor( {2, 0}, m_lines);
        assert_position(4, 0);
    }

    std::string construct_line() {
        std::string text_line = "";
        bool first_line = true;
        for (auto &line : m_lines) {
            if (!first_line) {
                text_line += " ";
            }

            text_line += line;
            first_line = false;
        }
        return text_line;
    }

    void assert_position(int x, int y) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect x position", x, m_cursor->cursor_line_position(m_lines).x);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect y position", y, m_cursor->cursor_line_position(m_lines).y);
    }

    void assert_position(int x, int y, const std::vector<std::string> &lines) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect x position", x, m_cursor->cursor_line_position(lines).x);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect y position", y, m_cursor->cursor_line_position(lines).y);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TextCursorTest);
} /* ńamespace sdl_gui */

#endif /* TEXTCURSORTEST_H_ */
