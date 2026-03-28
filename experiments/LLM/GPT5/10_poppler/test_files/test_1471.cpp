#include <gtest/gtest.h>
#include <optional>
#include "GfxState.h"  // Ensure this header is included for the enum definition

// Function under test
static std::optional<GfxState::LineCapStyle> intToLineCapStyle(int value) {
    switch (value) {
        case GfxState::LineCapButt:
        case GfxState::LineCapRound:
        case GfxState::LineCapProjecting:
            return static_cast<GfxState::LineCapStyle>(value);
        break;
    }
    return {};
}

// TEST CASE 1: Normal operation - valid values
TEST_F(GfxStateTest_1471, ValidLineCapStyles_1471) {
    // Test each valid enum value
    EXPECT_EQ(intToLineCapStyle(GfxState::LineCapButt), GfxState::LineCapButt);
    EXPECT_EQ(intToLineCapStyle(GfxState::LineCapRound), GfxState::LineCapRound);
    EXPECT_EQ(intToLineCapStyle(GfxState::LineCapProjecting), GfxState::LineCapProjecting);
}

// TEST CASE 2: Boundary condition - Invalid value (outside the enum range)
TEST_F(GfxStateTest_1471, InvalidLineCapStyle_1471) {
    // Test an invalid value that is not in the enum
    EXPECT_EQ(intToLineCapStyle(999), std::nullopt);  // Expecting an empty optional
}

// TEST CASE 3: Boundary condition - Zero value (valid value for LineCapButt)
TEST_F(GfxStateTest_1471, ZeroLineCapStyle_1471) {
    // Test if 0 maps to LineCapButt
    EXPECT_EQ(intToLineCapStyle(0), GfxState::LineCapButt);
}

// TEST CASE 4: Exceptional case - Negative value (invalid case)
TEST_F(GfxStateTest_1471, NegativeValueLineCapStyle_1471) {
    // Test a negative value to check for exceptional behavior
    EXPECT_EQ(intToLineCapStyle(-1), std::nullopt);  // Expecting an empty optional
}

// TEST CASE 5: Boundary condition - Large invalid value
TEST_F(GfxStateTest_1471, LargeInvalidValueLineCapStyle_1471) {
    // Test a very large value that is not in the enum
    EXPECT_EQ(intToLineCapStyle(1000000), std::nullopt);  // Expecting an empty optional
}

// TEST CASE 6: Boundary condition - Value just outside the valid range
TEST_F(GfxStateTest_1471, JustOutsideValidRange_1471) {
    // Test a value just outside the valid enum range
    EXPECT_EQ(intToLineCapStyle(3), std::nullopt);  // Expecting an empty optional
}