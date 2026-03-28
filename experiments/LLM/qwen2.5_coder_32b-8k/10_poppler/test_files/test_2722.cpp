#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/pdftotext.cc"

#include "TestProjects/poppler/poppler/TextOutputDev.h"



class DefaultEndOfLineTest : public ::testing::Test {

protected:

    // No additional setup needed for this test suite.

};



TEST_F(DefaultEndOfLineTest_2722, UnixEolOnNonWindows_2722) {

#ifndef _WIN32

    EXPECT_EQ(defaultEndOfLine(), eolUnix);

#endif

}



TEST_F(DefaultEndOfLineTest_2722, DosEolOnWindows_2722) {

#ifdef _WIN32

    EXPECT_EQ(defaultEndOfLine(), eolDOS);

#endif

}
