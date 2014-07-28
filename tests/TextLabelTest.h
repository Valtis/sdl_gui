#ifndef TEXTLABELTEST_H_
#define TEXTLABELTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../src/components/TextLabel.h"
#include "mocks/TestRenderer.h"
#include "mocks/TestTextureFactory.h"

namespace sdl_gui {

class TextLabelTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TextLabelTest);

    CPPUNIT_TEST(set_text_works);

    CPPUNIT_TEST(empty_label_width_and_height_is_zero);
    CPPUNIT_TEST(set_text_sets_width_and_height_if_unset_before);
    CPPUNIT_TEST(label_enforces_maximum_width_and_height_through_set_text);
    CPPUNIT_TEST(label_enforces_maximum_width_and_height_through_set_dimension);
    CPPUNIT_TEST(set_font_size_changes_width_and_height);


    CPPUNIT_TEST(set_horizontal_alignment_to_left_sets_x_correctly);
    CPPUNIT_TEST(set_horizontal_alignment_to_left_with_offset_sets_x_correctly);
    CPPUNIT_TEST(set_horizontal_alignment_to_center_sets_x_correctly);
    CPPUNIT_TEST(set_horizontal_alignment_to_center_with_offset_sets_x_correctly);
    CPPUNIT_TEST(set_horizontal_alignment_to_right_sets_x_correctly);
    CPPUNIT_TEST(set_horizontal_alignment_to_right_with_offset_sets_x_correctly);


    CPPUNIT_TEST(set_vertical_alignment_to_top_sets_y_correctly);
    CPPUNIT_TEST(set_vertical_alignment_to_top_with_offset_sets_y_correctly);
    CPPUNIT_TEST(set_vertical_alignment_to_center_sets_y_correctly);
    CPPUNIT_TEST(set_vertical_alignment_to_center_with_offset_sets_y_correctly);
    CPPUNIT_TEST(set_vertical_alignment_to_bottom_sets_y_correctly);
    CPPUNIT_TEST(set_vertical_alignment_to_bottom_with_offset_sets_y_correctly);


    CPPUNIT_TEST_SUITE_END();

public:
    TextLabelTest() { }
	virtual ~TextLabelTest() { }

    void setUp(void) {
    	m_renderer = std::make_shared<TestRenderer>();
    	m_factory = std::make_shared<TestTextureFactory>();
    	m_label = std::make_shared<TextLabel>(m_factory);
    	m_label->set_renderer(m_renderer.get());
    }
    void tearDown(void) {}

private:
    std::shared_ptr<TestRenderer> m_renderer;
    std::shared_ptr<TestTextureFactory> m_factory;
    std::shared_ptr<TextLabel> m_label;

    void set_text_works() {
    	m_label->set_text("12345");
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Text was not set correctly", std::string("12345"), m_label->get_text());
    }

    void empty_label_width_and_height_is_zero() {
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Width should be zero", 0, m_label->relative_dimension().w);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Height should be zero", 0, m_label->relative_dimension().h);
    }

    void set_text_sets_width_and_height_if_unset_before() {
    	m_renderer->m_texture_width=40;
    	m_renderer->m_texture_height=20;
    	m_label->set_text("abcd");

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Width should be 40", 40, m_label->relative_dimension().w);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Height should be 20", 20, m_label->relative_dimension().h);
    }

    void label_enforces_maximum_width_and_height_through_set_text() {
    	m_renderer->m_texture_width=40;
    	m_renderer->m_texture_height=20;
    	m_label->set_text("abcd");

    	m_renderer->m_texture_width=80;
    	m_renderer->m_texture_height=50;

    	m_label->set_text("abcd");

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Width should be 40", 40, m_label->relative_dimension().w);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Height should be 20", 20, m_label->relative_dimension().h);
    }


    void label_enforces_maximum_width_and_height_through_set_dimension() {
    	m_label->set_relative_dimension({0, 0, 40, 20});

    	m_renderer->m_texture_width=80;
    	m_renderer->m_texture_height=50;

    	m_label->set_text("abcd");

    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Width should be 40", 40, m_label->relative_dimension().w);
    	CPPUNIT_ASSERT_EQUAL_MESSAGE("Height should be 20", 20, m_label->relative_dimension().h);
    }

    void set_font_size_changes_width_and_height() {
    	m_renderer->m_texture_width=40;
		m_renderer->m_texture_height=20;
		m_label->set_text("abcd");

		m_renderer->m_texture_width=20;
		m_renderer->m_texture_height=10;

		m_label->set_font_size(10);

		CPPUNIT_ASSERT_EQUAL_MESSAGE("Width should be 20", 20, m_label->relative_dimension().w);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Height should be 10", 10, m_label->relative_dimension().h);
    }

    void set_horizontal_alignment_to_left_sets_x_correctly() {
        	m_label->set_horizontal_alignment(Text_HAlignment::LEFT, 0);
        	CPPUNIT_ASSERT_EQUAL(0, m_label->relative_dimension().x);
        }

    void set_horizontal_alignment_to_left_with_offset_sets_x_correctly() {
    	m_label->set_horizontal_alignment(Text_HAlignment::LEFT, 15);
    	CPPUNIT_ASSERT_EQUAL(15, m_label->relative_dimension().x);
    }


    void set_horizontal_alignment_to_center_sets_x_correctly() {

    	m_label->set_relative_dimension({0, 0, 100, 20});
    	m_renderer->m_texture_width=40;
		m_renderer->m_texture_height=20;
		m_label->set_text("abcd");

		m_label->set_horizontal_alignment(Text_HAlignment::CENTER, 0);
		CPPUNIT_ASSERT_EQUAL(30, m_label->relative_dimension().x);
    }

    void set_horizontal_alignment_to_center_with_offset_sets_x_correctly() {
    	m_label->set_relative_dimension({0, 0, 100, 20});
		m_renderer->m_texture_width=40;
		m_renderer->m_texture_height=20;
		m_label->set_text("abcd");

    	m_label->set_horizontal_alignment(Text_HAlignment::CENTER, -15);
    	CPPUNIT_ASSERT_EQUAL(15, m_label->relative_dimension().x);
    }


    void set_horizontal_alignment_to_right_sets_x_correctly() {

    	m_label->set_relative_dimension({0, 0, 100, 20});
    	m_renderer->m_texture_width=40;
		m_renderer->m_texture_height=20;
		m_label->set_text("abcd");

		m_label->set_horizontal_alignment(Text_HAlignment::RIGHT, 0);
		CPPUNIT_ASSERT_EQUAL(60, m_label->relative_dimension().x);
    }

    void set_horizontal_alignment_to_right_with_offset_sets_x_correctly() {
    	m_label->set_relative_dimension({0, 0, 100, 20});
		m_renderer->m_texture_width=40;
		m_renderer->m_texture_height=20;
		m_label->set_text("abcd");

    	m_label->set_horizontal_alignment(Text_HAlignment::RIGHT, 10);
    	CPPUNIT_ASSERT_EQUAL(50, m_label->relative_dimension().x);
    }


    void set_vertical_alignment_to_top_sets_y_correctly() {
        	m_label->set_vertical_alignment(Text_VAlignment::TOP, 0);
        	CPPUNIT_ASSERT_EQUAL(0, m_label->relative_dimension().y);
	}

    void set_vertical_alignment_to_top_with_offset_sets_y_correctly() {
    	m_label->set_vertical_alignment(Text_VAlignment::TOP, 15);
    	CPPUNIT_ASSERT_EQUAL(15, m_label->relative_dimension().y);
    }


    void set_vertical_alignment_to_center_sets_y_correctly() {

    	m_label->set_relative_dimension({0, 0, 100, 50});
    	m_renderer->m_texture_width=40;
		m_renderer->m_texture_height=20;
		m_label->set_text("abcd");

		m_label->set_vertical_alignment(Text_VAlignment::CENTER, 0);
		CPPUNIT_ASSERT_EQUAL(15, m_label->relative_dimension().y);
    }


    void set_vertical_alignment_to_center_with_offset_sets_y_correctly() {
    	m_label->set_relative_dimension({0, 0, 100, 50});
		m_renderer->m_texture_width=40;
		m_renderer->m_texture_height=20;
		m_label->set_text("abcd");

    	m_label->set_vertical_alignment(Text_VAlignment::CENTER, 5);
    	CPPUNIT_ASSERT_EQUAL(20, m_label->relative_dimension().y);
    }


    void set_vertical_alignment_to_bottom_sets_y_correctly() {

    	m_label->set_relative_dimension({0, 0, 100, 70});
    	m_renderer->m_texture_width=40;
		m_renderer->m_texture_height=20;
		m_label->set_text("abcd");

		m_label->set_vertical_alignment(Text_VAlignment::BOTTOM, 0);
		CPPUNIT_ASSERT_EQUAL(50, m_label->relative_dimension().y);
    }

    void set_vertical_alignment_to_bottom_with_offset_sets_y_correctly() {
    	m_label->set_relative_dimension({0, 0, 100, 70});
		m_renderer->m_texture_width=40;
		m_renderer->m_texture_height=20;
		m_label->set_text("abcd");

    	m_label->set_vertical_alignment(Text_VAlignment::BOTTOM, 5);
    	CPPUNIT_ASSERT_EQUAL(45, m_label->relative_dimension().y);
    }
};




CPPUNIT_TEST_SUITE_REGISTRATION( TextLabelTest);
} /* ńamespace sdl_gui */

#endif /* TEXTLABELTEST_H_ */
