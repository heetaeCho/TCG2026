#include <gtest/gtest.h>
#include <string>
#include "catch2/catch_tostring.hpp"

class StringMakerUnsignedLongLongTest_274 : public ::testing::Test {
protected:
    std::string convert(unsigned long long value) {
        return Catch::StringMaker<unsigned long long>::convert(value);
    }
};

// Test: Value 0 should just produce "0" with no hex suffix
TEST_F(StringMakerUnsignedLongLongTest_274, ZeroValue_274) {
    std::string result = convert(0ULL);
    EXPECT_EQ(result, "0");
}

// Test: Value 1 should produce "1" with no hex suffix
TEST_F(StringMakerUnsignedLongLongTest_274, SmallValue_274) {
    std::string result = convert(1ULL);
    EXPECT_EQ(result, "1");
}

// Test: Value exactly at threshold (255) should not have hex suffix
TEST_F(StringMakerUnsignedLongLongTest_274, ValueAtThreshold_274) {
    std::string result = convert(255ULL);
    EXPECT_EQ(result, "255");
}

// Test: Value just above threshold (256) should have hex suffix
TEST_F(StringMakerUnsignedLongLongTest_274, ValueAboveThreshold_274) {
    std::string result = convert(256ULL);
    EXPECT_EQ(result, "256 (0x100)");
}

// Test: Value 254 (below threshold) should not have hex suffix
TEST_F(StringMakerUnsignedLongLongTest_274, ValueBelowThreshold_274) {
    std::string result = convert(254ULL);
    EXPECT_EQ(result, "254");
}

// Test: Large value should include hex representation
TEST_F(StringMakerUnsignedLongLongTest_274, LargeValue_274) {
    std::string result = convert(65535ULL);
    EXPECT_EQ(result, "65535 (0xffff)");
}

// Test: Power of two above threshold
TEST_F(StringMakerUnsignedLongLongTest_274, PowerOfTwo_274) {
    std::string result = convert(1024ULL);
    EXPECT_EQ(result, "1024 (0x400)");
}

// Test: Maximum unsigned long long value
TEST_F(StringMakerUnsignedLongLongTest_274, MaxValue_274) {
    unsigned long long maxVal = std::numeric_limits<unsigned long long>::max();
    std::string result = convert(maxVal);
    // Should contain the decimal value and hex representation
    EXPECT_NE(result.find("0x"), std::string::npos);
    EXPECT_NE(result.find("ffffffffffffffff"), std::string::npos);
}

// Test: Value 4096 should have hex suffix
TEST_F(StringMakerUnsignedLongLongTest_274, Value4096_274) {
    std::string result = convert(4096ULL);
    EXPECT_EQ(result, "4096 (0x1000)");
}

// Test: Value 100 (well below threshold) should not have hex
TEST_F(StringMakerUnsignedLongLongTest_274, ValueWellBelowThreshold_274) {
    std::string result = convert(100ULL);
    EXPECT_EQ(result, "100");
}

// Test: Value 512 should include hex
TEST_F(StringMakerUnsignedLongLongTest_274, Value512_274) {
    std::string result = convert(512ULL);
    EXPECT_EQ(result, "512 (0x200)");
}

// Test: Hex output format - should have parentheses and 0x prefix
TEST_F(StringMakerUnsignedLongLongTest_274, HexFormatContainsParensAndPrefix_274) {
    std::string result = convert(1000ULL);
    // Should start with decimal
    EXPECT_EQ(result.substr(0, 4), "1000");
    // Should contain " (0x"
    EXPECT_NE(result.find(" (0x"), std::string::npos);
    // Should end with ')'
    EXPECT_EQ(result.back(), ')');
}

// Test: Value 256 hex representation
TEST_F(StringMakerUnsignedLongLongTest_274, Value256HexCorrect_274) {
    std::string result = convert(256ULL);
    EXPECT_NE(result.find("0x100"), std::string::npos);
}

// Test: Very large value 
TEST_F(StringMakerUnsignedLongLongTest_274, VeryLargeValue_274) {
    std::string result = convert(1000000000ULL);
    EXPECT_EQ(result, "1000000000 (0x3b9aca00)");
}
