#include <gtest/gtest.h>

#include "string_piece_util.h"

#include "string_piece.h"



class StringPieceUtilTest_126 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize common objects if needed.

    }

};



TEST_F(StringPieceUtilTest_126, EqualStringsCaseInsensitiveASCII_126) {

    StringPiece a("Hello");

    StringPiece b("hello");

    EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));

}



TEST_F(StringPieceUtilTest_126, DifferentStringsCaseInsensitiveASCII_126) {

    StringPiece a("Hello");

    StringPiece b("world");

    EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));

}



TEST_F(StringPieceUtilTest_126, DifferentLengthStringsCaseInsensitiveASCII_126) {

    StringPiece a("Hello");

    StringPiece b("hell");

    EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));

}



TEST_F(StringPieceUtilTest_126, EmptyStringComparisonCaseInsensitiveASCII_126) {

    StringPiece a("");

    StringPiece b("");

    EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));

}



TEST_F(StringPieceUtilTest_126, EmptyAndNonEmptyStringComparisonCaseInsensitiveASCII_126) {

    StringPiece a("");

    StringPiece b("test");

    EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));

}



TEST_F(StringPieceUtilTest_126, MixedCaseStringsCaseInsensitiveASCII_126) {

    StringPiece a("HeLLo");

    StringPiece b("hEllO");

    EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));

}



TEST_F(StringPieceUtilTest_126, SingleCharacterStringsCaseInsensitiveASCII_126) {

    StringPiece a("A");

    StringPiece b("a");

    EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));

}



TEST_F(StringPieceUtilTest_126, DifferentSingleCharacterStringsCaseInsensitiveASCII_126) {

    StringPiece a("A");

    StringPiece b("b");

    EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));

}
