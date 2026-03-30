#include <gtest/gtest.h>



namespace re2 {



// Test fixture for IsHex function tests.

class IsHexTest : public ::testing::Test {};



// Test if IsHex correctly identifies hexadecimal digits 0-9.

TEST_F(IsHexTest_517, HexDigits0To9_ReturnTrue_517) {

    for (int c = '0'; c <= '9'; ++c) {

        EXPECT_TRUE(IsHex(c));

    }

}



// Test if IsHex correctly identifies hexadecimal digits A-F.

TEST_F(IsHexTest_517, HexDigitsAToF_ReturnTrue_517) {

    for (int c = 'A'; c <= 'F'; ++c) {

        EXPECT_TRUE(IsHex(c));

    }

}



// Test if IsHex correctly identifies hexadecimal digits a-f.

TEST_F(IsHexTest_517, HexDigitsaTof_ReturnTrue_517) {

    for (int c = 'a'; c <= 'f'; ++c) {

        EXPECT_TRUE(IsHex(c));

    }

}



// Test if IsHex returns false for characters outside the hexadecimal range.

TEST_F(IsHexTest_517, NonHexDigits_ReturnFalse_517) {

    const std::string non_hex_chars = "!@#$%^&*()_+-=[]{}|;':\",./<>?";

    for (char c : non_hex_chars) {

        EXPECT_FALSE(IsHex(c));

    }

}



// Test if IsHex returns false for characters below '0'.

TEST_F(IsHexTest_517, BelowZero_ReturnFalse_517) {

    for (int c = 0; c < '0'; ++c) {

        EXPECT_FALSE(IsHex(c));

    }

}



// Test if IsHex returns false for characters between '9' and 'A'.

TEST_F(IsHexTest_517, BetweenNineAndA_ReturnFalse_517) {

    for (int c = '9' + 1; c < 'A'; ++c) {

        EXPECT_FALSE(IsHex(c));

    }

}



// Test if IsHex returns false for characters between 'F' and 'a'.

TEST_F(IsHexTest_517, BetweenFA_ReturnFalse_517) {

    for (int c = 'F' + 1; c < 'a'; ++c) {

        EXPECT_FALSE(IsHex(c));

    }

}



// Test if IsHex returns false for characters above 'f'.

TEST_F(IsHexTest_517, AboveF_ReturnFalse_517) {

    for (int c = 'f' + 1; c <= 127; ++c) { // Assuming ASCII range

        EXPECT_FALSE(IsHex(c));

    }

}



} // namespace re2
