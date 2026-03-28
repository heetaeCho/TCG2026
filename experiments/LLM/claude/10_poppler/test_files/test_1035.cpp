#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashTypesTest_1035 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: splashRGB8B returns the blue component (index 2)
TEST_F(SplashTypesTest_1035, SplashRGB8B_ReturnsBlueComponent_1035) {
    SplashColor rgb8;
    rgb8[0] = 100; // R
    rgb8[1] = 150; // G
    rgb8[2] = 200; // B
    
    unsigned char result = splashRGB8B(rgb8);
    EXPECT_EQ(result, 200);
}

// Test with zero values
TEST_F(SplashTypesTest_1035, SplashRGB8B_ZeroBlue_1035) {
    SplashColor rgb8;
    rgb8[0] = 255;
    rgb8[1] = 128;
    rgb8[2] = 0;
    
    unsigned char result = splashRGB8B(rgb8);
    EXPECT_EQ(result, 0);
}

// Test with maximum value for blue component
TEST_F(SplashTypesTest_1035, SplashRGB8B_MaxBlue_1035) {
    SplashColor rgb8;
    rgb8[0] = 0;
    rgb8[1] = 0;
    rgb8[2] = 255;
    
    unsigned char result = splashRGB8B(rgb8);
    EXPECT_EQ(result, 255);
}

// Test that splashRGB8B only reads index 2 regardless of other values
TEST_F(SplashTypesTest_1035, SplashRGB8B_IndependentOfOtherChannels_1035) {
    SplashColor rgb8_a;
    rgb8_a[0] = 0;
    rgb8_a[1] = 0;
    rgb8_a[2] = 42;
    
    SplashColor rgb8_b;
    rgb8_b[0] = 255;
    rgb8_b[1] = 255;
    rgb8_b[2] = 42;
    
    EXPECT_EQ(splashRGB8B(rgb8_a), splashRGB8B(rgb8_b));
}

// Test with all channels set to the same value
TEST_F(SplashTypesTest_1035, SplashRGB8B_AllChannelsSame_1035) {
    SplashColor rgb8;
    rgb8[0] = 128;
    rgb8[1] = 128;
    rgb8[2] = 128;
    
    unsigned char result = splashRGB8B(rgb8);
    EXPECT_EQ(result, 128);
}

// Test boundary: value 1
TEST_F(SplashTypesTest_1035, SplashRGB8B_MinNonZeroBlue_1035) {
    SplashColor rgb8;
    rgb8[0] = 0;
    rgb8[1] = 0;
    rgb8[2] = 1;
    
    unsigned char result = splashRGB8B(rgb8);
    EXPECT_EQ(result, 1);
}

// Test boundary: value 254
TEST_F(SplashTypesTest_1035, SplashRGB8B_NearMaxBlue_1035) {
    SplashColor rgb8;
    rgb8[0] = 0;
    rgb8[1] = 0;
    rgb8[2] = 254;
    
    unsigned char result = splashRGB8B(rgb8);
    EXPECT_EQ(result, 254);
}

// Test that different blue values return different results
TEST_F(SplashTypesTest_1035, SplashRGB8B_DifferentBlueValues_1035) {
    SplashColor rgb8_a;
    rgb8_a[0] = 50;
    rgb8_a[1] = 50;
    rgb8_a[2] = 100;
    
    SplashColor rgb8_b;
    rgb8_b[0] = 50;
    rgb8_b[1] = 50;
    rgb8_b[2] = 200;
    
    EXPECT_NE(splashRGB8B(rgb8_a), splashRGB8B(rgb8_b));
}

// Test return type is unsigned char
TEST_F(SplashTypesTest_1035, SplashRGB8B_ReturnTypeCheck_1035) {
    SplashColor rgb8;
    rgb8[0] = 0;
    rgb8[1] = 0;
    rgb8[2] = 128;
    
    auto result = splashRGB8B(rgb8);
    static_assert(std::is_same<decltype(result), unsigned char>::value, 
                  "Return type should be unsigned char");
    EXPECT_EQ(result, 128);
}

// Test with mid-range value
TEST_F(SplashTypesTest_1035, SplashRGB8B_MidRangeBlue_1035) {
    SplashColor rgb8;
    rgb8[0] = 10;
    rgb8[1] = 20;
    rgb8[2] = 127;
    
    unsigned char result = splashRGB8B(rgb8);
    EXPECT_EQ(result, 127);
}
