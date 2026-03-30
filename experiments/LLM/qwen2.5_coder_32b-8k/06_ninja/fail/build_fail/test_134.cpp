#include <gtest/gtest.h>



TEST(IsPathSeparatorTest_134, UnixStyleSeparator_134) {

    EXPECT_TRUE(IsPathSeparator('/'));

}



TEST(IsPathSeparatorTest_134, NonSeparatorCharacter_134) {

    EXPECT_FALSE(IsPathSeparator('a'));

    EXPECT_FALSE(IsPathSeparator('.'));

    EXPECT_FALSE(IsPathSeparator('\\'));  // Backslash is not a separator on Unix

}



#ifdef _WIN32

TEST(IsPathSeparatorTest_134, WindowsStyleSeparator_134) {

    EXPECT_TRUE(IsPathSeparator('\\'));

}

#endif



TEST(IsPathSeparatorTest_134, NullCharacter_134) {

    EXPECT_FALSE(IsPathSeparator('\0'));

}



TEST(IsPathSeparatorTest_134, SpaceCharacter_134) {

    EXPECT_FALSE(IsPathSeparator(' '));

}



TEST(IsPathSeparatorTest_134, ColonCharacter_134) {

    EXPECT_FALSE(IsPathSeparator(':'));

}
