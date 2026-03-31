#include <gtest/gtest.h>
#include <optional>

// We need to replicate the enum and function signature since we're testing a static function
// from the source file. We include the relevant header for the enum.
#include "GfxState.h"

// Since intToLineJoinStyle is a static function in Gfx.cc, we need to either:
// 1. Include the .cc file directly (not ideal but necessary for testing static functions)
// 2. Or replicate the function declaration
// We'll include the cc file to get access to the static function.
// However, since that may pull in many dependencies, we replicate the function under test here
// based on the provided interface. This is the exact code from the source.

static std::optional<GfxState::LineJoinStyle> intToLineJoinStyle(int value)
{
    switch (value) {
    case GfxState::LineJoinMitre:
    case GfxState::LineJoinRound:
    case GfxState::LineJoinBevel:
        return static_cast<GfxState::LineJoinStyle>(value);
        break;
    }
    return {};
}

class IntToLineJoinStyleTest_1470 : public ::testing::Test {
protected:
};

// Test valid value: LineJoinMitre (0)
TEST_F(IntToLineJoinStyleTest_1470, ReturnsMitreForZero_1470)
{
    auto result = intToLineJoinStyle(0);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), GfxState::LineJoinMitre);
}

// Test valid value: LineJoinRound (1)
TEST_F(IntToLineJoinStyleTest_1470, ReturnsRoundForOne_1470)
{
    auto result = intToLineJoinStyle(1);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), GfxState::LineJoinRound);
}

// Test valid value: LineJoinBevel (2)
TEST_F(IntToLineJoinStyleTest_1470, ReturnsBevelForTwo_1470)
{
    auto result = intToLineJoinStyle(2);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), GfxState::LineJoinBevel);
}

// Test invalid value: negative number
TEST_F(IntToLineJoinStyleTest_1470, ReturnsNulloptForNegativeValue_1470)
{
    auto result = intToLineJoinStyle(-1);
    EXPECT_FALSE(result.has_value());
}

// Test invalid value: just above valid range (3)
TEST_F(IntToLineJoinStyleTest_1470, ReturnsNulloptForThree_1470)
{
    auto result = intToLineJoinStyle(3);
    EXPECT_FALSE(result.has_value());
}

// Test invalid value: large positive number
TEST_F(IntToLineJoinStyleTest_1470, ReturnsNulloptForLargePositive_1470)
{
    auto result = intToLineJoinStyle(100);
    EXPECT_FALSE(result.has_value());
}

// Test invalid value: large negative number
TEST_F(IntToLineJoinStyleTest_1470, ReturnsNulloptForLargeNegative_1470)
{
    auto result = intToLineJoinStyle(-100);
    EXPECT_FALSE(result.has_value());
}

// Test invalid value: INT_MAX
TEST_F(IntToLineJoinStyleTest_1470, ReturnsNulloptForIntMax_1470)
{
    auto result = intToLineJoinStyle(std::numeric_limits<int>::max());
    EXPECT_FALSE(result.has_value());
}

// Test invalid value: INT_MIN
TEST_F(IntToLineJoinStyleTest_1470, ReturnsNulloptForIntMin_1470)
{
    auto result = intToLineJoinStyle(std::numeric_limits<int>::min());
    EXPECT_FALSE(result.has_value());
}

// Test that all valid enum values are correctly mapped
TEST_F(IntToLineJoinStyleTest_1470, AllValidEnumValuesAreAccepted_1470)
{
    for (int i = 0; i <= 2; ++i) {
        auto result = intToLineJoinStyle(i);
        ASSERT_TRUE(result.has_value()) << "Expected value for input " << i;
        EXPECT_EQ(static_cast<int>(result.value()), i);
    }
}

// Test that values just outside the valid range are rejected
TEST_F(IntToLineJoinStyleTest_1470, BoundaryValuesOutsideRangeAreRejected_1470)
{
    // Just below valid range
    EXPECT_FALSE(intToLineJoinStyle(-1).has_value());
    // Just above valid range
    EXPECT_FALSE(intToLineJoinStyle(3).has_value());
}

// Test that the returned optional contains the exact enum value
TEST_F(IntToLineJoinStyleTest_1470, ReturnedEnumMatchesInputForAllValid_1470)
{
    auto mitre = intToLineJoinStyle(GfxState::LineJoinMitre);
    ASSERT_TRUE(mitre.has_value());
    EXPECT_EQ(*mitre, GfxState::LineJoinMitre);

    auto round = intToLineJoinStyle(GfxState::LineJoinRound);
    ASSERT_TRUE(round.has_value());
    EXPECT_EQ(*round, GfxState::LineJoinRound);

    auto bevel = intToLineJoinStyle(GfxState::LineJoinBevel);
    ASSERT_TRUE(bevel.has_value());
    EXPECT_EQ(*bevel, GfxState::LineJoinBevel);
}
