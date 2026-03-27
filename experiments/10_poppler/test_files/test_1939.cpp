#include <gtest/gtest.h>



namespace DN { namespace detail {

    inline unsigned char xtoi(unsigned char c);

} }



TEST(xtoiTest_1939, ConvertsNumericCharToValue_1939) {

    EXPECT_EQ(DN::detail::xtoui('0'), 0);

    EXPECT_EQ(DN::detail::xtoui('5'), 5);

    EXPECT_EQ(DN::detail::xtoui('9'), 9);

}



TEST(xtoiTest_1939, ConvertsUppercaseHexCharToValue_1939) {

    EXPECT_EQ(DN::detail::xtoui('A'), 10);

    EXPECT_EQ(DN::detail::xtoui('F'), 15);

}



TEST(xtoiTest_1939, ConvertsLowercaseHexCharToValue_1939) {

    EXPECT_EQ(DN::detail::xtoui('a'), 10);

    EXPECT_EQ(DN::detail::xtoui('f'), 15);

}



TEST(xtoiTest_1939, HandlesInvalidCharacterGracefully_1939) {

    // Assuming 'G' is invalid and should return an arbitrary value

    // The implementation detail here is that it returns c - 'a' + 10 which would be 7

    EXPECT_EQ(DN::detail::xtoui('G'), 7);

}



TEST(xtoiTest_1939, BoundaryConditionForNumericChars_1939) {

    EXPECT_EQ(DN::detail::xtoui('0'), 0);

    EXPECT_EQ(DN::detail::xtoui('9'), 9);

}



TEST(xtoiTest_1939, BoundaryConditionForUppercaseHexChars_1939) {

    EXPECT_EQ(DN::detail::xtoui('A'), 10);

    EXPECT_EQ(DN::detail::xtoui('F'), 15);

}



TEST(xtoiTest_1939, BoundaryConditionForLowercaseHexChars_1939) {

    EXPECT_EQ(DN::detail::xtoui('a'), 10);

    EXPECT_EQ(DN::detail::xtoui('f'), 15);

}
