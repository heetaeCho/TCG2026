#include <gtest/gtest.h>



// Assuming islatinalpha is part of a namespace or class, we'll define it as a standalone function for this example.

extern bool islatinalpha(int c);



TEST(islatinalphaTest_145, LowercaseLetterReturnsTrue_145) {

    EXPECT_TRUE(islatinalpha('a'));

    EXPECT_TRUE(islatinalpha('z'));

}



TEST(islatinalphaTest_145, UppercaseLetterReturnsTrue_145) {

    EXPECT_TRUE(islatinalpha('A'));

    EXPECT_TRUE(islatinalpha('Z'));

}



TEST(islatinalphaTest_145, DigitReturnsFalse_145) {

    EXPECT_FALSE(islatinalpha('0'));

    EXPECT_FALSE(islatinalpha('9'));

}



TEST(islatinalphaTest_145, SpecialCharacterReturnsFalse_145) {

    EXPECT_FALSE(islatinalpha('@'));

    EXPECT_FALSE(islatinalpha('#'));

}



TEST(islatinalphaTest_145, SpaceReturnsFalse_145) {

    EXPECT_FALSE(islatinalpha(' '));

}



TEST(islatinalphaTest_145, BoundaryValuesReturnCorrectly_145) {

    EXPECT_TRUE(islatinalpha('a' - 0)); // 'a'

    EXPECT_TRUE(islatinalpha('z' + 0)); // 'z'

    EXPECT_TRUE(islatinalpha('A' - 0)); // 'A'

    EXPECT_TRUE(islatinalpha('Z' + 0)); // 'Z'

    EXPECT_FALSE(islatinalpha('a' - 1)); // Before 'a'

    EXPECT_FALSE(islatinalpha('z' + 1)); // After 'z'

    EXPECT_FALSE(islatinalpha('A' - 1)); // Before 'A'

    EXPECT_FALSE(islatinalpha('Z' + 1)); // After 'Z'

}
