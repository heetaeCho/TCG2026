// File: tests/range_to_string_90_tests.cpp
#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the function under test
// Adjust include path as needed for your project layout.
#include "catch2/catch_tostring.hpp"

using Catch::rangeToString;

TEST(RangeToStringTest_90, EmptyVectorYieldsBracedSpace_90) {
    const std::vector<bool> v{};
    const std::string s = rangeToString(v);
    EXPECT_EQ(s, "{ }");
}

TEST(RangeToStringTest_90, SingleTrueFormatsCorrectly_90) {
    const std::vector<bool> v{true};
    const std::string s = rangeToString(v);
    EXPECT_EQ(s, "{ true }");
}

TEST(RangeToStringTest_90, SingleFalseFormatsCorrectly_90) {
    const std::vector<bool> v{false};
    const std::string s = rangeToString(v);
    EXPECT_EQ(s, "{ false }");
}

TEST(RangeToStringTest_90, TwoElementsCommaAndSpaces_90) {
    const std::vector<bool> v{true, false};
    const std::string s = rangeToString(v);
    // Verify exact comma + space separation and surrounding spaces
    EXPECT_EQ(s, "{ true, false }");
}

TEST(RangeToStringTest_90, MultipleElementsNoTrailingComma_90) {
    const std::vector<bool> v{false, false, false, false, false};
    const std::string s = rangeToString(v);
    // Exact expected layout, ensuring no trailing comma and proper spacing
    EXPECT_EQ(s, "{ false, false, false, false, false }");
}
