// File: convert_bool_test_84.cpp
#include <gtest/gtest.h>
#include "Catch2/src/catch2/catch_tostring.hpp"

using ::testing::Test;

class ConvertBoolTest_84 : public Test {};

// Normal operation: true -> "true"
TEST_F(ConvertBoolTest_84, TrueReturnsTrue_84) {
    const std::string out = Catch::convert(true);
    EXPECT_EQ(out, "true");
    EXPECT_EQ(out.size(), std::string("true").size()); // no extra chars
}

// Normal operation: false -> "false"
TEST_F(ConvertBoolTest_84, FalseReturnsFalse_84) {
    const std::string out = Catch::convert(false);
    EXPECT_EQ(out, "false");
    EXPECT_EQ(out.size(), std::string("false").size()); // no extra chars
}

// Boundary-ish inputs via implicit conversion: 0 -> false, nonzero -> true
TEST_F(ConvertBoolTest_84, ImplicitConversionZeroIsFalse_84) {
    int zero = 0;
    const std::string out = Catch::convert(static_cast<bool>(zero));
    EXPECT_EQ(out, "false");
}

TEST_F(ConvertBoolTest_84, ImplicitConversionNonZeroIsTrue_84) {
    int one = 1;
    const std::string out = Catch::convert(static_cast<bool>(one));
    EXPECT_EQ(out, "true");
}
