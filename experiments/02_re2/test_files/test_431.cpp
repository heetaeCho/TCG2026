#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class IsEmptyOpTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common state if needed.

    }



    void TearDown() override {

        // Cleanup any common state if needed.

    }

};



TEST_F(IsEmptyOpTest, BeginLine_ReturnsTrue_431) {

    Regexp* re = new Regexp(kRegexpBeginLine, 0);

    EXPECT_TRUE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, EndLine_ReturnsTrue_431) {

    Regexp* re = new Regexp(kRegexpEndLine, 0);

    EXPECT_TRUE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, WordBoundary_ReturnsTrue_431) {

    Regexp* re = new Regexp(kRegexpWordBoundary, 0);

    EXPECT_TRUE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, NoWordBoundary_ReturnsTrue_431) {

    Regexp* re = new Regexp(kRegexpNoWordBoundary, 0);

    EXPECT_TRUE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, BeginText_ReturnsTrue_431) {

    Regexp* re = new Regexp(kRegexpBeginText, 0);

    EXPECT_TRUE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, EndText_ReturnsTrue_431) {

    Regexp* re = new Regexp(kRegexpEndText, 0);

    EXPECT_TRUE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, Literal_ReturnsFalse_431) {

    Regexp* re = new Regexp(kRegexpLiteral, 0);

    EXPECT_FALSE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, LiteralString_ReturnsFalse_431) {

    Regexp* re = new Regexp(kRegexpLiteralString, 0);

    EXPECT_FALSE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, Concat_ReturnsFalse_431) {

    Regexp* re = new Regexp(kRegexpConcat, 0);

    EXPECT_FALSE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, Alternate_ReturnsFalse_431) {

    Regexp* re = new Regexp(kRegexpAlternate, 0);

    EXPECT_FALSE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, Star_ReturnsFalse_431) {

    Regexp* re = new Regexp(kRegexpStar, 0);

    EXPECT_FALSE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, Plus_ReturnsFalse_431) {

    Regexp* re = new Regexp(kRegexpPlus, 0);

    EXPECT_FALSE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, Quest_ReturnsFalse_431) {

    Regexp* re = new Regexp(kRegexpQuest, 0);

    EXPECT_FALSE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, Repeat_ReturnsFalse_431) {

    Regexp* re = new Regexp(kRegexpRepeat, 0);

    EXPECT_FALSE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, Capture_ReturnsFalse_431) {

    Regexp* re = new Regexp(kRegexpCapture, 0);

    EXPECT_FALSE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, AnyChar_ReturnsFalse_431) {

    Regexp* re = new Regexp(kRegexpAnyChar, 0);

    EXPECT_FALSE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, AnyByte_ReturnsFalse_431) {

    Regexp* re = new Regexp(kRegexpAnyByte, 0);

    EXPECT_FALSE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, CharClass_ReturnsFalse_431) {

    Regexp* re = new Regexp(kRegexpCharClass, 0);

    EXPECT_FALSE(IsEmptyOp(re));

    delete re;

}



TEST_F(IsEmptyOpTest, HaveMatch_ReturnsFalse_431) {

    Regexp* re = new Regexp(kRegexpHaveMatch, 0);

    EXPECT_FALSE(IsEmptyOp(re));

    delete re;

}
