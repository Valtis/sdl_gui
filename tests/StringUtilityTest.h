#ifndef STRINGUTILITYTEST_H_
#define STRINGUTILITYTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../src/utility/StringUtility.h"

namespace sdl_gui {

class StringUtilityTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(StringUtilityTest);

    CPPUNIT_TEST(tokenize_returns_empty_vector_for_empty_string);
    CPPUNIT_TEST(tokenize_returns_vector_with_correct_size_if_no_separator_is_found_from_string);
    CPPUNIT_TEST(tokenize_returns_vector_with_correct_content_if_no_separator_is_found_from_string);
    CPPUNIT_TEST(tokenize_returns_vector_with_correct_size_if_separator_is_found_from_string);
    CPPUNIT_TEST(tokenize_returns_vector_with_correct_content_if_separator_is_found_from_string);
    CPPUNIT_TEST(tokenize_returns_vector_with_correct_size_if_multiple_separators_are_in_row_in_string);
    CPPUNIT_TEST(tokenize_returns_vector_with_correct_content_if_multiple_separators_are_in_row_in_string);

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

    CPPUNIT_TEST_SUITE_END();

public:
    StringUtilityTest() { }
	virtual ~StringUtilityTest() { }

    void setUp(void) {}
    void tearDown(void) {}

private:

    void tokenize_returns_empty_vector_for_empty_string() {
    	auto result = utility::tokenize("", ' ');
    	CPPUNIT_ASSERT_EQUAL((size_t)0, result.size());
    }

    void tokenize_returns_vector_with_correct_size_if_no_separator_is_found_from_string() {
    	auto result = utility::tokenize("string_to_tokenize", '*');
    	CPPUNIT_ASSERT_EQUAL((size_t)1, result.size());
    }

    void tokenize_returns_vector_with_correct_content_if_no_separator_is_found_from_string() {
    	auto result = utility::tokenize("string_to_tokenize", '*');
    	CPPUNIT_ASSERT_EQUAL(std::string("string_to_tokenize"), result.at(0));
    }

    void tokenize_returns_vector_with_correct_size_if_separator_is_found_from_string() {
    	auto result = utility::tokenize("string_to_ tokenize ", '_');
    	CPPUNIT_ASSERT_EQUAL((size_t)3, result.size());
    }

    void tokenize_returns_vector_with_correct_content_if_separator_is_found_from_string() {
    	auto result = utility::tokenize("string_to_ tokenize ", '_');
    	CPPUNIT_ASSERT_EQUAL(std::string("string"), result.at(0));
    	CPPUNIT_ASSERT_EQUAL(std::string("to"), result.at(1));
    	CPPUNIT_ASSERT_EQUAL(std::string(" tokenize "), result.at(2));
    }

    void tokenize_returns_vector_with_correct_size_if_multiple_separators_are_in_row_in_string() {
    	auto result = utility::tokenize("string_____________to_____ tokenize ", '_');
		CPPUNIT_ASSERT_EQUAL((size_t)3, result.size());
    }

    void tokenize_returns_vector_with_correct_content_if_multiple_separators_are_in_row_in_string() {
    	auto result = utility::tokenize("string_____________to_____ tokenize ", '_');
    	CPPUNIT_ASSERT_EQUAL(std::string("string"), result.at(0));
    	CPPUNIT_ASSERT_EQUAL(std::string("to"), result.at(1));
    	CPPUNIT_ASSERT_EQUAL(std::string(" tokenize "), result.at(2));
    }

	void word_wrap_does_not_wrap_text_that_fits_the_field() {
		auto renderer = std::make_shared<TestRenderer>();
		std::string text = "This is a test";
		auto wrapped_text = utility::wrap_text(text, 12,  renderer.get(), {0, 0, 200, 200}, { 0, 0 });
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect number of lines created when wrapping text", (size_t)1, wrapped_text.size());
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", text, wrapped_text[0]);
	}

	void word_wrap_wraps_two_liner_correctly() {
		auto renderer = std::make_shared<TestRenderer>();
		std::string text = "This is a test line";
		auto wrapped_text = utility::wrap_text(text, 12,  renderer.get(), {0, 0, 15, 200}, { 0, 0 });
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect number of lines created when wrapping text", (size_t)2, wrapped_text.size());
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("This is a test"), wrapped_text[0]);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("line"), wrapped_text[1]);
	}

	void word_wrap_does_not_split_word_from_middle() {
		auto renderer = std::make_shared<TestRenderer>();
		std::string text = "This is largeish test line";
		auto wrapped_text = utility::wrap_text(text, 12, renderer.get(), {0, 0, 15, 200}, { 0, 0 });
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect number of lines created when wrapping text", (size_t)3, wrapped_text.size());
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("This is"), wrapped_text[0]);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("largeish test"), wrapped_text[1]);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("line"), wrapped_text[2]);
	}

	void word_wrap_splist_correctly_when_long_word_is_first() {
		auto renderer = std::make_shared<TestRenderer>();
		std::string text = "gigantic_word_for_testing foo bar";
		auto wrapped_text = utility::wrap_text(text, 12, renderer.get(), {0, 0, 15, 200}, { 0, 0 });
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect number of lines created when wrapping text", (size_t)2, wrapped_text.size());
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("gigantic_word_for_testing"), wrapped_text[0]);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("foo bar"), wrapped_text[1]);
	}

	void word_wrap_splist_correctly_when_long_word_is_last() {
		auto renderer = std::make_shared<TestRenderer>();
		std::string text = "foo bar gigantic_word_for_testing";
		auto wrapped_text = utility::wrap_text(text, 12, renderer.get(), {0, 0, 15, 200}, { 0, 0 });
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect number of lines created when wrapping text", (size_t)2, wrapped_text.size());
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("foo bar"), wrapped_text[0]);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("gigantic_word_for_testing"), wrapped_text[1]);
	}

	void word_wrap_does_not_split_word_that_is_too_long_to_fit_single_line() {
   		auto renderer = std::make_shared<TestRenderer>();
   		std::string text = "This is gigantic_word_for_testing test line";
   		auto wrapped_text = utility::wrap_text(text, 12, renderer.get(), {0, 0, 15, 200}, { 0, 0 });
   		CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect number of lines created when wrapping text", (size_t)3, wrapped_text.size());
   		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("This is"), wrapped_text[0]);
   		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("gigantic_word_for_testing"), wrapped_text[1]);
   		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("test line"), wrapped_text[2]);
   	}

	void word_wrap_splits_with_left_offset_correctly() {
		auto renderer = std::make_shared<TestRenderer>();
		std::string text = "This is a test line";
		auto wrapped_text = utility::wrap_text(text, 12,  renderer.get(), {0, 0, 15, 200}, { 5, 0 });
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect number of lines created when wrapping text", (size_t)2, wrapped_text.size());
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("This is a"), wrapped_text[0]);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("test line"), wrapped_text[1]);
	}

	void word_wrap_splits_with_right_offset_correctly() {
		auto renderer = std::make_shared<TestRenderer>();
		std::string text = "This is a test line";
		auto wrapped_text = utility::wrap_text(text, 12,  renderer.get(), {0, 0, 15, 200}, { 0, 5 });
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect number of lines created when wrapping text", (size_t)2, wrapped_text.size());
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("This is a"), wrapped_text[0]);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("test line"), wrapped_text[1]);
	}

	void word_wrap_splits_with_both_offsets_correctly() {
		auto renderer = std::make_shared<TestRenderer>();
		std::string text = "This is a test line";
		auto wrapped_text = utility::wrap_text(text, 12,  renderer.get(), {0, 0, 15, 200}, { 5, 5 });
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect number of lines created when wrapping text", (size_t)4, wrapped_text.size());
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("This"), wrapped_text[0]);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("is a"), wrapped_text[1]);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("test"), wrapped_text[2]);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("line"), wrapped_text[3]);
	}

	void word_wrap_splits_with_both_offsets_correctly_with_long_word() {
		auto renderer = std::make_shared<TestRenderer>();
		std::string text = "This is gigantic_word_for_testing test line";
		auto wrapped_text = utility::wrap_text(text, 12, renderer.get(), {0, 0, 25, 200}, { 5, 5 });
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect number of lines created when wrapping text", (size_t)3, wrapped_text.size());
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("This is"), wrapped_text[0]);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("gigantic_word_for_testing"), wrapped_text[1]);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Invalid text", std::string("test line"), wrapped_text[2]);
	}

};




CPPUNIT_TEST_SUITE_REGISTRATION( StringUtilityTest);
} /* ńamespace sdl_gui */

#endif /* STRINGUTILITYTEST_H_ */
