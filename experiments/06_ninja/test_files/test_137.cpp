#include <gtest/gtest.h>



// Assuming IsKnownWin32SafeCharacter is part of a class or namespace,

// we will mock up a simple structure to use it in our tests.

struct Util {

    static bool IsKnownWin32SafeCharacter(char ch) {

        return ::IsKnownWin32SafeCharacter(ch);

    }

};



TEST(IsKnownWin32SafeCharacterTest_137, NormalOperation_Space_137) {

    EXPECT_FALSE(Util::IsKnownWin32SafeCharacter(' '));

}



TEST(IsKnownWin32SafeCharacterTest_137, NormalOperation_DoubleQuote_137) {

    EXPECT_FALSE(Util::IsKnownWin32SafeCharacter('"'));

}



TEST(IsKnownWin32SafeCharacterTest_137, NormalOperation_Alphabet_137) {

    EXPECT_TRUE(Util::IsKnownWin32SafeCharacter('a'));

    EXPECT_TRUE(Util::IsKnownWin32SafeCharacter('Z'));

}



TEST(IsKnownWin32SafeCharacterTest_137, NormalOperation_Digit_137) {

    EXPECT_TRUE(Util::IsKnownWin32SafeCharacter('0'));

    EXPECT_TRUE(Util::IsKnownWin32SafeCharacter('9'));

}



TEST(IsKnownWin32SafeCharacterTest_137, BoundaryCondition_ASCIIStart_137) {

    EXPECT_FALSE(Util::IsKnownWin32SafeCharacter('\0')); // Null character

}



TEST(IsKnownWin32SafeCharacterTest_137, BoundaryCondition_ASCIIEnd_137) {

    EXPECT_TRUE(Util::IsKnownWin32SafeCharacter(126)); // Tilde (~)

}



TEST(IsKnownWin32SafeCharacterTest_137, ExceptionalCase_SpecialCharacters_137) {

    EXPECT_FALSE(Util::IsKnownWin32SafeCharacter('!'));

    EXPECT_TRUE(Util::IsKnownWin32SafeCharacter('@'));

    EXPECT_TRUE(Util::IsKnownWin32SafeCharacter('#'));

    EXPECT_TRUE(Util::IsKnownWin32SafeCharacter('$'));

    EXPECT_TRUE(Util::IsKnownWin32SafeCharacter('%'));

    EXPECT_FALSE(Util::IsKnownWin32SafeCharacter('^'));

    EXPECT_TRUE(Util::IsKnownWin32SafeCharacter('&'));

    EXPECT_TRUE(Util::IsKnownWin32SafeCharacter('*'));

    EXPECT_TRUE(Util::IsKnownWin32SafeCharacter('('));

    EXPECT_TRUE(Util::IsKnownWin32SafeCharacter(')'));

}
