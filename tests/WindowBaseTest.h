#ifndef WINDOWBASETEST_H_
#define WINDOWBASETEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>

namespace sdl_gui {

class WindowBaseTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(WindowBaseTest);
    CPPUNIT_TEST(always_pass);
    CPPUNIT_TEST(always_fail);
    CPPUNIT_TEST_SUITE_END();

public:
	WindowBaseTest();
	virtual ~WindowBaseTest();


    void setUp(void) {}
    void tearDown(void) {}

private:
	void always_pass();
	void always_fail();
};


} /* namespace sdl_gui */





#endif /* WINDOWBASETEST_H_ */
