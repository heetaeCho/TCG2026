#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <numeric>  // for std::gcd

namespace Exiv2 {
    std::string getAspectRatio(uint64_t width, uint64_t height);
}

// TEST ID 121
TEST_F(GetAspectRatioTest_121, NormalOperation_121) {
    uint64_t width = 1920;
    uint64_t height = 1080;
    
    // Expected aspect ratio is "16:9"
    EXPECT_EQ(Exiv2::getAspectRatio(width, height), "16:9");
}

// TEST ID 122
TEST_F(GetAspectRatioTest_122, ZeroHeight_122) {
    uint64_t width = 1920;
    uint64_t height = 0;
    
    // When height is zero, return the ratio "1920:0"
    EXPECT_EQ(Exiv2::getAspectRatio(width, height), "1920:0");
}

// TEST ID 123
TEST_F(GetAspectRatioTest_123, ZeroWidth_123) {
    uint64_t width = 0;
    uint64_t height = 1080;
    
    // When width is zero, return the ratio "0:1080"
    EXPECT_EQ(Exiv2::getAspectRatio(width, height), "0:1080");
}

// TEST ID 124
TEST_F(GetAspectRatioTest_124, EqualWidthAndHeight_124) {
    uint64_t width = 100;
    uint64_t height = 100;
    
    // When width and height are equal, return the ratio "1:1"
    EXPECT_EQ(Exiv2::getAspectRatio(width, height), "1:1");
}

// TEST ID 125
TEST_F(GetAspectRatioTest_125, LargeNumbers_125) {
    uint64_t width = 1000000000;
    uint64_t height = 250000000;
    
    // Expected aspect ratio should be simplified: "4:1"
    EXPECT_EQ(Exiv2::getAspectRatio(width, height), "4:1");
}

// TEST ID 126
TEST_F(GetAspectRatioTest_126, GcdSimplification_126) {
    uint64_t width = 100;
    uint64_t height = 25;
    
    // gcd(100, 25) = 25, so ratio is 4:1
    EXPECT_EQ(Exiv2::getAspectRatio(width, height), "4:1");
}

// TEST ID 127
TEST_F(GetAspectRatioTest_127, EdgeCase_ZeroBoth_127) {
    uint64_t width = 0;
    uint64_t height = 0;
    
    // When both are zero, return "0:0"
    EXPECT_EQ(Exiv2::getAspectRatio(width, height), "0:0");
}

// TEST ID 128
TEST_F(GetAspectRatioTest_128, VeryLargeValues_128) {
    uint64_t width = std::numeric_limits<uint64_t>::max();
    uint64_t height = std::numeric_limits<uint64_t>::max();
    
    // gcd(max, max) = max, so the ratio is "1:1"
    EXPECT_EQ(Exiv2::getAspectRatio(width, height), "1:1");
}