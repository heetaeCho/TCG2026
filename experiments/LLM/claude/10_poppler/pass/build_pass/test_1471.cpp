#include <gtest/gtest.h>
#include <optional>

// Replicate the enum from GfxState.h since we need it for testing
namespace GfxState {
enum LineCapStyle {
    LineCapButt = 0,
    LineCapRound = 1,
    LineCapProjecting = 2
};
}

// Replicate the function under test (it's a static function in Gfx.cc, so we need to
// include its definition here for testing purposes)
static std::optional<GfxState::LineCapStyle> intToLineCapStyle(int value)
{
    switch (value) {
    case GfxState::LineCapButt:
    case GfxState::LineCapRound:
    case GfxState::LineCapProjecting:
        return static_cast<GfxState::LineCapStyle>(value);
        break;
    }
    return {};
}

class IntToLineCapStyleTest_1471 : public ::testing::Test {
};

// Test that LineCapButt (0) returns the correct enum value
TEST_F(IntToLineCapStyleTest_1471, ReturnsLineCapButt_1471)
{
    auto result = intToLineCapStyle(0);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), GfxState::LineCapButt);
}

// Test that LineCapRound (1) returns the correct enum value
TEST_F(IntToLineCapStyleTest_1471, ReturnsLineCapRound_1471)
{
    auto result = intToLineCapStyle(1);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), GfxState::LineCapRound);
}

// Test that LineCapProjecting (2) returns the correct enum value
TEST_F(IntToLineCapStyleTest_1471, ReturnsLineCapProjecting_1471)
{
    auto result = intToLineCapStyle(2);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), GfxState::LineCapProjecting);
}

// Test that value 3 (one above valid range) returns nullopt
TEST_F(IntToLineCapStyleTest_1471, ReturnsNulloptForThree_1471)
{
    auto result = intToLineCapStyle(3);
    EXPECT_FALSE(result.has_value());
}

// Test that negative value -1 returns nullopt
TEST_F(IntToLineCapStyleTest_1471, ReturnsNulloptForNegativeOne_1471)
{
    auto result = intToLineCapStyle(-1);
    EXPECT_FALSE(result.has_value());
}

// Test that a large positive value returns nullopt
TEST_F(IntToLineCapStyleTest_1471, ReturnsNulloptForLargePositive_1471)
{
    auto result = intToLineCapStyle(100);
    EXPECT_FALSE(result.has_value());
}

// Test that a large negative value returns nullopt
TEST_F(IntToLineCapStyleTest_1471, ReturnsNulloptForLargeNegative_1471)
{
    auto result = intToLineCapStyle(-100);
    EXPECT_FALSE(result.has_value());
}

// Test that INT_MAX returns nullopt
TEST_F(IntToLineCapStyleTest_1471, ReturnsNulloptForIntMax_1471)
{
    auto result = intToLineCapStyle(std::numeric_limits<int>::max());
    EXPECT_FALSE(result.has_value());
}

// Test that INT_MIN returns nullopt
TEST_F(IntToLineCapStyleTest_1471, ReturnsNulloptForIntMin_1471)
{
    auto result = intToLineCapStyle(std::numeric_limits<int>::min());
    EXPECT_FALSE(result.has_value());
}

// Test boundary: value just above valid range (3)
TEST_F(IntToLineCapStyleTest_1471, BoundaryAboveValidRange_1471)
{
    auto result = intToLineCapStyle(3);
    EXPECT_FALSE(result.has_value());
}

// Test boundary: value just below valid range (-1)
TEST_F(IntToLineCapStyleTest_1471, BoundaryBelowValidRange_1471)
{
    auto result = intToLineCapStyle(-1);
    EXPECT_FALSE(result.has_value());
}

// Test that all valid values return the exact enum cast
TEST_F(IntToLineCapStyleTest_1471, AllValidValuesMatchEnumCast_1471)
{
    for (int i = 0; i <= 2; ++i) {
        auto result = intToLineCapStyle(i);
        ASSERT_TRUE(result.has_value()) << "Failed for value " << i;
        EXPECT_EQ(result.value(), static_cast<GfxState::LineCapStyle>(i))
            << "Mismatch for value " << i;
    }
}

// Test that several invalid values all return nullopt
TEST_F(IntToLineCapStyleTest_1471, MultipleInvalidValuesReturnNullopt_1471)
{
    for (int i : {-10, -5, -2, -1, 3, 4, 5, 10, 50, 255, 1000}) {
        auto result = intToLineCapStyle(i);
        EXPECT_FALSE(result.has_value()) << "Should be nullopt for value " << i;
    }
}
