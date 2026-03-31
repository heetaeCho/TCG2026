#include <gtest/gtest.h>
#include <string>
#include <limits>
#include <cmath>

// Include the header under test
#include "catch2/internal/catch_to_string.hpp"

// Test suite for Catch::to_string

// ==================== Integer Tests ====================

TEST(CatchToStringTest_195, IntegerZero_195) {
    std::string result = Catch::to_string(0);
    EXPECT_EQ(result, "0");
}

TEST(CatchToStringTest_195, PositiveInteger_195) {
    std::string result = Catch::to_string(42);
    EXPECT_EQ(result, "42");
}

TEST(CatchToStringTest_195, NegativeInteger_195) {
    std::string result = Catch::to_string(-42);
    EXPECT_EQ(result, "-42");
}

TEST(CatchToStringTest_195, IntMaxValue_195) {
    int val = std::numeric_limits<int>::max();
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, IntMinValue_195) {
    int val = std::numeric_limits<int>::min();
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, OneValue_195) {
    std::string result = Catch::to_string(1);
    EXPECT_EQ(result, "1");
}

TEST(CatchToStringTest_195, NegativeOne_195) {
    std::string result = Catch::to_string(-1);
    EXPECT_EQ(result, "-1");
}

// ==================== Unsigned Integer Tests ====================

TEST(CatchToStringTest_195, UnsignedIntZero_195) {
    unsigned int val = 0u;
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, "0");
}

TEST(CatchToStringTest_195, UnsignedIntMax_195) {
    unsigned int val = std::numeric_limits<unsigned int>::max();
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, UnsignedIntPositive_195) {
    unsigned int val = 12345u;
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, "12345");
}

// ==================== Long Tests ====================

TEST(CatchToStringTest_195, LongValue_195) {
    long val = 123456789L;
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, LongNegativeValue_195) {
    long val = -123456789L;
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, LongMaxValue_195) {
    long val = std::numeric_limits<long>::max();
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, LongMinValue_195) {
    long val = std::numeric_limits<long>::min();
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

// ==================== Long Long Tests ====================

TEST(CatchToStringTest_195, LongLongValue_195) {
    long long val = 9876543210LL;
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, LongLongMax_195) {
    long long val = std::numeric_limits<long long>::max();
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, LongLongMin_195) {
    long long val = std::numeric_limits<long long>::min();
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, UnsignedLongLongMax_195) {
    unsigned long long val = std::numeric_limits<unsigned long long>::max();
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

// ==================== Floating Point Tests ====================

TEST(CatchToStringTest_195, FloatZero_195) {
    float val = 0.0f;
    std::string result = Catch::to_string(val);
    // Should produce some valid string representation of 0
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, FloatPositive_195) {
    float val = 3.14f;
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, FloatNegative_195) {
    float val = -2.718f;
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, DoubleZero_195) {
    double val = 0.0;
    std::string result = Catch::to_string(val);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, DoublePositive_195) {
    double val = 3.141592653589793;
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, DoubleNegative_195) {
    double val = -1.23456789;
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, LongDoubleValue_195) {
    long double val = 1.23456789012345L;
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

// ==================== Boundary Float Tests ====================

TEST(CatchToStringTest_195, FloatMax_195) {
    float val = std::numeric_limits<float>::max();
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, FloatMin_195) {
    float val = std::numeric_limits<float>::min();
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, DoubleMax_195) {
    double val = std::numeric_limits<double>::max();
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, DoubleMin_195) {
    double val = std::numeric_limits<double>::min();
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

// ==================== Short / char Tests ====================

TEST(CatchToStringTest_195, ShortValue_195) {
    short val = 32000;
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

TEST(CatchToStringTest_195, ShortNegative_195) {
    short val = -32000;
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, std::to_string(val));
}

// ==================== Multiple Calls / Consistency Tests ====================

TEST(CatchToStringTest_195, ConsistentResults_195) {
    int val = 42;
    std::string result1 = Catch::to_string(val);
    std::string result2 = Catch::to_string(val);
    EXPECT_EQ(result1, result2);
}

TEST(CatchToStringTest_195, DifferentValuesProduceDifferentStrings_195) {
    std::string result1 = Catch::to_string(1);
    std::string result2 = Catch::to_string(2);
    EXPECT_NE(result1, result2);
}

// ==================== Large Number Tests ====================

TEST(CatchToStringTest_195, LargePositiveNumber_195) {
    long long val = 999999999999LL;
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, "999999999999");
}

TEST(CatchToStringTest_195, LargeNegativeNumber_195) {
    long long val = -999999999999LL;
    std::string result = Catch::to_string(val);
    EXPECT_EQ(result, "-999999999999");
}

// ==================== Non-empty result Tests ====================

TEST(CatchToStringTest_195, ResultIsNonEmptyForInt_195) {
    std::string result = Catch::to_string(100);
    EXPECT_FALSE(result.empty());
}

TEST(CatchToStringTest_195, ResultIsNonEmptyForDouble_195) {
    std::string result = Catch::to_string(1.5);
    EXPECT_FALSE(result.empty());
}

TEST(CatchToStringTest_195, ResultIsNonEmptyForUnsigned_195) {
    std::string result = Catch::to_string(100u);
    EXPECT_FALSE(result.empty());
}
