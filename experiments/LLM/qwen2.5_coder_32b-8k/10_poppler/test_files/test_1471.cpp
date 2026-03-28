#include <gtest/gtest.h>

#include <optional>

#include "GfxState.h"



// Assuming intToLineCapStyle is part of a class or namespace for testing purposes.

namespace Gfx {

    static std::optional<GfxState::LineCapStyle> intToLineCapStyle(int value);

}



class IntToLineCapStyleTest_1471 : public ::testing::Test {

protected:

};



TEST_F(IntToLineCapStyleTest_1471, ValidValueButt_1471) {

    auto result = Gfx::intToLineCapStyle(GfxState::LineCapButt);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, GfxState::LineCapButt);

}



TEST_F(IntToLineCapStyleTest_1471, ValidValueRound_1471) {

    auto result = Gfx::intToLineCapStyle(GfxState::LineCapRound);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, GfxState::LineCapRound);

}



TEST_F(IntToLineCapStyleTest_1471, ValidValueProjecting_1471) {

    auto result = Gfx::intToLineCapStyle(GfxState::LineCapProjecting);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, GfxState::LineCapProjecting);

}



TEST_F(IntToLineCapStyleTest_1471, InvalidValueNegative_1471) {

    auto result = Gfx::intToLineCapStyle(-1);

    EXPECT_FALSE(result.has_value());

}



TEST_F(IntToLineCapStyleTest_1471, InvalidValueAboveRange_1471) {

    auto result = Gfx::intToLineCapStyle(3);

    EXPECT_FALSE(result.has_value());

}



TEST_F(IntToLineCapStyleTest_1471, InvalidValueMaxInt_1471) {

    auto result = Gfx::intToLineCapStyle(INT_MAX);

    EXPECT_FALSE(result.has_value());

}
