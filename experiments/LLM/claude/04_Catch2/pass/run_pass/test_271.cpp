#include <gtest/gtest.h>
#include <string>
#include <climits>

// Include the necessary headers from Catch2
#include "catch2/catch_tostring.hpp"

class StringMakerLongLongTest_271 : public ::testing::Test {
protected:
    std::string convert(long long value) {
        return Catch::StringMaker<long long>::convert(value);
    }
};

// Test: Zero value should just return "0" with no hex
TEST_F(StringMakerLongLongTest_271, ZeroValue_271) {
    std::string result = convert(0);
    EXPECT_EQ(result, "0");
}

// Test: Value of 1 (small positive, below threshold)
TEST_F(StringMakerLongLongTest_271, SmallPositiveValue_271) {
    std::string result = convert(1);
    EXPECT_EQ(result, "1");
}

// Test: Value exactly at the hex threshold (255) - should NOT show hex
TEST_F(StringMakerLongLongTest_271, ValueAtHexThreshold_271) {
    std::string result = convert(255);
    EXPECT_EQ(result, "255");
}

// Test: Value just above the hex threshold (256) - should show hex
TEST_F(StringMakerLongLongTest_271, ValueAboveHexThreshold_271) {
    std::string result = convert(256);
    EXPECT_EQ(result, "256 (0x100)");
}

// Test: Value of 254 (one below threshold) - should NOT show hex
TEST_F(StringMakerLongLongTest_271, ValueBelowHexThreshold_271) {
    std::string result = convert(254);
    EXPECT_EQ(result, "254");
}

// Test: Negative value should not show hex (negative is not > 255)
TEST_F(StringMakerLongLongTest_271, NegativeValue_271) {
    std::string result = convert(-1);
    EXPECT_EQ(result, "-1");
}

// Test: Large negative value
TEST_F(StringMakerLongLongTest_271, LargeNegativeValue_271) {
    std::string result = convert(-1000000);
    EXPECT_EQ(result, "-1000000");
}

// Test: Large positive value should show hex representation
TEST_F(StringMakerLongLongTest_271, LargePositiveValue_271) {
    std::string result = convert(1000);
    EXPECT_EQ(result, "1000 (0x3e8)");
}

// Test: Value of 4096 (power of 2, above threshold)
TEST_F(StringMakerLongLongTest_271, PowerOfTwoAboveThreshold_271) {
    std::string result = convert(4096);
    EXPECT_EQ(result, "4096 (0x1000)");
}

// Test: LLONG_MAX should show both decimal and hex
TEST_F(StringMakerLongLongTest_271, MaxLongLong_271) {
    std::string result = convert(LLONG_MAX);
    // Should contain the decimal representation and a hex part
    EXPECT_NE(result.find("(0x"), std::string::npos);
    EXPECT_NE(result.find("9223372036854775807"), std::string::npos);
}

// Test: LLONG_MIN should not show hex (it's negative)
TEST_F(StringMakerLongLongTest_271, MinLongLong_271) {
    std::string result = convert(LLONG_MIN);
    // Should not contain hex representation since value is negative
    EXPECT_EQ(result.find("(0x"), std::string::npos);
}

// Test: Value of 100 (below threshold)
TEST_F(StringMakerLongLongTest_271, ValueOf100_271) {
    std::string result = convert(100);
    EXPECT_EQ(result, "100");
}

// Test: Value of 65535 (0xFFFF) should show hex
TEST_F(StringMakerLongLongTest_271, ValueOf65535_271) {
    std::string result = convert(65535);
    EXPECT_EQ(result, "65535 (0xffff)");
}

// Test: Value of 128 (below threshold, should not show hex)
TEST_F(StringMakerLongLongTest_271, ValueOf128_271) {
    std::string result = convert(128);
    EXPECT_EQ(result, "128");
}

// Test: Value of 512 (above threshold)
TEST_F(StringMakerLongLongTest_271, ValueOf512_271) {
    std::string result = convert(512);
    EXPECT_EQ(result, "512 (0x200)");
}
