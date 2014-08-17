#ifndef STRINGUTILITYTEST_H_
#define STRINGUTILITYTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../src/utility/StringUtility.h"

namespace sdl_gui {

class StringUtilityTest: public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE(StringUtilityTest);

    CPPUNIT_TEST(tokenize_returns_empty_vector_for_empty_string);
    CPPUNIT_TEST(tokenize_returns_vector_with_correct_content_if_no_separator_is_found_from_string);
    CPPUNIT_TEST(tokenize_returns_vector_with_correct_content_if_separator_is_found_from_string);
    CPPUNIT_TEST(tokenize_returns_vector_with_correct_content_if_multiple_separators_are_in_row_in_string);
    CPPUNIT_TEST(tokenize_returns_delimiters_if_include_delimiters_is_true);

    CPPUNIT_TEST(word_wrap_does_not_wrap_text_that_fits_the_field);
    CPPUNIT_TEST(word_wrap_wraps_two_liner_correctly);
    CPPUNIT_TEST(word_wrap_does_not_split_word_from_middle);
    CPPUNIT_TEST(word_wrap_splist_correctly_when_long_word_is_first);
    CPPUNIT_TEST(word_wrap_splist_correctly_when_long_word_is_last);
    CPPUNIT_TEST(word_wrap_does_not_split_word_that_is_too_long_to_fit_single_line);
    CPPUNIT_TEST(word_wrap_splits_with_left_offset_correctly);
    CPPUNIT_TEST(word_wrap_splits_with_right_offset_correctly);
    CPPUNIT_TEST(word_wrap_splits_with_both_offsets_correctly);
    CPPUNIT_TEST(word_wrap_splits_with_both_offsets_correctly_with_long_word);
    CPPUNIT_TEST(word_wrap_preserves_multiple_spaces_correctly_in_a_sentence);

    CPPUNIT_TEST(erase_does_not_erase_ascii_if_char_count_is_zero);
    CPPUNIT_TEST(erase_does_not_erase_ascii_if_char_count_is_negative);
    CPPUNIT_TEST(erase_returns_empty_string_if_count_is_larger_than_char_count_in_ascii);
    CPPUNIT_TEST(erase_removes_single_character_from_ascii_correctly);
    CPPUNIT_TEST(erase_removes_multiple_characters_from_ascii_correctly);
    CPPUNIT_TEST(erase_removes_all_characters_from_ascii_correctly);
    CPPUNIT_TEST(erase_handles_white_space);

    CPPUNIT_TEST(erase_does_not_erase_cyrillic_if_char_count_is_zero);
    CPPUNIT_TEST(erase_does_not_erase_cyrillic_if_char_count_is_negative);
    CPPUNIT_TEST(erase_returns_empty_string_if_count_is_larger_than_char_count_in_cyrillic);
    CPPUNIT_TEST(erase_removes_single_character_from_cyrillic_correctly);
    CPPUNIT_TEST(erase_removes_multiple_characters_from_cyrillic_correctly);
    CPPUNIT_TEST(erase_removes_all_characters_from_cyrillic_correctly);

    CPPUNIT_TEST(erase_removes_multiple_characters_from_mix_of_ascii_and_cyrillic_correctly);
    CPPUNIT_TEST(erase_removes_all_characters_from_mix_of_ascii_and_cyrillic_correctly);

    CPPUNIT_TEST(erase_removes_single_chinese_character);
    CPPUNIT_TEST(erase_removes_multiple_chinese_characters);
    CPPUNIT_TEST(erase_removes_mix_of_chinese_and_ascii);

    CPPUNIT_TEST(erase_from_before_position_does_nothing_if_deleting_characters_from_beginning);
    CPPUNIT_TEST(erase_from_before_position_deletes_from_middle);
    CPPUNIT_TEST(
            erase_from_before_position_deletes_all_characters_from_position_if_requested_deletion_is_larger_than_position);
    CPPUNIT_TEST(erase_from_before_position_deletes_from_end);

    CPPUNIT_TEST(erase_from_after_position_removes_characters_from_beginning);
    CPPUNIT_TEST(erase_from_after_position_removes_characters_from_middle);
    CPPUNIT_TEST(erase_from_after_position_does_nothing_if_deleting_characters_from_the_end);
    CPPUNIT_TEST(
            erase_from_after_position_deletes_all_characters_if_requested_deletion_is_larger_than_the_remaining_string);

    CPPUNIT_TEST(substring_returns_empty_string_on_empty_input);
    CPPUNIT_TEST(substring_returns_empty_string_on_empty_input_and_with_large_length);
    CPPUNIT_TEST(substring_returns_empty_string_on_empty_input_and_with_large_initial_position);

    CPPUNIT_TEST(substring_returns_correct_string_with_ascii_when_initial_position_is_in_the_beginning);
    CPPUNIT_TEST(substring_returns_correct_string_with_ascii_when_initial_position_is_not_in_the_beginning);
    CPPUNIT_TEST(substring_returns_correct_string_with_ascii_if_length_is_larger_than_text_length);
    CPPUNIT_TEST(substring_returns_correct_string_with_ascii_if_length_is_exactly_text_length);

    CPPUNIT_TEST(substring_returns_correct_string_with_cyrillic_when_initial_position_is_in_the_beginning);
    CPPUNIT_TEST(substring_returns_correct_string_with_cyrillic_when_initial_position_is_not_in_the_beginning);
    CPPUNIT_TEST(substring_returns_correct_string_with_cyrillic_if_length_is_larger_than_text_length);
    CPPUNIT_TEST(substring_returns_correct_string_with_cyrillic_if_length_is_exactly_text_length);

    CPPUNIT_TEST(
            substring_returns_correct_string_with_mix_of_ascii_and_cyrillic_when_initial_position_is_in_the_beginning);
    CPPUNIT_TEST(
            substring_returns_correct_string_with_mix_of_ascii_and_cyrillic_when_initial_position_is_not_in_the_beginning);
    CPPUNIT_TEST(substring_returns_correct_string_with_mix_of_ascii_and_cyrillic_if_length_is_larger_than_text_length);
    CPPUNIT_TEST(substring_returns_correct_string_with_mix_of_ascii_and_cyrillic_if_length_is_exactly_text_length);

    CPPUNIT_TEST(glyph_count_returns_0_for_empty_string);
    CPPUNIT_TEST(glyph_count_returns_correct_count_for_ascii);
    CPPUNIT_TEST(glyph_count_returns_correct_count_for_cyrillic);
    CPPUNIT_TEST(glyph_count_returns_correct_count_for_chinese);
    CPPUNIT_TEST(glyph_count_returns_correct_count_for_mixed_string);

    CPPUNIT_TEST(adding_to_beginning_of_string_works);
    CPPUNIT_TEST(adding_to_middle_of_string_works);
    CPPUNIT_TEST(adding_to_end_of_string_works);

    CPPUNIT_TEST_SUITE_END()
    ;

public:
    StringUtilityTest() {
    }
    virtual ~StringUtilityTest() {
    }

    void setUp(void) {
    }
    void tearDown(void) {
    }

private:

    void tokenize_returns_empty_vector_for_empty_string() {
        auto result = utility::tokenize("", ' ');
        assert_tokenization_is_correct( { }, result);
    }

    void tokenize_returns_vector_with_correct_content_if_no_separator_is_found_from_string() {
        auto result = utility::tokenize("string_to_tokenize", '*');
        assert_tokenization_is_correct( { "string_to_tokenize" }, result);
    }

    void tokenize_returns_vector_with_correct_content_if_separator_is_found_from_string() {
        auto result = utility::tokenize("string_to_ tokenize ", '_');
        assert_tokenization_is_correct( { "string", "to", " tokenize " }, result);
    }

    void tokenize_returns_vector_with_correct_content_if_multiple_separators_are_in_row_in_string() {
        auto result = utility::tokenize("string_____________to_____ tokenize ", '_');
        assert_tokenization_is_correct( { "string", "to", " tokenize " }, result);
    }

    void tokenize_returns_delimiters_if_include_delimiters_is_true() {
        auto result = utility::tokenize("this_is_a__string", '_', true);
        assert_tokenization_is_correct( { "this", "_", "is", "_", "a", "_", "_", "string" }, result);
    }

    void assert_tokenization_is_correct(const std::vector<std::string> &expected,
            const std::vector<std::string> &actual) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect number of tokens created when tokenizing", expected.size(),
                actual.size());
        for (size_t i = 0; i < expected.size(); ++i) {
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Tokens do not match", expected[i], actual[i]);
        }
    }

    void word_wrap_does_not_wrap_text_that_fits_the_field() {
        auto wrapped_text = wrap("This is a test", { 0, 0, 200, 200 }, { 0, 0 });
        assert_word_wrap_content_is_correct( { "This is a test" }, wrapped_text);
    }

    void word_wrap_wraps_two_liner_correctly() {
        auto wrapped_text = wrap("This is a test line", { 0, 0, 15, 200 }, { 0, 0 });
        assert_word_wrap_content_is_correct( { "This is a test ", "line" }, wrapped_text);
    }

    void word_wrap_does_not_split_word_from_middle() {
        auto wrapped_text = wrap("This is largeish test line", { 0, 0, 15, 200 }, { 0, 0 });
        assert_word_wrap_content_is_correct( { "This is ", "largeish test ", "line" }, wrapped_text);
    }

    void word_wrap_splist_correctly_when_long_word_is_first() {
        auto wrapped_text = wrap("gigantic_word_for_testing foo bar", { 0, 0, 15, 200 }, { 0, 0 });
        assert_word_wrap_content_is_correct( { "gigantic_word_for_testing", " foo bar" }, wrapped_text);
    }

    void word_wrap_splist_correctly_when_long_word_is_last() {
        auto wrapped_text = wrap("foo bar gigantic_word_for_testing", { 0, 0, 15, 200 }, { 0, 0 });
        assert_word_wrap_content_is_correct( { "foo bar ", "gigantic_word_for_testing" }, wrapped_text);
    }

    void word_wrap_does_not_split_word_that_is_too_long_to_fit_single_line() {
        auto wrapped_text = wrap("This is gigantic_word_for_testing test line", { 0, 0, 15, 200 }, { 0, 0 });
        assert_word_wrap_content_is_correct( { "This is ", "gigantic_word_for_testing", " test line" }, wrapped_text);
    }

    void word_wrap_splits_with_left_offset_correctly() {
        auto wrapped_text = wrap("This is a test line", { 0, 0, 15, 200 }, { 5, 0 });
        assert_word_wrap_content_is_correct( { "This is a ", "test line" }, wrapped_text);
    }

    void word_wrap_splits_with_right_offset_correctly() {
        auto wrapped_text = wrap("This is a test line", { 0, 0, 15, 200 }, { 0, 5 });
        assert_word_wrap_content_is_correct( { "This is a ", "test line" }, wrapped_text);
    }

    void word_wrap_splits_with_both_offsets_correctly() {
        auto wrapped_text = wrap("This is a test line", { 0, 0, 15, 200 }, { 5, 5 });
        assert_word_wrap_content_is_correct( { "This ", "is a ", "test ", "line" }, wrapped_text);
    }

    void word_wrap_splits_with_both_offsets_correctly_with_long_word() {
        auto wrapped_text = wrap("This is gigantic_word_for_testing test line", { 0, 0, 25, 200 }, { 5, 5 });
        assert_word_wrap_content_is_correct( { "This is ", "gigantic_word_for_testing", " test line" }, wrapped_text);
    }

    void word_wrap_preserves_multiple_spaces_correctly_in_a_sentence() {
        auto wrapped_text = wrap("  this  is  a      sentence with  multiple  spaces  ", { 0, 0, 20, 200 }, { 0, 0 });
        assert_word_wrap_content_is_correct( { "  this  is  a      ", "sentence with  ", "multiple  spaces  " },
                wrapped_text);
    }

    std::vector<std::string> wrap(std::string text, SDL_Rect textbox_size, std::pair<int, int> offset) {
        auto renderer = std::make_shared<TestRenderer>();
        return utility::wrap_text(text, 12, renderer.get(), textbox_size, offset);
    }

    void assert_word_wrap_content_is_correct(const std::vector<std::string> &expected,
            const std::vector<std::string> &actual) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect number of lines created when wrapping text", expected.size(),
                actual.size());
        for (size_t i = 0; i < expected.size(); ++i) {
            CPPUNIT_ASSERT_EQUAL_MESSAGE("Wrapped line does not match", expected[i], actual[i]);
        }
    }

    void erase_does_not_erase_ascii_if_char_count_is_zero() {
        std::string text = "helloo!";
        auto result = utility::erase_from_end_utf8(text, 0);
        CPPUNIT_ASSERT_EQUAL(text, result);
    }

    void erase_does_not_erase_ascii_if_char_count_is_negative() {
        std::string text = "helloo!";
        auto result = utility::erase_from_end_utf8(text, -1);
        CPPUNIT_ASSERT_EQUAL(text, result);
    }

    void erase_returns_empty_string_if_count_is_larger_than_char_count_in_ascii() {
        std::string text = "helloo!";
        auto result = utility::erase_from_end_utf8(text, 255);
        CPPUNIT_ASSERT(result.empty());
    }

    void erase_removes_single_character_from_ascii_correctly() {
        std::string text = "helloo!";
        std::string expected = "helloo";
        auto result = utility::erase_from_end_utf8(text, 1);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_removes_multiple_characters_from_ascii_correctly() {
        std::string text = "helloo!";
        std::string expected = "hell";
        auto result = utility::erase_from_end_utf8(text, 3);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_removes_all_characters_from_ascii_correctly() {
        std::string text = "helloo!";
        auto result = utility::erase_from_end_utf8(text, 7);
        CPPUNIT_ASSERT(result.empty());
    }

    void erase_does_not_erase_cyrillic_if_char_count_is_zero() {
        std::string text = "молоде́ц";
        auto result = utility::erase_from_end_utf8(text, 0);
        CPPUNIT_ASSERT_EQUAL(text, result);
    }

    void erase_does_not_erase_cyrillic_if_char_count_is_negative() {
        std::string text = "молоде́ц";
        auto result = utility::erase_from_end_utf8(text, -1);
        CPPUNIT_ASSERT_EQUAL(text, result);
    }

    void erase_returns_empty_string_if_count_is_larger_than_char_count_in_cyrillic() {
        std::string text = "молоде́ц";
        auto result = utility::erase_from_end_utf8(text, 255);
        CPPUNIT_ASSERT(result.empty());
    }

    void erase_removes_single_character_from_cyrillic_correctly() {
        std::string text = "молоде́ц";
        std::string expected = "молоде́";
        auto result = utility::erase_from_end_utf8(text, 1);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_removes_multiple_characters_from_cyrillic_correctly() {
        std::string text = "молоде́ц";
        std::string expected = "моло";
        auto result = utility::erase_from_end_utf8(text, 3);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_removes_all_characters_from_cyrillic_correctly() {
        std::string text = "молоде́ц";
        auto result = utility::erase_from_end_utf8(text, 7);
        CPPUNIT_ASSERT(result.empty());
    }
    void erase_removes_multiple_characters_from_mix_of_ascii_and_cyrillic_correctly() {
        std::string text = "молодaе́ц!";
        std::string expected = "молод";
        auto result = utility::erase_from_end_utf8(text, 4);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_removes_all_characters_from_mix_of_ascii_and_cyrillic_correctly() {
        std::string text = "молодaе́ц!";
        auto result = utility::erase_from_end_utf8(text, 9);
        CPPUNIT_ASSERT(result.empty());
    }

    void erase_removes_single_chinese_character() {
        std::string text = "茅台酒";
        std::string expected = "茅台";
        auto result = utility::erase_from_end_utf8(text, 1);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_removes_multiple_chinese_characters() {
        std::string text = "好久不見";
        std::string expected = "好久";
        auto result = utility::erase_from_end_utf8(text, 2);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_removes_mix_of_chinese_and_ascii() {
        std::string text = "好久!!不a見va";
        std::string expected = "好久!";
        auto result = utility::erase_from_end_utf8(text, 6);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_handles_white_space() {
        std::string text = "abc def ghi jkl";
        std::string expected = "abc def g";
        auto result = utility::erase_from_end_utf8(text, 6);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_from_before_position_does_nothing_if_deleting_characters_from_beginning() {
        std::string text = "хоро́ший ascii 好久不見";
        std::string expected = "хоро́ший ascii 好久不見";
        auto result = utility::erase_from_before_position_utf8(text, 0, 5);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_from_before_position_deletes_from_middle() {
        std::string text = "хоро́ший ascii 好久不見";
        std::string expected = "хоий ascii 好久不見";
        auto result = utility::erase_from_before_position_utf8(text, 3, 5);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_from_before_position_deletes_all_characters_from_position_if_requested_deletion_is_larger_than_position() {
        std::string text = "хоро́ший ascii 好久不見";
        std::string expected = "ий ascii 好久不見";
        auto result = utility::erase_from_before_position_utf8(text, 7, 5);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_from_before_position_deletes_from_end() {
        std::string text = "хоро́ший ascii 好久不見";
        std::string expected = "хоро́ший ascii 好";
        auto result = utility::erase_from_before_position_utf8(text, 3, 18);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_from_after_position_removes_characters_from_beginning() {
        std::string text = "хоро́ший ascii 好久不見";
        std::string expected = "cii 好久不見";
        auto result = utility::erase_from_after_position_utf8(text, 10, 0);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_from_after_position_removes_characters_from_middle() {
        std::string text = "хоро́ший ascii 好久不見";
        std::string expected = "хоро́ший as久不見";
        auto result = utility::erase_from_after_position_utf8(text, 5, 10);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_from_after_position_does_nothing_if_deleting_characters_from_the_end() {
        std::string text = "хоро́ший ascii 好久不見";
        std::string expected = text;
        auto result = utility::erase_from_after_position_utf8(text, 10, 18);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void erase_from_after_position_deletes_all_characters_if_requested_deletion_is_larger_than_the_remaining_string() {
        std::string text = "хоро́ший ascii 好久不見";
        std::string expected = "хоро́ший asci";
        auto result = utility::erase_from_after_position_utf8(text, 255, 12);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }

    void substring_returns_empty_string_on_empty_input() {
        CPPUNIT_ASSERT_EQUAL(std::string(""), utility::substring_utf8("", 0, 0));
    }

    void substring_returns_empty_string_on_empty_input_and_with_large_length() {
        CPPUNIT_ASSERT_EQUAL(std::string(""), utility::substring_utf8("", 0, 159));
    }

    void substring_returns_empty_string_on_empty_input_and_with_large_initial_position() {
        CPPUNIT_ASSERT_EQUAL(std::string(""), utility::substring_utf8("", 24, 159));
    }

    void substring_returns_correct_string_with_ascii_when_initial_position_is_in_the_beginning() {
        CPPUNIT_ASSERT_EQUAL(std::string("abc"), utility::substring_utf8("abcdefgh", 0, 3));
    }

    void substring_returns_correct_string_with_ascii_when_initial_position_is_not_in_the_beginning() {
        CPPUNIT_ASSERT_EQUAL(std::string("cde"), utility::substring_utf8("abcdefgh", 2, 3));
    }

    void substring_returns_correct_string_with_ascii_if_length_is_larger_than_text_length() {
        CPPUNIT_ASSERT_EQUAL(std::string("abcdefgh"), utility::substring_utf8("abcdefgh", 0, 124));
    }

    void substring_returns_correct_string_with_ascii_if_length_is_exactly_text_length() {
        CPPUNIT_ASSERT_EQUAL(std::string("abcdefgh"), utility::substring_utf8("abcdefgh", 0, 8));
    }

    void substring_returns_correct_string_with_cyrillic_when_initial_position_is_in_the_beginning() {
        CPPUNIT_ASSERT_EQUAL(std::string("хор"), utility::substring_utf8("хоро́ший", 0, 3));
    }

    void substring_returns_correct_string_with_cyrillic_when_initial_position_is_not_in_the_beginning() {
        CPPUNIT_ASSERT_EQUAL(std::string("ро́ш"), utility::substring_utf8("хоро́ший", 2, 3));
    }

    void substring_returns_correct_string_with_cyrillic_if_length_is_larger_than_text_length() {
        CPPUNIT_ASSERT_EQUAL(std::string("хоро́ший"), utility::substring_utf8("хоро́ший", 0, 124));
    }

    void substring_returns_correct_string_with_cyrillic_if_length_is_exactly_text_length() {
        CPPUNIT_ASSERT_EQUAL(std::string("хоро́ший"), utility::substring_utf8("хоро́ший", 0, 7));
    }

    void substring_returns_correct_string_with_mix_of_ascii_and_cyrillic_when_initial_position_is_in_the_beginning() {
        CPPUNIT_ASSERT_EQUAL(std::string("хор"), utility::substring_utf8("хоро́ший", 0, 3));
    }

    void substring_returns_correct_string_with_mix_of_ascii_and_cyrillic_when_initial_position_is_not_in_the_beginning() {
        CPPUNIT_ASSERT_EQUAL(std::string("ро́ш"), utility::substring_utf8("хоро́ший", 2, 3));
    }

    void substring_returns_correct_string_with_mix_of_ascii_and_cyrillic_if_length_is_larger_than_text_length() {
        CPPUNIT_ASSERT_EQUAL(std::string("хоро́ший"), utility::substring_utf8("хоро́ший", 0, 124));
    }

    void substring_returns_correct_string_with_mix_of_ascii_and_cyrillic_if_length_is_exactly_text_length() {
        CPPUNIT_ASSERT_EQUAL(std::string("хоро́ший"), utility::substring_utf8("хоро́ший", 0, 7));
    }

    void glyph_count_returns_0_for_empty_string() {
        CPPUNIT_ASSERT_EQUAL(0, utility::glyph_count_utf8(""));
    }

    void glyph_count_returns_correct_count_for_ascii() {
        CPPUNIT_ASSERT_EQUAL(11, utility::glyph_count_utf8("hello world"));
    }

    void glyph_count_returns_correct_count_for_cyrillic() {
        CPPUNIT_ASSERT_EQUAL(15, utility::glyph_count_utf8("хоро́ший хоро́ший"));
    }

    void glyph_count_returns_correct_count_for_chinese() {
        CPPUNIT_ASSERT_EQUAL(9, utility::glyph_count_utf8("好久不見 好久不見"));
    }

    void glyph_count_returns_correct_count_for_mixed_string() {
        CPPUNIT_ASSERT_EQUAL(18, utility::glyph_count_utf8("хоро́ший ascii 好久不見"));
    }

    void adding_to_beginning_of_string_works() {
        std::string text = "хоро́ший ascii 好久不見";
        std::string addition = "*好久хоро́ascii*";
        CPPUNIT_ASSERT_EQUAL(std::string("*好久хоро́ascii*хоро́ший ascii 好久不見"),
                utility::add_text_to_position_utf8(text, addition, 0));
    }

    void adding_to_middle_of_string_works() {
        std::string text = "хоро́ший ascii 好久不見";
        std::string addition = "*好久хоро́ascii*";
        CPPUNIT_ASSERT_EQUAL(std::string("хоро́ш*好久хоро́ascii*ий ascii 好久不見"),
                utility::add_text_to_position_utf8(text, addition, 5));
    }

    void adding_to_end_of_string_works() {
        std::string text = "хоро́ший ascii 好久不見";
        std::string addition = "*好久хоро́ascii*";
        CPPUNIT_ASSERT_EQUAL(std::string("хоро́ший ascii 好久不見*好久хоро́ascii*"),
                utility::add_text_to_position_utf8(text, addition, 18));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(StringUtilityTest);
} /* ńamespace sdl_gui */

#endif /* STRINGUTILITYTEST_H_ */
