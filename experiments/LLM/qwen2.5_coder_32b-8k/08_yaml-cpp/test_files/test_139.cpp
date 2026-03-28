#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exp.h"

#include "regex_yaml.h"



using namespace YAML;

using namespace Exp;



TEST_F(AnchorTest_139, MatchesValidAnchors_139) {

    const RegEx& anchorRegex = Anchor();

    EXPECT_TRUE(anchorRegex.Matches('['));

    EXPECT_TRUE(anchorRegex.Matches(']'));

    EXPECT_TRUE(anchorRegex.Matches('{'));

    EXPECT_TRUE(anchorRegex.Matches('}'));

    EXPECT_TRUE(anchorRegex.Matches(','));

}



TEST_F(AnchorTest_139, MatchesInvalidAnchors_139) {

    const RegEx& anchorRegex = Anchor();

    EXPECT_FALSE(anchorRegex.Matches('a'));

    EXPECT_FALSE(anchorRegex.Matches('1'));

    EXPECT_FALSE(anchorRegex.Matches(' '));

    EXPECT_FALSE(anchorRegex.Matches('\n'));

}



TEST_F(AnchorTest_139, MatchesBlankOrBreak_139) {

    const RegEx& anchorRegex = Anchor();

    EXPECT_TRUE(anchorRegex.Matches(' '));  // Blank

    EXPECT_TRUE(anchorRegex.Matches('\t')); // Blank

    EXPECT_TRUE(anchorRegex.Matches('\n')); // Break

    EXPECT_TRUE(anchorRegex.Matches('\r')); // Break

}



TEST_F(AnchorTest_139, MatchesEmptyString_139) {

    const RegEx& anchorRegex = Anchor();

    EXPECT_FALSE(anchorRegex.Matches(""));

}



TEST_F(AnchorTest_139, MatchesLongStringWithAnchors_139) {

    const RegEx& anchorRegex = Anchor();

    std::string testString = "abc[def]ghi{jkl}mno,pqr";

    for (char ch : testString) {

        if (std::string("[]{},").find(ch) != std::string::npos || ch == ' ') {

            EXPECT_TRUE(anchorRegex.Matches(ch));

        } else {

            EXPECT_FALSE(anchorRegex.Matches(ch));

        }

    }

}



TEST_F(AnchorTest_139, MatchesValidAnchorsInString_139) {

    const RegEx& anchorRegex = Anchor();

    EXPECT_TRUE(anchorRegex.Matches("[]"));

    EXPECT_TRUE(anchorRegex.Matches("{}"));

    EXPECT_TRUE(anchorRegex.Matches(","));

    EXPECT_TRUE(anchorRegex.Matches("[{}]"));

}



TEST_F(AnchorTest_139, MatchesInvalidAnchorsInString_139) {

    const RegEx& anchorRegex = Anchor();

    EXPECT_FALSE(anchorRegex.Matches("abc"));

    EXPECT_FALSE(anchorRegex.Matches("123"));

    EXPECT_FALSE(anchorRegex.Matches(" "));

    EXPECT_FALSE(anchorRegex.Matches("\n"));

}



TEST_F(AnchorTest_139, MatchesBlankOrBreakInString_139) {

    const RegEx& anchorRegex = Anchor();

    EXPECT_TRUE(anchorRegex.Matches(" "));

    EXPECT_TRUE(anchorRegex.Matches("\t"));

    EXPECT_TRUE(anchorRegex.Matches("\n"));

    EXPECT_TRUE(anchorRegex.Matches("\r"));

}



TEST_F(AnchorTest_139, MatchesComplexString_139) {

    const RegEx& anchorRegex = Anchor();

    std::string testString = "abc [def] ghi {jkl} mno, pqr";

    for (char ch : testString) {

        if (std::string("[]{},").find(ch) != std::string::npos || ch == ' ') {

            EXPECT_TRUE(anchorRegex.Matches(ch));

        } else {

            EXPECT_FALSE(anchorRegex.Matches(ch));

        }

    }

}
