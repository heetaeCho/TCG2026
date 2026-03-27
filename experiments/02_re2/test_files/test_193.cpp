#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pcre.h"



namespace re2 {



class PCRETest_193 : public ::testing::Test {

protected:

    std::string str;

};



TEST_F(PCRETest_193, Replace_SuccessfulReplacement_193) {

    PCRE pattern("foo");

    str = "foobar";

    EXPECT_TRUE(pattern.Replace(&str, pattern, "bar"));

    EXPECT_EQ(str, "barbar");

}



TEST_F(PCRETest_193, Replace_NoMatch_193) {

    PCRE pattern("foo");

    str = "bazqux";

    EXPECT_FALSE(pattern.Replace(&str, pattern, "bar"));

    EXPECT_EQ(str, "bazqux");

}



TEST_F(PCRETest_193, Replace_EmptyString_193) {

    PCRE pattern("foo");

    str = "";

    EXPECT_FALSE(pattern.Replace(&str, pattern, "bar"));

    EXPECT_EQ(str, "");

}



TEST_F(PCRETest_193, Replace_MultipleMatches_193) {

    PCRE pattern("o");

    str = "foobar";

    EXPECT_TRUE(pattern.Replace(&str, pattern, "a"));

    EXPECT_EQ(str, "faabar");

}



TEST_F(PCRETest_193, Replace_BoundaryCondition_StartOfString_193) {

    PCRE pattern("^foo");

    str = "foobar";

    EXPECT_TRUE(pattern.Replace(&str, pattern, "bar"));

    EXPECT_EQ(str, "barbar");

}



TEST_F(PCRETest_193, Replace_BoundaryCondition_EndOfString_193) {

    PCRE pattern("bar$");

    str = "foobar";

    EXPECT_TRUE(pattern.Replace(&str, pattern, "qux"));

    EXPECT_EQ(str, "fooqux");

}



TEST_F(PCRETest_193, Replace_EmptyPattern_193) {

    PCRE pattern("");

    str = "foobar";

    EXPECT_FALSE(pattern.Replace(&str, pattern, "bar"));

    EXPECT_EQ(str, "foobar");

}



}  // namespace re2
