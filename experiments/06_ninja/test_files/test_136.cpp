#include <gtest/gtest.h>



// Assuming the function IsKnownShellSafeCharacter is part of a class or namespace,

// we'll define a simple wrapper for testing purposes.

class UtilTestHelper {

public:

    static bool IsKnownShellSafeCharacter(char ch) {

        return ::IsKnownShellSafeCharacter(ch);

    }

};



TEST(IsKnownShellSafeCharacterTest_136, UppercaseLetter_ReturnsTrue_136) {

    EXPECT_TRUE(UtilTestHelper::IsKnownShellSafeCharacter('A'));

    EXPECT_TRUE(UtilTestHelper::IsKnownShellSafeCharacter('Z'));

}



TEST(IsKnownShellSafeCharacterTest_136, LowercaseLetter_ReturnsTrue_136) {

    EXPECT_TRUE(UtilTestHelper::IsKnownShellSafeCharacter('a'));

    EXPECT_TRUE(UtilTestHelper::IsKnownShellSafeCharacter('z'));

}



TEST(IsKnownShellSafeCharacterTest_136, Digit_ReturnsTrue_136) {

    EXPECT_TRUE(UtilTestHelper::IsKnownShellSafeCharacter('0'));

    EXPECT_TRUE(UtilTestHelper::IsKnownShellSafeCharacter('9'));

}



TEST(IsKnownShellSafeCharacterTest_136, SafeSpecialCharacters_ReturnsTrue_136) {

    EXPECT_TRUE(UtilTestHelper::IsKnownShellSafeCharacter('_'));

    EXPECT_TRUE(UtilTestHelper::IsKnownShellSafeCharacter('+'));

    EXPECT_TRUE(UtilTestHelper::IsKnownShellSafeCharacter('-'));

    EXPECT_TRUE(UtilTestHelper::IsKnownShellSafeCharacter('.'));

    EXPECT_TRUE(UtilTestHelper::IsKnownShellSafeCharacter('/'));

}



TEST(IsKnownShellSafeCharacterTest_136, NonSafeSpecialCharacters_ReturnsFalse_136) {

    EXPECT_FALSE(UtilTestHelper::IsKnownShellSafeCharacter('!'));

    EXPECT_FALSE(UtilTestHelper::IsKnownShellSafeCharacter('@'));

    EXPECT_FALSE(UtilTestHelper::IsKnownShellSafeCharacter('#'));

    EXPECT_FALSE(UtilTestHelper::IsKnownShellSafeCharacter('$'));

}



TEST(IsKnownShellSafeCharacterTest_136, Space_ReturnsFalse_136) {

    EXPECT_FALSE(UtilTestHelper::IsKnownShellSafeCharacter(' '));

}



TEST(IsKnownShellSafeCharacterTest_136, Tab_ReturnsFalse_136) {

    EXPECT_FALSE(UtilTestHelper::IsKnownShellSafeCharacter('\t'));

}



TEST(IsKnownShellSafeCharacterTest_136, Newline_ReturnsFalse_136) {

    EXPECT_FALSE(UtilTestHelper::IsKnownShellSafeCharacter('\n'));

}
