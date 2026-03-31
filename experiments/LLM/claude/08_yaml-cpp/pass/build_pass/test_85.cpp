#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Include the header under test
#include "yaml-cpp/exceptions.h"

// Test fixture for BAD_SUBSCRIPT_WITH_KEY tests
class BadSubscriptWithKeyTest_85 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that BAD_SUBSCRIPT_WITH_KEY with a string argument returns BAD_SUBSCRIPT
TEST_F(BadSubscriptWithKeyTest_85, StringKeyReturnsBadSubscript_85) {
    std::string key = "some_key";
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_EQ(result, YAML::ErrorMsg::BAD_SUBSCRIPT);
}

// Test that BAD_SUBSCRIPT_WITH_KEY with an empty string returns BAD_SUBSCRIPT
TEST_F(BadSubscriptWithKeyTest_85, EmptyStringKeyReturnsBadSubscript_85) {
    std::string key = "";
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_EQ(result, YAML::ErrorMsg::BAD_SUBSCRIPT);
}

// Test that BAD_SUBSCRIPT_WITH_KEY with a const char* returns BAD_SUBSCRIPT
TEST_F(BadSubscriptWithKeyTest_85, CStringKeyReturnsBadSubscript_85) {
    const char* key = "test_key";
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_EQ(result, YAML::ErrorMsg::BAD_SUBSCRIPT);
}

// Test that BAD_SUBSCRIPT_WITH_KEY with a const std::string returns BAD_SUBSCRIPT
TEST_F(BadSubscriptWithKeyTest_85, ConstStringKeyReturnsBadSubscript_85) {
    const std::string key = "const_key";
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_EQ(result, YAML::ErrorMsg::BAD_SUBSCRIPT);
}

// Test that the return type is std::string
TEST_F(BadSubscriptWithKeyTest_85, ReturnTypeIsString_85) {
    std::string key = "key";
    auto result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    bool isSameType = std::is_same<decltype(result), std::string>::value;
    EXPECT_TRUE(isSameType);
}

// Test that BAD_SUBSCRIPT_WITH_KEY result is non-empty (BAD_SUBSCRIPT should be a meaningful error message)
TEST_F(BadSubscriptWithKeyTest_85, ResultIsNonEmpty_85) {
    std::string key = "any_key";
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_FALSE(result.empty());
}

// Test that BAD_SUBSCRIPT_WITH_KEY returns the same value regardless of key content
TEST_F(BadSubscriptWithKeyTest_85, DifferentKeysReturnSameResult_85) {
    std::string key1 = "first_key";
    std::string key2 = "second_key";
    std::string result1 = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key1);
    std::string result2 = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key2);
    EXPECT_EQ(result1, result2);
}

// Test with a very long string key
TEST_F(BadSubscriptWithKeyTest_85, LongStringKeyReturnsBadSubscript_85) {
    std::string key(10000, 'x');
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_EQ(result, YAML::ErrorMsg::BAD_SUBSCRIPT);
}

// Test with string containing special characters
TEST_F(BadSubscriptWithKeyTest_85, SpecialCharKeyReturnsBadSubscript_85) {
    std::string key = "key\n\t\0with_special";
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_EQ(result, YAML::ErrorMsg::BAD_SUBSCRIPT);
}

// Test that calling the function multiple times gives consistent results
TEST_F(BadSubscriptWithKeyTest_85, ConsistentResultsOnMultipleCalls_85) {
    std::string key = "test";
    std::string result1 = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    std::string result2 = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    std::string result3 = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result2, result3);
}

// Test that a custom non-numeric struct type works as a key
struct CustomNonNumericType_85 {
    std::string name;
};

TEST_F(BadSubscriptWithKeyTest_85, CustomNonNumericTypeReturnsBadSubscript_85) {
    CustomNonNumericType_85 key{"custom"};
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_EQ(result, YAML::ErrorMsg::BAD_SUBSCRIPT);
}

// Verify that SFINAE disables numeric types - this is a compile-time check
// We test that bool (a numeric type) would be disabled via the disable_if<is_numeric<T>> mechanism
// We can't directly test compilation failure, but we verify non-numeric types work
TEST_F(BadSubscriptWithKeyTest_85, BooleanPtrTypeWorksAsNonNumeric_85) {
    bool* key = nullptr;
    std::string result = YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);
    EXPECT_EQ(result, YAML::ErrorMsg::BAD_SUBSCRIPT);
}
