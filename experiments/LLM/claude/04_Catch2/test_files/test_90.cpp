#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "catch2/catch_tostring.hpp"

// Test for empty vector<bool>
TEST(RangeToStringVectorBool_90, EmptyVector_90) {
    std::vector<bool> v;
    std::string result = Catch::rangeToString(v);
    EXPECT_EQ(result, "{  }");
}

// Test for single true element
TEST(RangeToStringVectorBool_90, SingleTrueElement_90) {
    std::vector<bool> v = {true};
    std::string result = Catch::rangeToString(v);
    EXPECT_EQ(result, "{ true }");
}

// Test for single false element
TEST(RangeToStringVectorBool_90, SingleFalseElement_90) {
    std::vector<bool> v = {false};
    std::string result = Catch::rangeToString(v);
    EXPECT_EQ(result, "{ false }");
}

// Test for multiple elements all true
TEST(RangeToStringVectorBool_90, MultipleAllTrue_90) {
    std::vector<bool> v = {true, true, true};
    std::string result = Catch::rangeToString(v);
    EXPECT_EQ(result, "{ true, true, true }");
}

// Test for multiple elements all false
TEST(RangeToStringVectorBool_90, MultipleAllFalse_90) {
    std::vector<bool> v = {false, false, false};
    std::string result = Catch::rangeToString(v);
    EXPECT_EQ(result, "{ false, false, false }");
}

// Test for mixed true and false elements
TEST(RangeToStringVectorBool_90, MixedTrueFalse_90) {
    std::vector<bool> v = {true, false, true, false};
    std::string result = Catch::rangeToString(v);
    EXPECT_EQ(result, "{ true, false, true, false }");
}

// Test for two elements
TEST(RangeToStringVectorBool_90, TwoElements_90) {
    std::vector<bool> v = {false, true};
    std::string result = Catch::rangeToString(v);
    EXPECT_EQ(result, "{ false, true }");
}

// Test that commas separate elements correctly
TEST(RangeToStringVectorBool_90, CommasSeparateElements_90) {
    std::vector<bool> v = {true, false};
    std::string result = Catch::rangeToString(v);
    // Verify comma is present between elements
    EXPECT_NE(result.find(", "), std::string::npos);
}

// Test for larger vector
TEST(RangeToStringVectorBool_90, LargerVector_90) {
    std::vector<bool> v(10, true);
    v[3] = false;
    v[7] = false;
    std::string result = Catch::rangeToString(v);
    EXPECT_EQ(result, "{ true, true, true, false, true, true, true, false, true, true }");
}

// Test that result starts with "{ " and ends with " }"
TEST(RangeToStringVectorBool_90, BracketFormatting_90) {
    std::vector<bool> v = {true};
    std::string result = Catch::rangeToString(v);
    EXPECT_EQ(result.substr(0, 2), "{ ");
    EXPECT_EQ(result.substr(result.size() - 2), " }");
}

// Test with alternating pattern
TEST(RangeToStringVectorBool_90, AlternatingPattern_90) {
    std::vector<bool> v = {true, false, true, false, true};
    std::string result = Catch::rangeToString(v);
    EXPECT_EQ(result, "{ true, false, true, false, true }");
}

// Test that no trailing comma exists for single element
TEST(RangeToStringVectorBool_90, NoTrailingCommaForSingleElement_90) {
    std::vector<bool> v = {true};
    std::string result = Catch::rangeToString(v);
    // Should not contain a comma
    EXPECT_EQ(result.find(","), std::string::npos);
}
