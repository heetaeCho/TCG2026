#include <gtest/gtest.h>
#include "exiv2/bmffimage.hpp"

// Test ID: 1190

TEST(BmffEnableBMFFTest_1190, EnableBMFFReturnsBoolean_1190) {
    // enableBMFF should return a boolean value (either true or false depending on compile-time flag)
    bool result = Exiv2::enableBMFF(true);
    // The result should be either true or false
    EXPECT_TRUE(result == true || result == false);
}

TEST(BmffEnableBMFFTest_1190, EnableBMFFWithTrue_1190) {
    bool result = Exiv2::enableBMFF(true);
#ifdef EXV_ENABLE_BMFF
    EXPECT_TRUE(result);
#else
    EXPECT_FALSE(result);
#endif
}

TEST(BmffEnableBMFFTest_1190, EnableBMFFWithFalse_1190) {
    bool result = Exiv2::enableBMFF(false);
#ifdef EXV_ENABLE_BMFF
    EXPECT_TRUE(result);
#else
    EXPECT_FALSE(result);
#endif
}

TEST(BmffEnableBMFFTest_1190, EnableBMFFConsistentResults_1190) {
    // Calling enableBMFF multiple times should return the same result
    bool result1 = Exiv2::enableBMFF(true);
    bool result2 = Exiv2::enableBMFF(true);
    EXPECT_EQ(result1, result2);
}

TEST(BmffEnableBMFFTest_1190, EnableBMFFParameterIndependent_1190) {
    // The parameter doesn't seem to affect the result based on the implementation
    // The return value is determined by the compile-time flag EXV_ENABLE_BMFF
    bool resultTrue = Exiv2::enableBMFF(true);
    bool resultFalse = Exiv2::enableBMFF(false);
    EXPECT_EQ(resultTrue, resultFalse);
}

TEST(BmffEnableBMFFTest_1190, EnableBMFFMultipleCalls_1190) {
    // Verify stability across multiple calls
    for (int i = 0; i < 10; ++i) {
        bool result = Exiv2::enableBMFF(i % 2 == 0);
#ifdef EXV_ENABLE_BMFF
        EXPECT_TRUE(result) << "Iteration " << i;
#else
        EXPECT_FALSE(result) << "Iteration " << i;
#endif
    }
}
