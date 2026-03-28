#include <gtest/gtest.h>
#include <string>
#include <cstdint>

// Declaration of the function under test
namespace Exiv2 {
std::string getAspectRatio(uint64_t width, uint64_t height);
}

// Normal operation tests

TEST(GetAspectRatioTest_121, CommonAspectRatio16x9_121) {
    std::string result = Exiv2::getAspectRatio(1920, 1080);
    EXPECT_EQ(result, "16:9");
}

TEST(GetAspectRatioTest_121, CommonAspectRatio4x3_121) {
    std::string result = Exiv2::getAspectRatio(1024, 768);
    EXPECT_EQ(result, "4:3");
}

TEST(GetAspectRatioTest_121, CommonAspectRatio1x1_121) {
    std::string result = Exiv2::getAspectRatio(500, 500);
    EXPECT_EQ(result, "1:1");
}

TEST(GetAspectRatioTest_121, CommonAspectRatio3x2_121) {
    std::string result = Exiv2::getAspectRatio(3000, 2000);
    EXPECT_EQ(result, "3:2");
}

TEST(GetAspectRatioTest_121, AlreadyReducedRatio_121) {
    std::string result = Exiv2::getAspectRatio(16, 9);
    EXPECT_EQ(result, "16:9");
}

TEST(GetAspectRatioTest_121, PrimeNumbers_121) {
    std::string result = Exiv2::getAspectRatio(7, 13);
    EXPECT_EQ(result, "7:13");
}

TEST(GetAspectRatioTest_121, WidthGreaterThanHeight_121) {
    std::string result = Exiv2::getAspectRatio(1280, 720);
    EXPECT_EQ(result, "16:9");
}

TEST(GetAspectRatioTest_121, HeightGreaterThanWidth_121) {
    std::string result = Exiv2::getAspectRatio(720, 1280);
    EXPECT_EQ(result, "9:16");
}

// Boundary condition tests

TEST(GetAspectRatioTest_121, BothZero_121) {
    std::string result = Exiv2::getAspectRatio(0, 0);
    EXPECT_EQ(result, "0:0");
}

TEST(GetAspectRatioTest_121, WidthZero_121) {
    std::string result = Exiv2::getAspectRatio(0, 100);
    EXPECT_EQ(result, "0:100");
}

TEST(GetAspectRatioTest_121, HeightZero_121) {
    std::string result = Exiv2::getAspectRatio(100, 0);
    EXPECT_EQ(result, "100:0");
}

TEST(GetAspectRatioTest_121, BothOne_121) {
    std::string result = Exiv2::getAspectRatio(1, 1);
    EXPECT_EQ(result, "1:1");
}

TEST(GetAspectRatioTest_121, WidthOneHeightLarge_121) {
    std::string result = Exiv2::getAspectRatio(1, 1000000);
    EXPECT_EQ(result, "1:1000000");
}

TEST(GetAspectRatioTest_121, HeightOneWidthLarge_121) {
    std::string result = Exiv2::getAspectRatio(1000000, 1);
    EXPECT_EQ(result, "1000000:1");
}

TEST(GetAspectRatioTest_121, LargeValuesWithCommonFactor_121) {
    // 1000000 and 500000 should reduce to 2:1
    std::string result = Exiv2::getAspectRatio(1000000, 500000);
    EXPECT_EQ(result, "2:1");
}

TEST(GetAspectRatioTest_121, SameValues_121) {
    std::string result = Exiv2::getAspectRatio(12345, 12345);
    EXPECT_EQ(result, "1:1");
}

TEST(GetAspectRatioTest_121, MultiplesOfEachOther_121) {
    std::string result = Exiv2::getAspectRatio(100, 50);
    EXPECT_EQ(result, "2:1");
}

TEST(GetAspectRatioTest_121, MultiplesReversed_121) {
    std::string result = Exiv2::getAspectRatio(50, 100);
    EXPECT_EQ(result, "1:2");
}

TEST(GetAspectRatioTest_121, LargeCoprimeNumbers_121) {
    // 997 and 991 are both prime
    std::string result = Exiv2::getAspectRatio(997, 991);
    EXPECT_EQ(result, "997:991");
}

TEST(GetAspectRatioTest_121, ResolutionFormat2560x1440_121) {
    std::string result = Exiv2::getAspectRatio(2560, 1440);
    EXPECT_EQ(result, "16:9");
}

TEST(GetAspectRatioTest_121, ResolutionFormat3840x2160_121) {
    std::string result = Exiv2::getAspectRatio(3840, 2160);
    EXPECT_EQ(result, "16:9");
}

TEST(GetAspectRatioTest_121, ResolutionFormat800x600_121) {
    std::string result = Exiv2::getAspectRatio(800, 600);
    EXPECT_EQ(result, "4:3");
}

TEST(GetAspectRatioTest_121, GCDReductionCheck_121) {
    // 120 and 80 -> GCD is 40 -> 3:2
    std::string result = Exiv2::getAspectRatio(120, 80);
    EXPECT_EQ(result, "3:2");
}

TEST(GetAspectRatioTest_121, WidthTwoHeightTwo_121) {
    std::string result = Exiv2::getAspectRatio(2, 2);
    EXPECT_EQ(result, "1:1");
}

TEST(GetAspectRatioTest_121, MaxUint64Values_121) {
    uint64_t maxVal = UINT64_MAX;
    // maxVal : maxVal should be 1:1
    std::string result = Exiv2::getAspectRatio(maxVal, maxVal);
    EXPECT_EQ(result, "1:1");
}

TEST(GetAspectRatioTest_121, PowerOfTwoRatio_121) {
    std::string result = Exiv2::getAspectRatio(1024, 512);
    EXPECT_EQ(result, "2:1");
}
