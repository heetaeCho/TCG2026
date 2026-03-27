#include <gtest/gtest.h>

#include "exp.h"



using namespace YAML::Exp;



class URIRegExTest : public ::testing::Test {

protected:

    const RegEx& uri_regex = URI();

};



TEST_F(URIRegExTest_141, MatchesValidURIScheme_141) {

    EXPECT_TRUE(uri_regex.Matches("http"));

    EXPECT_TRUE(uri_regex.Matches("https"));

}



TEST_F(URIRegExTest_141, MatchesValidURICharacters_141) {

    EXPECT_TRUE(uri_regex.Matches("#"));

    EXPECT_TRUE(uri_regex.Matches(";"));

    EXPECT_TRUE(uri_regex.Matches("/"));

    EXPECT_TRUE(uri_regex.Matches("?"));

    EXPECT_TRUE(uri_regex.Matches("@"));

    EXPECT_TRUE(uri_regex.Matches("&"));

    EXPECT_TRUE(uri_regex.Matches("="));

    EXPECT_TRUE(uri_regex.Matches("+"));

    EXPECT_TRUE(uri_regex.Matches("$"));

    EXPECT_TRUE(uri_regex.Matches(","));

    EXPECT_TRUE(uri_regex.Matches("."));

    EXPECT_TRUE(uri_regex.Matches("!"));

    EXPECT_TRUE(uri_regex.Matches("~"));

    EXPECT_TRUE(uri_regex.Matches("*"));

    EXPECT_TRUE(uri_regex.Matches("'"));

    EXPECT_TRUE(uri_regex.Matches("("));

    EXPECT_TRUE(uri_regex.Matches(")"));

    EXPECT_TRUE(uri_regex.Matches("["));

    EXPECT_TRUE(uri_regex.Matches("]"));

}



TEST_F(URIRegExTest_141, MatchesPercentEncodedCharacter_141) {

    EXPECT_TRUE(uri_regex.Matches("%20"));  // Example of percent-encoded space

}



TEST_F(URIRegExTest_141, DoesNotMatchInvalidCharacters_141) {

    EXPECT_FALSE(uri_regex.Matches(" "));

    EXPECT_FALSE(uri_regex.Matches("<"));

    EXPECT_FALSE(uri_regex.Matches(">"));

    EXPECT_FALSE(uri_regex.Matches("\\"));

    EXPECT_FALSE(uri_regex.Matches("{"));

    EXPECT_FALSE(uri_regex.Matches("}"));

    EXPECT_FALSE(uri_regex.Matches("|"));

}



TEST_F(URIRegExTest_141, MatchesWordCharacters_141) {

    EXPECT_TRUE(uri_regex.Matches("a"));

    EXPECT_TRUE(uri_regex.Matches("z"));

    EXPECT_TRUE(uri_regex.Matches("A"));

    EXPECT_TRUE(uri_regex.Matches("Z"));

    EXPECT_TRUE(uri_regex.Matches("0"));

    EXPECT_TRUE(uri_regex.Matches("9"));

}



TEST_F(URIRegExTest_141, MatchesEmptyString_141) {

    EXPECT_FALSE(uri_regex.Matches(""));

}



TEST_F(URIRegExTest_141, MatchesLongValidURIString_141) {

    EXPECT_TRUE(uri_regex.Matches("https://www.example.com/path/to/resource?query=param#fragment"));

}
