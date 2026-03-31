#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <limits>
#include "yaml-cpp/exceptions.h"

// Test fixture for KEY_NOT_FOUND_WITH_KEY tests
class KeyNotFoundWithKeyTest_84 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with integer key
TEST_F(KeyNotFoundWithKeyTest_84, IntegerKey_84) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(42);
    // The result should contain the KEY_NOT_FOUND message and the key value
    EXPECT_NE(result.find("42"), std::string::npos);
    EXPECT_NE(result.find(": "), std::string::npos);
}

// Test with zero integer key
TEST_F(KeyNotFoundWithKeyTest_84, ZeroIntegerKey_84) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(0);
    EXPECT_NE(result.find("0"), std::string::npos);
    EXPECT_NE(result.find(": "), std::string::npos);
}

// Test with negative integer key
TEST_F(KeyNotFoundWithKeyTest_84, NegativeIntegerKey_84) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(-1);
    EXPECT_NE(result.find("-1"), std::string::npos);
    EXPECT_NE(result.find(": "), std::string::npos);
}

// Test with double key
TEST_F(KeyNotFoundWithKeyTest_84, DoubleKey_84) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(3.14);
    EXPECT_NE(result.find("3.14"), std::string::npos);
    EXPECT_NE(result.find(": "), std::string::npos);
}

// Test with float key
TEST_F(KeyNotFoundWithKeyTest_84, FloatKey_84) {
    float key = 2.5f;
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    EXPECT_NE(result.find("2.5"), std::string::npos);
    EXPECT_NE(result.find(": "), std::string::npos);
}

// Test with unsigned integer key
TEST_F(KeyNotFoundWithKeyTest_84, UnsignedIntegerKey_84) {
    unsigned int key = 100u;
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    EXPECT_NE(result.find("100"), std::string::npos);
    EXPECT_NE(result.find(": "), std::string::npos);
}

// Test with long key
TEST_F(KeyNotFoundWithKeyTest_84, LongKey_84) {
    long key = 999999L;
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    EXPECT_NE(result.find("999999"), std::string::npos);
    EXPECT_NE(result.find(": "), std::string::npos);
}

// Test with long long key
TEST_F(KeyNotFoundWithKeyTest_84, LongLongKey_84) {
    long long key = 123456789012345LL;
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    EXPECT_NE(result.find("123456789012345"), std::string::npos);
    EXPECT_NE(result.find(": "), std::string::npos);
}

// Test with max int key (boundary condition)
TEST_F(KeyNotFoundWithKeyTest_84, MaxIntKey_84) {
    int key = std::numeric_limits<int>::max();
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    std::stringstream ss;
    ss << key;
    EXPECT_NE(result.find(ss.str()), std::string::npos);
    EXPECT_NE(result.find(": "), std::string::npos);
}

// Test with min int key (boundary condition)
TEST_F(KeyNotFoundWithKeyTest_84, MinIntKey_84) {
    int key = std::numeric_limits<int>::min();
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    std::stringstream ss;
    ss << key;
    EXPECT_NE(result.find(ss.str()), std::string::npos);
    EXPECT_NE(result.find(": "), std::string::npos);
}

// Test with short key
TEST_F(KeyNotFoundWithKeyTest_84, ShortKey_84) {
    short key = 32;
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    EXPECT_NE(result.find("32"), std::string::npos);
    EXPECT_NE(result.find(": "), std::string::npos);
}

// Test that result starts with KEY_NOT_FOUND message
TEST_F(KeyNotFoundWithKeyTest_84, ResultContainsKeyNotFoundPrefix_84) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(7);
    // The result should start with YAML::ErrorMsg::KEY_NOT_FOUND
    EXPECT_EQ(result.find(YAML::ErrorMsg::KEY_NOT_FOUND), 0u);
}

// Test result format: KEY_NOT_FOUND + ": " + key
TEST_F(KeyNotFoundWithKeyTest_84, ResultFormatIsCorrect_84) {
    int key = 55;
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    std::string expected = std::string(YAML::ErrorMsg::KEY_NOT_FOUND) + ": " + "55";
    EXPECT_EQ(result, expected);
}

// Test with negative double
TEST_F(KeyNotFoundWithKeyTest_84, NegativeDoubleKey_84) {
    double key = -99.99;
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    EXPECT_NE(result.find("-99.99"), std::string::npos);
}

// Test with zero double
TEST_F(KeyNotFoundWithKeyTest_84, ZeroDoubleKey_84) {
    double key = 0.0;
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    EXPECT_NE(result.find("0"), std::string::npos);
}

// Test with unsigned long long boundary
TEST_F(KeyNotFoundWithKeyTest_84, UnsignedLongLongMaxKey_84) {
    unsigned long long key = std::numeric_limits<unsigned long long>::max();
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);
    std::stringstream ss;
    ss << key;
    EXPECT_NE(result.find(ss.str()), std::string::npos);
}

// Test that the function returns a non-empty string
TEST_F(KeyNotFoundWithKeyTest_84, ResultIsNonEmpty_84) {
    std::string result = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(1);
    EXPECT_FALSE(result.empty());
}

// Test that different keys produce different results
TEST_F(KeyNotFoundWithKeyTest_84, DifferentKeysProduceDifferentResults_84) {
    std::string result1 = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(1);
    std::string result2 = YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(2);
    EXPECT_NE(result1, result2);
}
