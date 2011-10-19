#include <cppunit/extensions/HelperMacros.h>

class SimplePuzzle : public CppUnit::TestFixture  {
    CPPUNIT_TEST_SUITE( SimplePuzzle );
    CPPUNIT_TEST( testSolveSimple );
    CPPUNIT_TEST_SUITE_END();
public:
    void testSolveSimple() {
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( SimplePuzzle );