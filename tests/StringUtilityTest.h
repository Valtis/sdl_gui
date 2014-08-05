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

};




CPPUNIT_TEST_SUITE_REGISTRATION( StringUtilityTest);
} /* ńamespace sdl_gui */

#endif /* STRINGUTILITYTEST_H_ */
