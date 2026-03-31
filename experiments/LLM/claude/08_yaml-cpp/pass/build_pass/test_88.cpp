#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <limits>

// We need to include the header under test
#include "yaml-cpp/exceptions.h"

// Test fixture for BAD_SUBSCRIPT_WITH_KEY tests
class BadSubscriptWithKeyTest_88 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with integer key
TEST_F(BadSubscriptWithKeyTest_88, IntegerKey_88) {
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(42);
    // The result should contain the BAD_SUBSCRIPT message and the key
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_NE(result.find("key:"), std::string::npos);
}

// Test with zero integer key
TEST_F(BadSubscriptWithKeyTest_88, ZeroIntegerKey_88) {
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(0);
    EXPECT_NE(result.find("0"), std::string::npos);
    EXPECT_NE(result.find("key:"), std::string::npos);
}

// Test with negative integer key
TEST_F(BadSubscriptWithKeyTest_88, NegativeIntegerKey_88) {
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(-1);
    EXPECT_NE(result.find("-1"), std::string::npos);
    EXPECT_NE(result.find("key:"), std::string::npos);
}

// Test with unsigned integer key
TEST_F(BadSubscriptWithKeyTest_88, UnsignedIntegerKey_88) {
    unsigned int key = 100u;
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_NE(result.find("100"), std::string::npos);
    EXPECT_NE(result.find("key:"), std::string::npos);
}

// Test with long key
TEST_F(BadSubscriptWithKeyTest_88, LongKey_88) {
    long key = 123456789L;
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_NE(result.find("123456789"), std::string::npos);
    EXPECT_NE(result.find("key:"), std::string::npos);
}

// Test with double key
TEST_F(BadSubscriptWithKeyTest_88, DoubleKey_88) {
    double key = 3.14;
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_NE(result.find("3.14"), std::string::npos);
    EXPECT_NE(result.find("key:"), std::string::npos);
}

// Test with float key
TEST_F(BadSubscriptWithKeyTest_88, FloatKey_88) {
    float key = 2.5f;
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_NE(result.find("2.5"), std::string::npos);
    EXPECT_NE(result.find("key:"), std::string::npos);
}

// Test with max int key (boundary condition)
TEST_F(BadSubscriptWithKeyTest_88, MaxIntKey_88) {
    int key = std::numeric_limits<int>::max();
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    std::stringstream ss;
    ss << key;
    EXPECT_NE(result.find(ss.str()), std::string::npos);
    EXPECT_NE(result.find("key:"), std::string::npos);
}

// Test with min int key (boundary condition)
TEST_F(BadSubscriptWithKeyTest_88, MinIntKey_88) {
    int key = std::numeric_limits<int>::min();
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    std::stringstream ss;
    ss << key;
    EXPECT_NE(result.find(ss.str()), std::string::npos);
    EXPECT_NE(result.find("key:"), std::string::npos);
}

// Test that the result starts with BAD_SUBSCRIPT message
TEST_F(BadSubscriptWithKeyTest_88, ContainsBadSubscriptPrefix_88) {
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(5);
    EXPECT_NE(result.find(YAML::ErrorMsg::BAD_SUBSCRIPT), std::string::npos);
    // Verify the format includes parentheses with key
    EXPECT_NE(result.find("(key: \"5\")"), std::string::npos);
}

// Test with short type
TEST_F(BadSubscriptWithKeyTest_88, ShortKey_88) {
    short key = 7;
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_NE(result.find("7"), std::string::npos);
    EXPECT_NE(result.find("key:"), std::string::npos);
}

// Test with unsigned long long key
TEST_F(BadSubscriptWithKeyTest_88, UnsignedLongLongKey_88) {
    unsigned long long key = 9999999999ULL;
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_NE(result.find("9999999999"), std::string::npos);
    EXPECT_NE(result.find("key:"), std::string::npos);
}

// Verify the exact format of the output
TEST_F(BadSubscriptWithKeyTest_88, ExactFormatVerification_88) {
    int key = 10;
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    
    // Build expected string
    std::stringstream expected;
    expected << YAML::ErrorMsg::BAD_SUBSCRIPT << " (key: \"" << key << "\")";
    
    EXPECT_EQ(result, expected.str());
}

// Test that different keys produce different results
TEST_F(BadSubscriptWithKeyTest_88, DifferentKeysProduceDifferentResults_88) {
    std::string result1 = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(1);
    std::string result2 = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(2);
    EXPECT_NE(result1, result2);
}

// Test with char type (which is numeric in C++)
TEST_F(BadSubscriptWithKeyTest_88, CharKey_88) {
    char key = 'A'; // ASCII 65
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    // char streamed to stringstream produces the character, not the number
    EXPECT_NE(result.find("key:"), std::string::npos);
}
