// File: tests/ConvertIntoTests_374.cpp

#include <gtest/gtest.h>
#include <string>

// Include the partial header under test
#include "Catch2/src/catch2/internal/catch_clara.hpp"

using Catch::Clara::ParseResultType;

namespace {

class ConvertIntoTest_374 : public ::testing::Test {};

// [Normal] int conversion succeeds and updates target
TEST_F(ConvertIntoTest_374, IntConversion_Succeeds_374) {
    int target = 0;
    auto result = Catch::Clara::Detail::convertInto(std::string("123"), target);

    EXPECT_TRUE(result);            // ok-result
    EXPECT_EQ(target, 123);         // target updated
}

// [Normal] double conversion succeeds and updates target
TEST_F(ConvertIntoTest_374, DoubleConversion_Succeeds_374) {
    double target = 0.0;
    auto result = Catch::Clara::Detail::convertInto(std::string("2.5"), target);

    EXPECT_TRUE(result);            // ok-result
    EXPECT_DOUBLE_EQ(target, 2.5);  // target updated
}

// [Boundary] leading/trailing whitespace is accepted by stream extraction
TEST_F(ConvertIntoTest_374, WhitespaceAroundNumber_Succeeds_374) {
    int target = -1;
    auto result = Catch::Clara::Detail::convertInto(std::string("   42  "), target);

    EXPECT_TRUE(result);
    EXPECT_EQ(target, 42);
}

// [Boundary] negative numbers parse correctly
TEST_F(ConvertIntoTest_374, NegativeNumber_Succeeds_374) {
    int target = 0;
    auto result = Catch::Clara::Detail::convertInto(std::string("-7"), target);

    EXPECT_TRUE(result);
    EXPECT_EQ(target, -7);
}

// [Error] non-numeric source returns runtime error and does not modify target
TEST_F(ConvertIntoTest_374, NonNumeric_ReturnsRuntimeError_And_DoesNotModifyTarget_374) {
    int original = 7;
    int target = original;

    auto result = Catch::Clara::Detail::convertInto(std::string("abc"), target);

    EXPECT_FALSE(result); // runtime error
    // Error message is observable via the public interface
    EXPECT_EQ(result.errorMessage(), "Unable to convert 'abc' to destination type");
    EXPECT_EQ(target, original); // target unchanged on failure
}

// [Error] empty string returns runtime error and does not modify target
TEST_F(ConvertIntoTest_374, EmptyString_ReturnsRuntimeError_And_DoesNotModifyTarget_374) {
    double original = 1.1;
    double target = original;

    auto result = Catch::Clara::Detail::convertInto(std::string(""), target);

    EXPECT_FALSE(result);
    EXPECT_EQ(result.errorMessage(), "Unable to convert '' to destination type");
    EXPECT_DOUBLE_EQ(target, original);
}

} // namespace
