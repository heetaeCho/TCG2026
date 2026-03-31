#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include <cfloat>

// Forward declaration of the function under test
namespace Catch {
    std::string getFormattedDuration(double duration);
}

// Normal operation tests

TEST(GetFormattedDurationTest_817, ZeroDuration_817) {
    std::string result = Catch::getFormattedDuration(0.0);
    EXPECT_EQ(result, "0.000");
}

TEST(GetFormattedDurationTest_817, PositiveIntegerDuration_817) {
    std::string result = Catch::getFormattedDuration(1.0);
    EXPECT_EQ(result, "1.000");
}

TEST(GetFormattedDurationTest_817, PositiveDecimalDuration_817) {
    std::string result = Catch::getFormattedDuration(1.234);
    EXPECT_EQ(result, "1.234");
}

TEST(GetFormattedDurationTest_817, NegativeDuration_817) {
    std::string result = Catch::getFormattedDuration(-1.0);
    EXPECT_EQ(result, "-1.000");
}

TEST(GetFormattedDurationTest_817, NegativeDecimalDuration_817) {
    std::string result = Catch::getFormattedDuration(-5.678);
    EXPECT_EQ(result, "-5.678");
}

TEST(GetFormattedDurationTest_817, SmallPositiveDuration_817) {
    std::string result = Catch::getFormattedDuration(0.001);
    EXPECT_EQ(result, "0.001");
}

TEST(GetFormattedDurationTest_817, VerySmallPositiveDuration_817) {
    std::string result = Catch::getFormattedDuration(0.0001);
    EXPECT_EQ(result, "0.000");
}

TEST(GetFormattedDurationTest_817, RoundingUp_817) {
    std::string result = Catch::getFormattedDuration(1.2345);
    EXPECT_EQ(result, "1.234") ; // or "1.235" depending on rounding
    // Just check it has 3 decimal places
    EXPECT_NE(result.find('.'), std::string::npos);
    size_t dotPos = result.find('.');
    EXPECT_EQ(result.size() - dotPos - 1, 3u);
}

TEST(GetFormattedDurationTest_817, LargePositiveDuration_817) {
    std::string result = Catch::getFormattedDuration(123456.789);
    EXPECT_EQ(result, "123456.789");
}

TEST(GetFormattedDurationTest_817, VeryLargeDuration_817) {
    std::string result = Catch::getFormattedDuration(1000000.0);
    EXPECT_EQ(result, "1000000.000");
}

TEST(GetFormattedDurationTest_817, ThreeDecimalPlacesFormat_817) {
    std::string result = Catch::getFormattedDuration(42.1);
    EXPECT_EQ(result, "42.100");
}

TEST(GetFormattedDurationTest_817, AlwaysHasThreeDecimalPlaces_817) {
    std::string result = Catch::getFormattedDuration(10.0);
    size_t dotPos = result.find('.');
    ASSERT_NE(dotPos, std::string::npos);
    std::string decimals = result.substr(dotPos + 1);
    EXPECT_EQ(decimals.size(), 3u);
}

TEST(GetFormattedDurationTest_817, HalfValue_817) {
    std::string result = Catch::getFormattedDuration(0.5);
    EXPECT_EQ(result, "0.500");
}

TEST(GetFormattedDurationTest_817, NegativeZero_817) {
    std::string result = Catch::getFormattedDuration(-0.0);
    // -0.0 may print as "0.000" or "-0.000" depending on implementation
    // Just check it ends with ".000"
    EXPECT_TRUE(result == "0.000" || result == "-0.000");
}

TEST(GetFormattedDurationTest_817, PrecisionTruncation_817) {
    std::string result = Catch::getFormattedDuration(1.9999);
    // Should be "2.000" or "1.999" depending on rounding
    size_t dotPos = result.find('.');
    ASSERT_NE(dotPos, std::string::npos);
    EXPECT_EQ(result.size() - dotPos - 1, 3u);
}

TEST(GetFormattedDurationTest_817, ExactlyThreeDecimalDigits_817) {
    std::string result = Catch::getFormattedDuration(3.14159);
    EXPECT_EQ(result, "3.142");
}

TEST(GetFormattedDurationTest_817, ResultIsNotEmpty_817) {
    std::string result = Catch::getFormattedDuration(99.99);
    EXPECT_FALSE(result.empty());
}

TEST(GetFormattedDurationTest_817, ContainsDot_817) {
    std::string result = Catch::getFormattedDuration(7.0);
    EXPECT_NE(result.find('.'), std::string::npos);
}

TEST(GetFormattedDurationTest_817, SmallNegativeDuration_817) {
    std::string result = Catch::getFormattedDuration(-0.001);
    EXPECT_EQ(result, "-0.001");
}

TEST(GetFormattedDurationTest_817, LargeNegativeDuration_817) {
    std::string result = Catch::getFormattedDuration(-999999.999);
    EXPECT_EQ(result, "-999999.999");
}
