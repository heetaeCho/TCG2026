#include <gtest/gtest.h>

#include <optional>

#include "GfxState.h"



// Assuming intToLineJoinStyle is accessible for testing purposes.

std::optional<GfxState::LineJoinStyle> intToLineJoinStyle(int value);



class IntToLineJoinStyleTest_1470 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(IntToLineJoinStyleTest_1470, ValidMitre_1470) {

    auto result = intToLineJoinStyle(GfxState::LineJoinMitre);

    EXPECT_TRUE(result.has_value());

    EXPECT_EQ(*result, GfxState::LineJoinMitre);

}



TEST_F(IntToLineJoinStyleTest_1470, ValidRound_1470) {

    auto result = intToLineJoinStyle(GfxState::LineJoinRound);

    EXPECT_TRUE(result.has_value());

    EXPECT_EQ(*result, GfxState::LineJoinRound);

}



TEST_F(IntToLineJoinStyleTest_1470, ValidBevel_1470) {

    auto result = intToLineJoinStyle(GfxState::LineJoinBevel);

    EXPECT_TRUE(result.has_value());

    EXPECT_EQ(*result, GfxState::LineJoinBevel);

}



TEST_F(IntToLineJoinStyleTest_1470, InvalidValueBelowRange_1470) {

    auto result = intToLineJoinStyle(-1);

    EXPECT_FALSE(result.has_value());

}



TEST_F(IntToLineJoinStyleTest_1470, InvalidValueAboveRange_1470) {

    auto result = intToLineJoinStyle(3);

    EXPECT_FALSE(result.has_value());

}



TEST_F(IntToLineJoinStyleTest_1470, BoundaryBelowValid_1470) {

    auto result = intToLineJoinStyle(GfxState::LineJoinMitre - 1);

    EXPECT_FALSE(result.has_value());

}



TEST_F(IntToLineJoinStyleTest_1470, BoundaryAboveValid_1470) {

    auto result = intToLineJoinStyle(GfxState::LineJoinBevel + 1);

    EXPECT_FALSE(result.has_value());

}
