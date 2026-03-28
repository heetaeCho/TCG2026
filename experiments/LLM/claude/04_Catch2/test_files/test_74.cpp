#include <gtest/gtest.h>
#include <string>
#include <cstdint>

// Include the header under test
#include "catch2/catch_tostring.hpp"

// Test fixture for rawMemoryToString tests
class RawMemoryToStringTest_74 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that rawMemoryToString returns a non-empty string for a simple integer
TEST_F(RawMemoryToStringTest_74, IntegerReturnsNonEmptyString_74) {
    int value = 42;
    std::string result = Catch::Detail::rawMemoryToString(value);
    EXPECT_FALSE(result.empty());
}

// Test that rawMemoryToString returns different strings for different integer values
TEST_F(RawMemoryToStringTest_74, DifferentIntegersProduceDifferentStrings_74) {
    int value1 = 0;
    int value2 = 1;
    std::string result1 = Catch::Detail::rawMemoryToString(value1);
    std::string result2 = Catch::Detail::rawMemoryToString(value2);
    EXPECT_NE(result1, result2);
}

// Test that rawMemoryToString returns the same string for the same value
TEST_F(RawMemoryToStringTest_74, SameValueProducesSameString_74) {
    int value1 = 12345;
    int value2 = 12345;
    std::string result1 = Catch::Detail::rawMemoryToString(value1);
    std::string result2 = Catch::Detail::rawMemoryToString(value2);
    EXPECT_EQ(result1, result2);
}

// Test with a char type (smallest common type)
TEST_F(RawMemoryToStringTest_74, CharTypeReturnsNonEmptyString_74) {
    char value = 'A';
    std::string result = Catch::Detail::rawMemoryToString(value);
    EXPECT_FALSE(result.empty());
}

// Test with zero-initialized integer
TEST_F(RawMemoryToStringTest_74, ZeroValueReturnsNonEmptyString_74) {
    int value = 0;
    std::string result = Catch::Detail::rawMemoryToString(value);
    EXPECT_FALSE(result.empty());
}

// Test with a double type
TEST_F(RawMemoryToStringTest_74, DoubleTypeReturnsNonEmptyString_74) {
    double value = 3.14159;
    std::string result = Catch::Detail::rawMemoryToString(value);
    EXPECT_FALSE(result.empty());
}

// Test with a bool type
TEST_F(RawMemoryToStringTest_74, BoolTypeReturnsNonEmptyString_74) {
    bool value = true;
    std::string result = Catch::Detail::rawMemoryToString(value);
    EXPECT_FALSE(result.empty());
}

// Test that different bool values produce different strings
TEST_F(RawMemoryToStringTest_74, DifferentBoolValuesProduceDifferentStrings_74) {
    bool trueVal = true;
    bool falseVal = false;
    std::string resultTrue = Catch::Detail::rawMemoryToString(trueVal);
    std::string resultFalse = Catch::Detail::rawMemoryToString(falseVal);
    EXPECT_NE(resultTrue, resultFalse);
}

// Test with uint8_t boundary values
TEST_F(RawMemoryToStringTest_74, Uint8BoundaryValues_74) {
    uint8_t minVal = 0;
    uint8_t maxVal = 255;
    std::string resultMin = Catch::Detail::rawMemoryToString(minVal);
    std::string resultMax = Catch::Detail::rawMemoryToString(maxVal);
    EXPECT_FALSE(resultMin.empty());
    EXPECT_FALSE(resultMax.empty());
    EXPECT_NE(resultMin, resultMax);
}

// Test with a struct type
TEST_F(RawMemoryToStringTest_74, StructTypeReturnsNonEmptyString_74) {
    struct SimpleStruct {
        int a;
        char b;
    };
    SimpleStruct s{42, 'x'};
    std::string result = Catch::Detail::rawMemoryToString(s);
    EXPECT_FALSE(result.empty());
}

// Test with int64_t type
TEST_F(RawMemoryToStringTest_74, Int64TypeReturnsNonEmptyString_74) {
    int64_t value = 9223372036854775807LL; // INT64_MAX
    std::string result = Catch::Detail::rawMemoryToString(value);
    EXPECT_FALSE(result.empty());
}

// Test with negative integer
TEST_F(RawMemoryToStringTest_74, NegativeIntegerReturnsNonEmptyString_74) {
    int value = -1;
    std::string result = Catch::Detail::rawMemoryToString(value);
    EXPECT_FALSE(result.empty());
}

// Test that negative and positive produce different strings
TEST_F(RawMemoryToStringTest_74, NegativeAndPositiveDiffer_74) {
    int pos = 1;
    int neg = -1;
    std::string resultPos = Catch::Detail::rawMemoryToString(pos);
    std::string resultNeg = Catch::Detail::rawMemoryToString(neg);
    EXPECT_NE(resultPos, resultNeg);
}

// Test with float type
TEST_F(RawMemoryToStringTest_74, FloatTypeReturnsNonEmptyString_74) {
    float value = 1.0f;
    std::string result = Catch::Detail::rawMemoryToString(value);
    EXPECT_FALSE(result.empty());
}

// Test consistency - calling twice on same object yields same result
TEST_F(RawMemoryToStringTest_74, ConsistentResultsOnRepeatedCalls_74) {
    int value = 99;
    std::string result1 = Catch::Detail::rawMemoryToString(value);
    std::string result2 = Catch::Detail::rawMemoryToString(value);
    EXPECT_EQ(result1, result2);
}

// Test with uint16_t max value
TEST_F(RawMemoryToStringTest_74, Uint16MaxValue_74) {
    uint16_t value = 65535;
    std::string result = Catch::Detail::rawMemoryToString(value);
    EXPECT_FALSE(result.empty());
}

// Test with a pointer-sized type
TEST_F(RawMemoryToStringTest_74, PointerSizedType_74) {
    uintptr_t value = 0xDEADBEEF;
    std::string result = Catch::Detail::rawMemoryToString(value);
    EXPECT_FALSE(result.empty());
}
