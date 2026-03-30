#include <gtest/gtest.h>

#include "TestProjects/poppler/goo/gfile.h"

#include <limits>



class GoffsetMaxTest_44 : public ::testing::Test {

protected:

    // You can set up any common state here if necessary.

};



TEST_F(GoffsetMaxTest_44, ReturnsCorrectMaxValueForOffT_44) {

#if HAVE_FSEEKO

    EXPECT_EQ(GoffsetMax(), (std::numeric_limits<off_t>::max)());

#endif

}



TEST_F(GoffsetMaxTest_44, ReturnsCorrectMaxValueForOff64T_44) {

#if HAVE_FSEEK64 || defined(__MINGW32__)

    EXPECT_EQ(GoffsetMax(), (std::numeric_limits<off64_t>::max)());

#endif

}



TEST_F(GoffsetMaxTest_44, ReturnsCorrectMaxValueForInt64_44) {

#ifdef _WIN32

    EXPECT_EQ(GoffsetMax(), (std::numeric_limits<__int64>::max)());

#endif

}



TEST_F(GoffsetMaxTest_44, ReturnsCorrectMaxValueForLong_44) {

#if !(HAVE_FSEEKO || HAVE_FSEEK64 || defined(__MINGW32__) || defined(_WIN32))

    EXPECT_EQ(GoffsetMax(), (std::numeric_limits<long>::max)());

#endif

}
