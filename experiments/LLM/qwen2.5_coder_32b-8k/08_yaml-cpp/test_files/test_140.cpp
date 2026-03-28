#include <gtest/gtest.h>

#include "exp.h"



namespace YAML {

    namespace Exp {



TEST_F(AnchorEndTest_140, MatchesAnchorCharacters_140) {

    const RegEx& anchorEnd = AnchorEnd();

    EXPECT_TRUE(anchorEnd.Matches(','));

    EXPECT_TRUE(anchorEnd.Matches(']'));

    EXPECT_TRUE(anchorEnd.Matches('}'));

    EXPECT_TRUE(anchorEnd.Matches('%'));

    EXPECT_TRUE(anchorEnd.Matches('@'));

    EXPECT_TRUE(anchorEnd.Matches('`'));

}



TEST_F(AnchorEndTest_140, MatchesBlankOrBreakCharacters_140) {

    const RegEx& anchorEnd = AnchorEnd();

    EXPECT_TRUE(anchorEnd.Matches(' '));

    EXPECT_TRUE(anchorEnd.Matches('\t'));

    EXPECT_TRUE(anchorEnd.Matches('\n'));

    EXPECT_TRUE(anchorEnd.Matches('\r'));

}



TEST_F(AnchorEndTest_140, DoesNotMatchOtherCharacters_140) {

    const RegEx& anchorEnd = AnchorEnd();

    EXPECT_FALSE(anchorEnd.Matches('a'));

    EXPECT_FALSE(anchorEnd.Matches('1'));

    EXPECT_FALSE(anchorEnd.Matches('#'));

}



TEST_F(AnchorEndTest_140, MatchReturnsCorrectLengthForValidAnchors_140) {

    const RegEx& anchorEnd = AnchorEnd();

    EXPECT_EQ(anchorEnd.Match(","), 1);

    EXPECT_EQ(anchorEnd.Match("]"), 1);

    EXPECT_EQ(anchorEnd.Match("}"), 1);

    EXPECT_EQ(anchorEnd.Match("%"), 1);

    EXPECT_EQ(anchorEnd.Match("@"), 1);

    EXPECT_EQ(anchorEnd.Match("`"), 1);

}



TEST_F(AnchorEndTest_140, MatchReturnsZeroForInvalidAnchors_140) {

    const RegEx& anchorEnd = AnchorEnd();

    EXPECT_EQ(anchorEnd.Match("a"), 0);

    EXPECT_EQ(anchorEnd.Match("1"), 0);

    EXPECT_EQ(anchorEnd.Match("#"), 0);

}



TEST_F(AnchorEndTest_140, MatchReturnsCorrectLengthForValidBlanks_140) {

    const RegEx& anchorEnd = AnchorEnd();

    EXPECT_EQ(anchorEnd.Match(" "), 1);

    EXPECT_EQ(anchorEnd.Match("\t"), 1);

    EXPECT_EQ(anchorEnd.Match("\n"), 1);

    EXPECT_EQ(anchorEnd.Match("\r"), 1);

}



TEST_F(AnchorEndTest_140, MatchReturnsZeroForEmptyString_140) {

    const RegEx& anchorEnd = AnchorEnd();

    EXPECT_EQ(anchorEnd.Match(""), 0);

}



} // namespace Exp

} // namespace YAML
