#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/util/rune.h"



namespace re2 {



// Test fixture for runelen function tests.

class RunelenTest_206 : public ::testing::Test {

protected:

    // You can set up any common objects or state here if needed.

};



TEST_F(RunelenTest_206, NormalOperation_ASCII_206) {

    Rune ascii_rune = 'A';  // ASCII character

    EXPECT_EQ(runelen(ascii_rune), 1);

}



TEST_F(RunelenTest_206, NormalOperation_TwoByteUnicode_206) {

    Rune two_byte_unicode_rune = 0x00A9;  // Copyright symbol (©)

    EXPECT_EQ(runelen(two_byte_unicode_rune), 2);

}



TEST_F(RunelenTest_206, NormalOperation_ThreeByteUnicode_206) {

    Rune three_byte_unicode_rune = 0x20AC;  // Euro sign (€)

    EXPECT_EQ(runelen(three_byte_unicode_rune), 3);

}



TEST_F(RunelenTest_206, NormalOperation_FourByteUnicode_206) {

    Rune four_byte_unicode_rune = 0x1F600;  // Grinning face emoji

    EXPECT_EQ(runelen(four_byte_unicode_rune), 4);

}



TEST_F(RunelenTest_206, BoundaryCondition_ZeroRune_206) {

    Rune zero_rune = 0;

    EXPECT_EQ(runelen(zero_rune), 1);  // Typically, a null rune is represented as a single byte

}



TEST_F(RunelenTest_206, BoundaryCondition_MaxValidRune_206) {

    Rune max_valid_rune = 0x10FFFF;  // Maximum valid Unicode code point

    EXPECT_EQ(runelen(max_valid_rune), 4);

}



// Assuming that invalid runes are not handled gracefully and return a specific value or behavior.

// This test would be applicable if the implementation defines how to handle such cases.

TEST_F(RunelenTest_206, ExceptionalCase_OutOfRangeRune_206) {

    Rune out_of_range_rune = 0x110000;  // One past maximum valid Unicode code point

    EXPECT_EQ(runelen(out_of_range_rune), -1);  // Hypothetical behavior for invalid runes

}



}  // namespace re2
