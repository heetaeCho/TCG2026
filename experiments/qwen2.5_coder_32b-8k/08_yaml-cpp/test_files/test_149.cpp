#include <gtest/gtest.h>

#include "yaml-cpp/src/exp.h"

#include <string>



using namespace YAML::Exp;



class RegExTest_149 : public ::testing::Test {

protected:

    const RegEx& escSingleQuoteRegex = EscSingleQuote();

};



TEST_F(RegExTest_149, MatchesSingleQuotePair_149) {

    EXPECT_TRUE(escSingleQuoteRegex.Matches("''"));

}



TEST_F(RegExTest_149, DoesNotMatchSingleQuote_149) {

    EXPECT_FALSE(escSingleQuoteRegex.Matches("'"));

}



TEST_F(RegExTest_149, DoesNotMatchEmptyString_149) {

    EXPECT_FALSE(escSingleQuoteRegex.Matches(""));

}



TEST_F(RegExTest_149, DoesNotMatchDifferentCharacters_149) {

    EXPECT_FALSE(escSingleQuoteRegex.Matches("ab"));

}



TEST_F(RegExTest_149, MatchesAtStartOfString_149) {

    EXPECT_TRUE(escSingleQuoteRegex.Matches("''abc"));

}



TEST_F(RegExTest_149, MatchesInMiddleOfString_149) {

    EXPECT_TRUE(escSingleQuoteRegex.Matches("a''c"));

}



TEST_F(RegExTest_149, MatchesAtEndOfString_149) {

    EXPECT_TRUE(escSingleQuoteRegex.Matches("abc'"));

}



TEST_F(RegExTest_149, MatchReturnsCorrectLength_149) {

    EXPECT_EQ(escSingleQuoteRegex.Match("''"), 2);

}



TEST_F(RegExTest_149, MatchReturnsZeroForNoMatch_149) {

    EXPECT_EQ(escSingleQuoteRegex.Match("a"), 0);

}
