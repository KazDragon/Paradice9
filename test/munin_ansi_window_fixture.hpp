#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class munin_ansi_window_fixture : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(munin_ansi_window_fixture);
        CPPUNIT_TEST(test_constructor);
        CPPUNIT_TEST(test_repaint_registration);
        CPPUNIT_TEST(test_repaint_chain);
        CPPUNIT_TEST(test_repaint_data);
        CPPUNIT_TEST(test_repaint_many_redraws);
    CPPUNIT_TEST_SUITE_END();

private :
    void test_constructor();
    void test_repaint_registration();
    void test_repaint_chain();
    void test_repaint_data();
    void test_repaint_many_redraws();
};