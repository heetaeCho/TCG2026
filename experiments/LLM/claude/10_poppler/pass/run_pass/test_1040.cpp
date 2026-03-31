#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashCMYK8MTest_1040 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: extracting the Magenta component from a CMYK8 color
TEST_F(SplashCMYK8MTest_1040, ReturnsMagentaComponent_1040) {
    SplashColor cmyk8 = {0, 128, 0, 0};
    EXPECT_EQ(128, splashCMYK8M(cmyk8));
}

// Test that index 1 (Magenta) is correctly returned when all components are set
TEST_F(SplashCMYK8MTest_1040, ReturnsMagentaWhenAllComponentsSet_1040) {
    SplashColor cmyk8 = {10, 20, 30, 40};
    EXPECT_EQ(20, splashCMYK8M(cmyk8));
}

// Test boundary: Magenta component is 0 (minimum value)
TEST_F(SplashCMYK8MTest_1040, ReturnsMagentaZero_1040) {
    SplashColor cmyk8 = {255, 0, 255, 255};
    EXPECT_EQ(0, splashCMYK8M(cmyk8));
}

// Test boundary: Magenta component is 255 (maximum value)
TEST_F(SplashCMYK8MTest_1040, ReturnsMagentaMax_1040) {
    SplashColor cmyk8 = {0, 255, 0, 0};
    EXPECT_EQ(255, splashCMYK8M(cmyk8));
}

// Test that changing other components does not affect the Magenta return value
TEST_F(SplashCMYK8MTest_1040, MagentaIndependentOfOtherComponents_1040) {
    SplashColor cmyk8a = {0, 100, 0, 0};
    SplashColor cmyk8b = {50, 100, 150, 200};
    SplashColor cmyk8c = {255, 100, 255, 255};
    EXPECT_EQ(splashCMYK8M(cmyk8a), splashCMYK8M(cmyk8b));
    EXPECT_EQ(splashCMYK8M(cmyk8b), splashCMYK8M(cmyk8c));
}

// Test with all components equal
TEST_F(SplashCMYK8MTest_1040, AllComponentsEqual_1040) {
    SplashColor cmyk8 = {42, 42, 42, 42};
    EXPECT_EQ(42, splashCMYK8M(cmyk8));
}

// Test with all components at maximum
TEST_F(SplashCMYK8MTest_1040, AllComponentsMax_1040) {
    SplashColor cmyk8 = {255, 255, 255, 255};
    EXPECT_EQ(255, splashCMYK8M(cmyk8));
}

// Test with all components at minimum
TEST_F(SplashCMYK8MTest_1040, AllComponentsMin_1040) {
    SplashColor cmyk8 = {0, 0, 0, 0};
    EXPECT_EQ(0, splashCMYK8M(cmyk8));
}

// Test with Magenta set to 1 (just above minimum boundary)
TEST_F(SplashCMYK8MTest_1040, MagentaOne_1040) {
    SplashColor cmyk8 = {0, 1, 0, 0};
    EXPECT_EQ(1, splashCMYK8M(cmyk8));
}

// Test with Magenta set to 254 (just below maximum boundary)
TEST_F(SplashCMYK8MTest_1040, MagentaAlmostMax_1040) {
    SplashColor cmyk8 = {0, 254, 0, 0};
    EXPECT_EQ(254, splashCMYK8M(cmyk8));
}

// Test that the function returns unsigned char type correctly for mid-range value
TEST_F(SplashCMYK8MTest_1040, ReturnTypeUnsignedChar_1040) {
    SplashColor cmyk8 = {0, 200, 0, 0};
    unsigned char result = splashCMYK8M(cmyk8);
    EXPECT_EQ(200, result);
}
