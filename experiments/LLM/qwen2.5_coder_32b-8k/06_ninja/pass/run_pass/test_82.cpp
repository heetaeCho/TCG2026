#include <gtest/gtest.h>

#include "string_piece_util.h"



class StringPieceUtilTest_82 : public ::testing::Test {

protected:

    // Additional setup or teardown can go here if needed.

};



TEST_F(StringPieceUtilTest_82, ToLowerASCII_LowercaseCharacter_82) {

    char input = 'a';

    EXPECT_EQ(ToLowerASCII(input), 'a');

}



TEST_F(StringPieceUtilTest_82, ToLowerASCII_UppercaseCharacter_82) {

    char input = 'A';

    EXPECT_EQ(ToLowerASCII(input), 'a');

}



TEST_F(StringPieceUtilTest_82, ToLowerASCII_OutsideAlphabetRange_82) {

    char input = '1';

    EXPECT_EQ(ToLowerASCII(input), '1');

}



TEST_F(StringPieceUtilTest_82, ToLowerASCII_BoundaryUppercaseA_82) {

    char input = 'A';

    EXPECT_EQ(ToLowerASCII(input), 'a');

}



TEST_F(StringPieceUtilTest_82, ToLowerASCII_BoundaryUppercaseZ_82) {

    char input = 'Z';

    EXPECT_EQ(ToLowerASCII(input), 'z');

}
